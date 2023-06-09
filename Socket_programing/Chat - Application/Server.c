/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.
  
  gcc server.c -o sever
  ./server 9999
  
  for client
  
  ./client loopback 9999
  
  loopback === ip address of server == 127.0.0.1
  
  
  ifconfig to get ipadrres

*******************************************************************************/
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>

void error(const char *msg){
    
    perror(msg);
    exit(1);
    
}


int main(int argc , char *argv[])

{
    
    if(argc<2){
        
        fprintf(stderr,"port numer is not provided\n");
        exit(1);
    }
    
    int sockfd ,newsockfd , portno,n;
    char buffer[255];
    
    
    struct sockaddr_in serv_addr  , cli_addr;
    socklen_t clilen;
    
     sockfd=socket(AF_INET ,SOCK_STREAM ,0);
    
    if(sockfd<0){
        
        error("socket is not created successfully");
    }
    
    bzero((char*) &serv_addr , sizeof(serv_addr));
    portno=ato(argv[1]);
    
    
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=INADDR_ANY;
    serv_addr.sin_port =htons(portno);
    
    
    if(bind(sockfd , (struct sockaddr*) &serv_addr ,sizeof(serv_addr))<0){
        
        error("bind failed");
        
    }
    
    
    listen(sockfd,5);
    
    int newsockfd=accept(sockfd , (struct sockaddr*) &cli_addr , sizeof(cli_addr));  // now client request is accepted
    
    
    if(newsockfd<0){
        
        error("error on accept");
        
    }
    
    
    while(1){
        
        bzero(buffer ,255);
        
         n =read(newsockfd , buffer ,255);
        
        if(n<0){
            
            error("error at reading");
            
        }
        
        printf("client : %s\n" ,buffer);
        
        bzero(buffer ,255);
        
        fgets(buffer ,255, stdin);
        
         n=write(newsockfd ,buffer , strlen(buffer));
        
        if(n<0){
            error("error while writting");
        }
        
        int i =strncmp("BYE" ,buffer ,3);
        if(i==0){
            break;
        }
        
    }
    
    
    close(newsockfd);
    close(sockfd);
    return 0;
    
    
    
    
    

}

