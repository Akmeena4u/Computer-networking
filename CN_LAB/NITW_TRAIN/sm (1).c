#include<time.h>
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/select.h>
#include<pthread.h>
#include<signal.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/shm.h>
#include<unistd.h>
#include<sys/un.h>
#include<netinet/ip.h>
#include<arpa/inet.h>
#include<poll.h>
#include<netinet/if_ether.h>
#include<net/ethernet.h>
#include<netinet/ether.h>
#include<netinet/udp.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#define port 12001

struct mymesg{
	long mtype;
	char mtext[100];
};

int send_fd(int nusfd, int file_fd)
{
    struct iovec iov[1];
    char ptr[2] = {0, 0};
    iov[0].iov_base = ptr;
    iov[0].iov_len = 2;
    struct cmsghdr *cmptr=malloc(CMSG_LEN(sizeof(int)));
    //control message header
    cmptr->cmsg_len=CMSG_LEN(sizeof(int));
    cmptr->cmsg_level=SOL_SOCKET;
    cmptr->cmsg_type = SCM_RIGHTS;

    struct msghdr m;
    //message header
    m.msg_name=NULL;
    m.msg_namelen = 0;
    m.msg_iov=iov;
    m.msg_iovlen = 1;
    m.msg_control=cmptr;
    m.msg_controllen=CMSG_LEN(sizeof(int));
    *(int *)CMSG_DATA(cmptr) = file_fd;

    sendmsg(nusfd,&m,0);
 }


void announcement( int t, int train_no, int ufd[3], int nsfd, int *arr)
{
	

	char a[1024];
	if(t==0 ) sprintf(a,"[+]Train Number %d Arriving from Vijayawada.\n", train_no);
	else if(t==1 ) sprintf(a,"[+] Train Number %d Arriving from Delhi.\n", train_no);
	else if(t==2 ) sprintf(a,"[+] Train Number %d Arriving from Hyderabad.\n", train_no);
	for(int i=0;i<3;i++) send(ufd[i], a, sizeof(a), 0);
	
	int l=0;
	for(int i=0;i<3;i++)	
	{	printf("%d", i);
		if(l==0 && arr[i]==1) l=i+1;
	}
	printf("%d\n",l);
	
	for(int i=0;i<3;i++) 
	{	char buff[20];
		if(i==l-1) strcpy(buff,"yes");
		else strcpy(buff,"no");
		send(ufd[i], buff, sizeof(buff),0);
	}
	
	send_fd(ufd[l-1],nsfd);
	
	printf("%d, %d,\n",nsfd, ufd[l-1]);
}

void main(){
	printf("*****Station Master*****\n");
	printf("--> Connecting to Platforms\n");
	int ufd[3], clen[3], nufd[3];
	struct sockaddr_un uadr[3], cadr[3];
	for(int i=0;i<3;i++)
	{
	        
		ufd[i]=socket(AF_UNIX,SOCK_STREAM,0);
		if(ufd[i]==-1) printf("error\n");
		else printf("[+]Socket %d Created \n",i+1);
		uadr[i].sun_family=AF_UNIX;
		char address[255];
		sprintf(address,"a%d",i+1);
		unlink(address);
		strcpy(uadr[i].sun_path,address);
		if(bind(ufd[i],(struct sockaddr*)&uadr[i],sizeof(uadr[i]))==-1) printf("error bind\n");;
		listen(ufd[i],10);

		clen[i]=sizeof(cadr[i]);
		nufd[i]=accept(ufd[i],(struct sockaddr*)&cadr[i],&clen[i]);
		
		if(nufd[i]!=-1) printf("[+]Connected to Platform %d \n", i+1); 
	}
	
	key_t key = ftok("sema",66);
	int shmid = shmget(key,1024,0666|IPC_CREAT);
	int *arr = (int*) shmat(shmid,(void*)0,0);
	arr[0]=1;
	arr[1]=1;
	arr[2]=1;
	
	printf("\n-->Creating Sockets for Direction Point V, D, H\n");
	int sfd[3];
	struct sockaddr_in sadr[3];
	for(int i=0;i<3;i++)
	{
	       
		sfd[i] = socket(AF_INET, SOCK_STREAM, 0);
		if(i==0 && sfd[i]>0) printf("[+]Created Socket for Direction point V (vijayawada).\n");
		else if(i==1 && sfd[i]>0) printf("[+] Created Socket for Direction point D (delhi).\n");
		else if(i==2 && sfd[i]>0) printf("[+] Created Socket for Direction point H (hyderabad).\n");
		memset(&sadr, '\0', sizeof(sadr[i]));
		sadr[i].sin_family = AF_INET;
		sadr[i].sin_port = htons(port+i);
		sadr[i].sin_addr.s_addr = inet_addr("127.0.0.1");
		if(bind(sfd[i], (struct sockaddr*)&sadr[i], sizeof(sadr[i]))!=-1)
		printf("[+]Binded...\n");
		if(listen(sfd[i], 5)!=-1)	printf("[+]Listening...\n");
	}
	
	printf("\n---Waiting for Arrival of trains---\n");
		
	struct pollfd rfd[3];
	for(int i=0;i<3;i++) rfd[i].fd=sfd[i], rfd[i].events=POLLIN;
	int count=0;
	while(1)
	{	int n= poll(rfd,3,-1);
	printf("%d\n",n);
		if(n==0) continue;
		for(int i=0;i<3;i++)
		{	count++;
			struct sockaddr_in n_adr;
			memset(&n_adr, '\0', sizeof(n_adr));
			socklen_t adr_size;
			int nsfd= accept(sfd[i], (struct sockaddr*)&n_adr, &adr_size);
			printf("-> Train no %d arrived... Announcing to Staions\n", ntohs(n_adr.sin_port));
			announcement(i, ntohs(n_adr.sin_port), nufd, nsfd, arr);
			
		}
		//for(int i=0;i<3;i++) rfd[i].fd=sfd[i], rfd[i].events=POLLIN;
	
		
	}
	
}
