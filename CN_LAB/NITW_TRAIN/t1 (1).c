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
#define PORT 12001
void main()
{	int csfd;
	struct sockaddr_in sadr;
	csfd = socket(PF_INET, SOCK_STREAM, 0);
	printf("[+]Train 1 Socket Created Sucessfully.\n");
	memset(&sadr, '\0', sizeof(sadr));
	sadr.sin_family = AF_INET;
	sadr.sin_port = htons(PORT);
	sadr.sin_addr.s_addr = inet_addr("127.0.0.1");
	connect(csfd, (struct sockaddr*)&sadr, sizeof(sadr));
	printf("[+]Connected to Station Master.\n");
	char a[15];
	recv(csfd, a, sizeof(a), 0);
	printf("%s\n",a);
	
	char buff[1024];
	char id[10];
	strcpy(buff,"E-A1-A2-A3-C1-C2-C3-D1-D2\n");
	key_t key = ftok("sema",66);
	int shmid = shmget(key,1024,0666|IPC_CREAT);
	int *arr = (int*) shmat(shmid,(void*)0,0);
	send(csfd, buff, sizeof(buff),0);
	recv(csfd,id,sizeof(id),0);
	
	sleep(40);
	int k = atoi(id);
	arr[k]=1;
	printf("Data Sent\n");
	close(csfd);
}
