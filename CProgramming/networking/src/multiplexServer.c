// server with multiplexing capability
// Multiple clients can connect and server maintains state of each client connector.


#include <stdio.h>
#include <errno.h>

#define MAX_CLIENT_SUPPORTED 2

#define SOCKET_NAME "/temp/mysock"
#define BUFFER_SIZE 128
#define error_handler(msg)\
    do(perror(msg); exit();) while(0);

//An array of file descriptors which the server process uses
//to talk to connected clients, it also has master socket file descriptor.

int monitored_fd_set[MAX_CLIENT_SUPPORTED];

// each connected clients intermediary results are maintained here
int client_result[MAX_CLIENT_SUPPORTED];

//remove all FDs, if any from thie array

static void
initialize_monitor_fd_set(){
    for(int i = 0; i < MAX_CLIENT_SUPPORTED; i++)
        monitored_fd_set[i] = -1;
}

// Add a new FD to monitored_fd_set array
static void
add_to_monitored_fd_set(int skt_fd){
    for(int i = 0; i < MAX_CLIENT_SUPPORTED; i++){
        if(monitored_fd_set[i] != -1)
            continue;
        monitored_fd_set[i] = skt_fd;
        break;
    }
}

// Remove a FD from monitored_fd_set
static void
remove_from_monitored_fd_set(int skt_fd){
    for(int i = 0; i < MAX_CLIENT_SUPPORTED; i++){
        if(monitored_fd_set[i] == skt_fd)
            monitored_fd_set[i] = -1;
    }
}



int
main(void)
{

}
