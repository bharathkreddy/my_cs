// server implementation - connects to one client at a time
// waits until client passes 0, until then keeps taking in ints and
// upon receiving 0, returns back sum of all the inputs.

#include <stdio.h>
#include <stdlib.h> //EXIT_FAILURE, 
#include <sys/socket.h> //needed for socket, bind.
#include <sys/un.h> // sockaddr_un
#include <errno.h> // errno, memset 
#include <string.h> //strncpy
#include <unistd.h> // unlink

#define BUFFER_SIZE 128
#define LISTEN_BACKLOG 3
#define SOCKET_NAME "/tmp/mysock"

# define handle_error(msg) \
    do {perror(msg); exit(EXIT_FAILURE);} while(0)

int 
main(void)
{
    int connection_socket;
    int data_socket;
    int ret; 
    int data;
    int result;
    char buffer[BUFFER_SIZE];
    struct sockaddr_un my_addr;

    // socket() creates an endpoint for communication and returns a file descriptor 
    // that refers to that endpoint.  The file descriptor returned by a successful call 
    // will be the lowest-numbered file descriptor not currently open for the process.
    // at this point this is just a naked socket without any address associated to it.

    unlink(SOCKET_NAME);  // in case socket already exists by program run the last time.
    connection_socket = socket(AF_UNIX, SOCK_STREAM, 0);

    if(connection_socket == -1) 
        handle_error("socket");

    printf("Master socket created, with file descriptor no: %d", connection_socket);

    // Lets create an address and use bind() system call to bind the file descriptor with an address.
    // A UNIX domain socket address is represented in the following structure:
    // struct sockaddr_un {
    //    sa_family_t sun_family;               /* AF_UNIX */
    //    char        sun_path[108];            /* Pathname */
    // };

    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sun_family = AF_UNIX;
    strncpy(my_addr.sun_path, SOCKET_NAME, sizeof(my_addr.sun_path)-1);  
    // -1 to leave space for null terminator in my_addr.

       
   //  When a socket is created with socket, it exists in a name space
   // (address family) but has no address assigned to it.  bind() 
   // assigns the address specified by addr to the socket referred to by
   // the file descriptor sockfd.  addrlen specifies the size, in bytes,
   // of the address structure pointed to by addr.  Traditionally, this
   // operation is called “assigning a name to a socket”.
   // &my_addr is pointer and bind fn accepts pointer to be casted as sockaddr and not sockaddr_un.

    ret = bind(connection_socket, (const struct sockaddr*) &my_addr, sizeof(my_addr));
    if(ret == -1)
        handle_error("bind");

    printf("bind() call successfull.\n");

    //  listen() marks the socket referred to by sockfd as a passive
    //  socket, that is, as a socket that will be used to accept incoming
    //  connection requests using accept().

    ret = listen(connection_socket, LISTEN_BACKLOG);
    if(ret == -1)
        handle_error("bind");

    printf("Socket now listening.\n");

    // accept() extracts first connection request from the LISTEN_BACKLOG and creates a new
    // connected socket, returns a new file descriptor for that new socket. Accept() blocks 
    // the caller until a connection is present.

    
    // Main loop for handling connections.
    
    for(;;){

        // wait for incomming connections
        data_socket = accept(connection_socket, NULL, NULL);
        if(data_socket == -1)
            handle_error("accept");
        
        printf("Connection accepted from client\n");
        result = 0;

        for(;;) {

            memset(buffer, 0, BUFFER_SIZE);
            printf("waiting for data from client.\n");

            ret = read(data_socket, buffer, BUFFER_SIZE);
            if(ret == -1)
                handle_error("read");
            
            memcpy(&data, buffer, sizeof(int));
            if(data == 0)
                break;

            result += data;
        }

        // send results

        memset(buffer, 0, BUFFER_SIZE);
        sprintf(buffer, "Result = %d", result);

        printf("Sending result to the client.\n");
        ret = write(data_socket, buffer, BUFFER_SIZE);
        if(ret == -1)
            handle_error("write");

        // close socket
        close(data_socket);
    }

    // close master socket
    close(connection_socket);
    printf("Connection closed.\n");

    // release resources
    unlink(SOCKET_NAME);
    exit(EXIT_SUCCESS);
}
