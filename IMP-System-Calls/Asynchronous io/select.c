/*select() ---is a system call in C programming that allows a program to monitor multiple file descriptors (e.g., sockets, pipes, files) to determine
if any of them are ready for reading, writing, or have an error condition. 
It provides a simple and efficient way to wait for I/O events on multiple file descriptors at the same time, 
without the need for multiple threads or processes.


select system call monitors all file descriptors present in FD_SET including new connection initiation requests
fd_set is datatype that have multiple file descriptors or varibles  for reading (readfds) , writting(writefds) , invoking fd for new connection( exceptfds) 
for example if a client sends connection initiation requestto server s then server s invoke except system call and give fd to new client and this newfd will be added to fd_set

its a blocking system call like scanf() its unblock on new connection arrival or data request arrival from existing clients
now select needs  to find it is new connection request or data request from already present clients and later on after unblocking select finds which process sends that particular request


in a process when it boots up id does three things create master socket fd and next it it to the fd_set and then invoke select on this  , as of now our fd_set only contains master socket
now it will wait for new clients when it get connect system call then it willl invoke accept and genrate a new file desciptor for further communication and place it in fd_set now it will serve


int select (int nfds, fd_set *readfds, fd_set *writefds,
            fd_set *exceptfds, struct timeval *timeout);

void FD_CLR (int fd, fd_set *set); 
int  FD_ISSET (int fd, fd_set *set); 
void FD_SET (int fd, fd_set *set); 
void FD_ZERO (fd_set *set); 

*/

//example --


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>

int main() {
    fd_set rfds;
    struct timeval tv;
    int retval;
    int fd = 0; // standard input

    /* Wait up to five seconds. */
    tv.tv_sec = 5;
    tv.tv_usec = 0;

    /* Watch stdin (fd 0) to see when it has input. */
    FD_ZERO(&rfds);
    FD_SET(fd, &rfds);

    /* Block until input becomes available or timeout occurs. */
    retval = select(fd + 1, &rfds, NULL, NULL, &tv);

    if (retval == -1) {
        perror("select()");
    } else if (retval) {
        printf("Data is available now.\n");
    } else {
        printf("No data within five seconds.\n");
    }

    return 0;
}


