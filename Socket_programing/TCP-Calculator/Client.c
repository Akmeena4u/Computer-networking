
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<netdb.h>

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
    
    int num1,num2 , choice ,ans;
    s: bzero(buffer, 255);
     n=read(sockfd,buffer,255);
     if(n<0){
         error("error on reading from socket");
         
     }
     
     printf("server - %s\n" , buffer);
     scanf("%d" , &num1);
     write(sockfd ,&num1, sizeof(int));
     
     
     
     bzero(buffer, 255);
     n=read(sockfd,buffer,255);       //read server string
     if(n<0){
         error("error on reading from socket");
         
     }
     
     printf("server - %s\n" , buffer);        // enter number two
     scanf("%d" , &num2);
     write(sockfd ,&num2, sizeof(int));
     
     
      bzero(buffer, 255);
     n=read(sockfd,buffer,255);       //read choice
     if(n<0){
         error("error on reading from socket");
         
     }
     
     printf("server - %s\n" , buffer);        // enter choice
     scanf("%d" ,&choice);
     write(sockfd ,&choice, sizeof(int));
     
    
     
     if(choice==5)
        goto Q;
        
    read(sockfd ,&ans , sizeof(int));
     printf("server -- the answer is :%d\n" ,ans);
     
     if(choice!=5)
        goto s;
     
     
    
   // close(newsockfd);
   Q: close(sockfd);
    return 0;
    
    
    
    
    

}
