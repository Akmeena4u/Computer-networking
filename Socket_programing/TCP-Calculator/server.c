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
    portno=atoi(argv[1]);
    
    
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=INADDR_ANY;
    serv_addr.sin_port =htons(portno);
    
    
    if(bind(sockfd , (struct sockaddr*) &serv_addr ,sizeof(serv_addr))<0){
        
        error("bind failed");
        
    }
    
    
    listen(sockfd,5);
    clilen =sizeof(cli_addr);
    newsockfd=accept(sockfd , (struct sockaddr*) &cli_addr , clilen);  // now client request is accepted
    
    
    if(newsockfd<0){
        
        error("error on accept");
        
    }
    
    
   int num1 ,num2  , ans , choice ;
   
s:    n =write(newsockfd,"ENTER number one: " ,strlen("ENTER number one: "));  //ask for number 1
     if(n<0)  error("error while wrritting ");
   
     read(newsockfd , &num1 ,sizeof(int));
      printf("client : Number one is - %d\n",num1);
   
       n =write(newsockfd,"ENTER number two: " ,strlen("ENTER number two: "));  //ask for number 2
      if(n<0)  error("error while wrritting ");
   
     read(newsockfd , &num2 ,sizeof(int));
     printf("client : Number two is - %d\n",num2);
   
   
      n =write(newsockfd,"ENTER your choice :\n1.Addition\n2.subtraction\n3.multiplication\n.4division\n5.exit\n " ,strlen("ENTER your choice :\n1.Addition\n2.subtraction\n3.multiplication\n.4division\n5.exit\n "));  //ask for choice
     if(n<0)  error("error while wrritting ");
   
      read(newsockfd , &choice ,sizeof(int));   //read choice
      printf("client : choice  is - %d\n",choice);
   
   
        switch(choice){
            
            
            case 1: 
                  ans=num1+num2;
                  break;
            case 2: 
                  ans=num1-num2;
                  break;  
            case 3: 
                  ans=num1*num2;
                  break; 
            case 4: 
                  ans=num1/num2;
                  break;
            case 5: 
                  goto Q;
                  break;      
        }
    
    write(newsockfd ,&ans , sizeof(int));
    if(choice !=5){
        goto s;
    }
    
 Q:   close(newsockfd);
      close(sockfd);
    return 0;
    
    
    
    
    

}
