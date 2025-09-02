// client implementation, pass integers to a server, on sending 0
// gets back sum of all numbers from server.
// get connect: Connection refused when server is not reachable.
// server and client has to run on same machine 

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/un.h>

#define BUFFER_SIZE 128
#define SOCKET_NAME "/tmp/mysock"
#define error_handler(msg) \
    do {perror(msg); exit(EXIT_FAILURE);} while(0)

int 
main(void)
{
    int data_socket;
    struct sockaddr_un addr; 
    int ret;
    int i;
    char buffer[BUFFER_SIZE];
    // create socket
    data_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (data_socket == -1)
        error_handler("data_socket");
    
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_NAME, sizeof(addr.sun_path)-1);

    ret = connect(data_socket, (const struct sockaddr *) &addr, sizeof(struct sockaddr_un));
    if (ret == -1)
        error_handler("connect");

    //  send arguments
    do{
        printf("Enter no to be sent to server: ");
        scanf("%d", &i);
        ret = write(data_socket, &i, sizeof(int));
        if(ret == -1){
            error_handler("write");
            break;
        }
        printf("Bytes sent: %d, data sent: %d\n", ret, i);
    } while(i);

    // request result
    memset(buffer, 0, BUFFER_SIZE);
    
    ret = read(data_socket, buffer, BUFFER_SIZE);
    if (ret == -1)
        error_handler("read");
    buffer[BUFFER_SIZE - 1] = '\0';

    printf("result : %s\n", buffer);
     
    //close socket
    close(data_socket);
    exit(EXIT_SUCCESS);
}
