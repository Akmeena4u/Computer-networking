/*`poll()` is a system call in C programming that provides an alternative to `select()` for monitoring multiple file descriptors for I/O events. It allows a program to wait for events on multiple file descriptors at the same time, and provides more flexibility than **`select()`** in terms of handling errors and managing timeouts.

The `poll()` function takes an array of `struct pollfd` structures that describe the file descriptors to monitor, and waits until an event occurs on one of them. Here is the prototype of the function:

```c
int poll(struct pollfd *fds, nfds_t nfds, int timeout);
```

- `fds`: a pointer to an array of `struct pollfd` structures.
- `nfds`: the number of file descriptors to monitor.
- `timeout`: the maximum time to wait for an event to occur.

The **`struct pollfd`** structure is defined as follows:

```c
struct pollfd {
    int fd;        /* file descriptor */
    short events;  /* events to look for */
    short revents; /* events that occurred */
};
```

- `fd`: the file descriptor to monitor.
- `events`: the events to look for (e.g., `POLLIN` for read readiness, `POLLOUT` for write readiness).
- `revents`: the events that occurred (set by the `poll()` function).

The **`poll()`** function returns the number of file descriptors that have events available, or -1 if an error occurs. If the **`timeout`** argument is greater than 0, **`poll()`** will wait for the specified number of milliseconds for an event to occur, otherwise it will block indefinitely until an event occurs.

After **`poll()`** returns, the **`revents`** field of each **`struct pollfd`** structure is set to indicate the events that occurred on the corresponding file descriptor. A program should check the **`revents`** field to determine which file descriptors are ready, and then perform the appropriate I/O operations.

Here is an example usage of **`poll()`**:

*/
  
  #include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/poll.h>

int main() {
    struct pollfd fds[1];
    int timeout = 5000; // 5 seconds
    int ret;

    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;

    ret = poll(fds, 1, timeout);

    if (ret == -1) {
        perror("poll()");
        exit(EXIT_FAILURE);
    }

    if (ret == 0) {
        printf("poll() timed out\n");
    }

    if (fds[0].revents & POLLIN) {
        printf("stdin is ready for reading\n");
    }

    return 0;
}
