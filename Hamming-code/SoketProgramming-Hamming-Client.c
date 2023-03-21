

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
    
    
    int a[10];
    int test[10];
    int p,p1,p2,p4;
    
    printf("The data recibved is :");
    for(int i=1;i<8 ;i++){
        
        n= read(sockfd,&a[i],sizeof(int));
        if(n<0){
            error("error on receiving data");
            printf("%d" ,a[i]);
        }
        
    }
    
    printf("please enter data to be tested\n");
    
    for(int i=1;i<8;i++){
        
        scanf("%d", &test[i]);
    }
    
    p1=a[1]^a[3]^a[5]^a[7];
    p2=a[2]^a[3]^a[6]^a[7];
    p4=a[4]^a[5]^a[6]^a[7];
    
    p=4*p4+2*p2+p1;
    
      for(int i=1;i<8;i++){
            printf("%d",test[i]);
            
        }
        
    if(p==0)  printf("no error");
    
    else{
        printf("\nThe error is at position %d",p);
        printf("The correct data is");
        if(test[p]==0){
        test[p]=1;
    }

    else {
       test[p]=0;
    }
    
    
     for(int i=1;i<8;i++){

        printf("%d",test[i]);
     } 
      
    }
   
    close(sockfd);
    return 0;
    
    
    
    
    

}
