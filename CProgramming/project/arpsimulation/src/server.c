#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <err.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SOCKET_NAME "/tmp/mysock.socket"
#define BUFFER_SIZE 128
#define LISTEN_BACKLOG 32
#define MAX_CLIENTS 32
#define error_handler(msg) \
    do {perror(msg); fprintf(stderr, "\n%s\n", strerror(errno)); exit(EXIT_FAILURE); } while (0)

/* function prototypes */
int find_max_fd(int master_socket_fd, int client_sockets[], int max_clients);
int add_client(int client_socket_fd, int client_sockets[], int max_clients);
void handle_client(int client_socket_fd, int client_sockets[], int index, char buffer[], int buffer_size);


int
main(void)
{
    int master_socket_fd;
    int client_socket_fd;
    int ret;
    char buffer[BUFFER_SIZE];
    fd_set read_fds;
    int client_sockets[MAX_CLIENTS];
    int max_fd;

    memset(client_sockets, -1, sizeof(client_sockets));
    
    // Unlink socket file if it exists
    unlink(SOCKET_NAME);

    /* create a local socket */

    master_socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(master_socket_fd == -1)
        error_handler("Connection Socket");
    printf("Master socket fd created.\n");

    /* create address for socket */
    struct sockaddr_un name;
    memset(&name, 0, sizeof(name));
    name.sun_family = AF_UNIX;
    strncpy(name.sun_path, SOCKET_NAME, sizeof(name.sun_path)-1);
    
    /* bind address to the local socket */
    ret = bind(master_socket_fd, (const struct sockaddr *)&name, sizeof(name));
    if(ret == -1)
        error_handler("bind");
    printf("master socket fd bind complete.\n");

    /* prepare for accepting connections */
    ret = listen(master_socket_fd, LISTEN_BACKLOG);
    if(ret == -1)
        error_handler("listen");
    printf("master socket listening.\n");

    /* main server loop */
    while(1){
        //initialize fd_set
        FD_ZERO(&read_fds);
        FD_SET(master_socket_fd, &read_fds);
        for(int i = 0; i < MAX_CLIENTS; ++i){
            if(client_sockets[i] != -1)
                FD_SET(client_sockets[i], &read_fds);
        }

        // find max_fd
        max_fd = find_max_fd(master_socket_fd, client_sockets, MAX_CLIENTS);

        // Wait for activity on any socket
        ret = select(max_fd+1, &read_fds, NULL, NULL, NULL);
        if(ret == -1)
            error_handler("select");

        // check for new connections
        if(FD_ISSET(master_socket_fd, &read_fds)){
            struct sockaddr_un client_addr;
            socklen_t addr_len = sizeof(client_addr);
            client_socket_fd = accept(master_socket_fd, (struct sockaddr *)&client_addr, &addr_len);
            if(client_socket_fd == -1)
                error_handler("client socket");
            ret = add_client(client_socket_fd, client_sockets, MAX_CLIENTS);
            if (ret == -1)
                error_handler("adding client_sockets");
        }
        
        // check data from clients
        for(int i = 0; i < MAX_CLIENTS; ++i){
            int sock = client_sockets[i];
            if(sock != -1 && FD_ISSET(sock, &read_fds)){
                handle_client(sock, client_sockets, i, buffer, BUFFER_SIZE);
            }
        }
    }
    
    /* cleanup before exit */
    for(int i = 0; i < MAX_CLIENTS; ++i){
        if(client_sockets[i] != -1)
            close(client_sockets[i]);
    }

    close(master_socket_fd);
    unlink(SOCKET_NAME);
    exit(EXIT_SUCCESS);
}
void
handle_client(int client_socket_fd, int client_sockets[], int index, char buffer[], int buffer_size)
{
    memset(buffer, 0, buffer_size); // Clear buffer
    int bytes_read = read(client_socket_fd, buffer, buffer_size - 1);
    if(bytes_read == -1){
        close(client_socket_fd);
        client_sockets[index] = -1;
        return; //continue the server loop and not exit on client termination or no read.
    } else if(bytes_read == 0){
        printf("client disconnected.\n");
        close(client_socket_fd);
        client_sockets[index] = -1;
        return;
    }
    buffer[bytes_read] = '\0';  // null terminate the buffer.
    printf("data received from client.\n");
    write(client_socket_fd, buffer, bytes_read);
    printf("echoed back to client.\n");
}

int 
find_max_fd(int master_socket_fd, int client_sockets[], int max_clients)
{
    int max_fd = master_socket_fd;
    for(int i = 0; i < max_clients ; ++i){
        if(client_sockets[i] != -1 && client_sockets[i] > master_socket_fd)
            max_fd = client_sockets[i];
    }
    return max_fd;
}

int 
add_client(int client_socket_fd, int client_sockets[], int max_clients)
{
    for(int i = 0; i < max_clients; ++i){
        if(client_sockets[i] == -1){
            client_sockets[i] = client_socket_fd;
            printf("client socket added at index %d.\n", i);
            return 0;
        }
    }
    return -1;  // no empty slot found.
}
