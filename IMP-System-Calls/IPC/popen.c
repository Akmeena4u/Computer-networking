Program to write into a pipe i.e to send data from one process to another process.

```c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
int main()
{
FILE *rd;
char buffer[50];
sprintf(buffer,"name first");
rd=popen("wc -c","w"); // wc -c -> is the process which counts the number of characters passed. 2nd parameter is "w" which means pipe is opened in writing mode
fwrite(buffer,sizeof(char),strlen(buffer),rd); // to write the data into the pipe
pclose(rd);
}
```

Program to read from a pipe i.e. to receive data from another process

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
int main()
{
FILE *rd;
char buffer[50];
rd=popen("ls","r"); //pipe opened in reading mode
fread(buffer, 1, 40, rd); //will read only 50 characters
printf("%s\n", buffer);
pclose(rd);
}
