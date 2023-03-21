
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<netdb.h>
#include<ctype.h>

void error(const char *msg){
    
    perror(msg);
    exit(1);
    
}


int main(int argc , char *argv[])

{
    
    if(argc<3){
        
        fprintf(stderr," filename %s is not provided\n",argv[0]);
        exit(1);
    }
    
    int sockfd , portno,n;
    char buffer[255];
    
    
    struct sockaddr_in serv_addr ;
    struct hostent *server;
    
    
     sockfd=socket(AF_INET ,SOCK_STREAM ,0);
    
    if(sockfd<0){
        
        error("socket is not created successfully");
    }
    
    server=gethostbyname(argv[1]);
    if(server==NULL){
        fprintf(stderr,"error no such host");
    }
 
    portno=atoi(argv[2]);
    bzero((char*) &serv_addr , sizeof(serv_addr));
    
    serv_addr.sin_family=AF_INET;
    bcopy((char *) server->h_addr , (char *) &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port =htons(portno);
    
    
   if(connect(sockfd ,( struct sockaddr *)  &serv_addr ,sizeof(serv_addr))<0){
       error("connection failed");
   }
   
   
   int a[10];
   printf("please input 4 bits of data\n");
   scanf("%d " , &a[3]);
   scanf("%d " , &a[5]);
   scanf("%d " , &a[6]);
   scanf("%d " , &a[7]);
   
   //calcualte parity bits
   
    a[1]=a[3]^a[5]^a[7];
    a[2]=a[3]^a[6]^a[7];
    a[4]=a[5]^a[6]^a[7];
   
   
   //sending complete msg to client
   
   for(int i=1;i<8;i++){
       
       n=write(newsockfd, &data[i] , sizeof(int));
       if(n<0){
           printf("error is sending the data ");
       }
   }

   printf("the data send is:");
   
   for(int i=1;i<8;i++){
       printf("%d",data[i]);
   }
    
   close(sockfd);
    return 0;
    
    
    
    
    

}
