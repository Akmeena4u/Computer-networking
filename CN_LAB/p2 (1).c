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
#include<errno.h>
#include<netinet/if_ether.h>
#include<net/ethernet.h>
#include<netinet/ether.h>
#include<netinet/udp.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#define path "a2"
int emty=1;
struct mymesg{
	long mtype;
	char mtext[100];
};

int recv_fd(int socket)
 {
  	struct iovec iov[1];
    char ptr[2];
    iov[0].iov_base = ptr;
    iov[0].iov_len = sizeof(ptr);
    struct cmsghdr *cmptr=malloc(CMSG_LEN(sizeof(int)));

    struct msghdr m;
    m.msg_name=NULL;
    m.msg_namelen = 0;
    m.msg_iov=iov;
    m.msg_iovlen = 1;
    m.msg_control=cmptr;
    m.msg_controllen=CMSG_LEN(sizeof(int));

    recvmsg(socket,&m,0);
    int fileFD = *(int *)CMSG_DATA(cmptr);
    printf("%d \n", fileFD);
    return fileFD;
 }

void update(int usfd)
{

	key_t key = ftok("sema",66);
	int shmid = shmget(key,1024,0666|IPC_CREAT);
	int *arr = (int*) shmat(shmid,(void*)0,0);
	arr[1]= 1;
	printf("  Platform State Updated to Station Master\n");

        char id[10];
         strcmp(id,"1");
	char buff[20];
	recv(usfd, buff, 20, 0);
	if(!strcmp(buff,"yes"))
	{	printf("receiving train info\n");
		int fd = recv_fd(usfd);
		printf("%d\n", fd);
		send(fd, "send data", 15,0);
		char seq[1024];
		recv(fd, seq, sizeof(seq), 0);
		send(fd,id,sizeof(id),0);
		arr[1]=0;
		printf("  Train Sequence of Compartments: %s \n",seq);
		
		close(fd);
	}
	printf("heyy");
	
}

int main() 
{	printf("*****Platform-1*****\n");
	int usfd, ulen, clen;
	struct sockaddr_un uadr;
	bzero(&uadr,sizeof(uadr));
  	usfd = socket(AF_UNIX, SOCK_STREAM, 0);
  	printf("[+]Platform 1 socket created succesfully\n");
  	bzero(&uadr,sizeof(uadr));
  	uadr.sun_family = AF_UNIX;
  	unlink(path);
   	strcpy(uadr.sun_path, path);
	ulen = sizeof(uadr);
	if(connect(usfd,(struct sockaddr *)&uadr,ulen)!=-1)
	printf("[+]Connected Station Master\n");
	printf("\n-->Ready for Announcement and accepting train\n");
	while(1)
	{	time_t t;   
    		time(&t);
	    	char buff[1024];
	    	recv(usfd, buff, 1024, 0);
	    	printf("%s\n", buff);
	    	update(usfd); 
	}
}
