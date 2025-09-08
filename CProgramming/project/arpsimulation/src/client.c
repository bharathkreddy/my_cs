#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_NAME "/tmp/mysock.socket"
#define BUFFER_SIZE 128
#define error_handler(msg) \
    do {perror(msg); fprintf(stderr, "\n%s\n", strerror(errno)); exit(EXIT_FAILURE); } while (0)


int
main(void)
{
    int client_socket_fd;
    int ret;
    char buffer[BUFFER_SIZE] = {0};

    /* create a local socket */
    client_socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(client_socket_fd == -1)
        error_handler("client socket");
    printf("client socket created.\n");

    /* create addres for local socket */
    struct sockaddr_un name;
    memset(&name, 0, sizeof(name));
    name.sun_family = AF_UNIX;
    strncpy(name.sun_path, SOCKET_NAME, sizeof(name.sun_path)-1);

    /* connect socket to address specified by name */
    ret = connect(client_socket_fd, (const struct sockaddr *)&name, sizeof(name));
    if(ret == -1)
        error_handler("connect");
    printf("client socket connected.\n");

    /* write data */
    printf("PID:%d\n\n\n", getpid());
    strncpy(buffer, "hello from brk.", sizeof(buffer)-1);
    ret = write(client_socket_fd, buffer, strlen(buffer)+1);
    if(ret == -1)
        error_handler("write");
    
    /* receive data */
    ret = read(client_socket_fd, buffer, sizeof(buffer));
    if(ret == -1)
        error_handler("read");

    /* ensure buffer is null terminated */
    buffer[sizeof(buffer) - 1] = '\0';
    printf("RESPONCE: %s\n", buffer);

    /* close socket */
    close(client_socket_fd);
    exit(EXIT_SUCCESS);

}
