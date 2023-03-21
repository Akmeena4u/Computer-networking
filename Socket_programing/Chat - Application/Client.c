/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
/*
filename server_ipaddress portno

argv[0]  filename
argv[1]  server server_ipaddress
arrgv[2]  portno

*/



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
    
    
    while(1){
        
        bzero(buffer ,255);
        fgets(buffer,255,stdin);
        n=write(sockfd ,buffer , strlen(buffer));
        
        if(n<0){
            error("error while writhing\n");
        }
        
        bzero(buffer ,255);
        
        n=read(sockfd, buffer,255);
        if(n<0){
            error("error on reading");
        }
        
        printf("server : %s", buffer);
        
        int i=strncmp("BYE",buffer ,3);
        if(i==0){
            break;
        }
    }
    
   // close(newsockfd);
    close(sockfd);
    return 0;
    
    
    
    
    

}
