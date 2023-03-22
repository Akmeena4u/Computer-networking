Program1: Creating fifo/named pipe ( 1.c )

```c
include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>        
int main()
        {
               int res;
               res = mkfifo("fifo1",0777); //creates a named pipe with the name fifo1
               printf("named pipe created\n");
        }
```

**Step 2** is to create a process which will use this pipe to send data. The below program will do that.

```c
#include<unistd.h>
        #include<stdio.h>
        #include<fcntl.h>
        int main()
        {
                    int res,n;
                    res=open("fifo1",O_WRONLY);
                    write(res,"Message",7);
                    printf("Sender Process %d sent the data\n",getpid());
        }
```

Compile this program as

$gcc -o 2 2.c

//Note: If you run this you will not see any output

The **third step** is to create the receiver process. The below program does so.

```c
#include<unistd.h>
        #include<stdio.h>
        #include<fcntl.h>
        int main()
        {
                    int res,n;
                    char buffer[100];
                    res=open("fifo1",O_RDONLY);
                    n=read(res,buffer,100);
                    printf("Reader process %d started\n",getpid());
                    printf("Data received by receiver %d is: %s\n",getpid(), buffer);
        }
```

This program connects to the pipe in reading mode and reads the data into buffer and prints it. But again this program will not run. Because the receiver is BLOCKED until the sender is there.

Therefore, run both the object files simultaneously as$./2 & ./3
