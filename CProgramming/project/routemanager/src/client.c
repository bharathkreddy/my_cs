// client connects to a server who maintains a routing table. client can add, delete or update entries.
// client gets updates from server if routing table change is made by anyother client and hence all clients stay synchronised.


#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/un.h>

#define SOCKET_NAME "/tmp/mysock"
#define error_handler(msg) \
    do {perror(msg); exit(EXIT_FAILURE);} while(0)

void display_menu(void);
int get_user_choice(void);
void clear_input_buffer(void);
void handle_add_route(int data_socket, int choice);
void handle_update_route(int data_socket, int choice);
void handle_delete_route(int data_socket, int choice);
void handle_list_routes(int data_socket, int choice);
void handle_exit(int data_socket);
void get_user_input(const char* msg , char *src, size_t msg_size);
void send_data(int data_socket, const char* msg, size_t msg_size);
char buffer[128];

int 
main(void)
{
    int choice;
    int data_socket;
    struct sockaddr_un addr; 
    int ret;

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
    printf("Connected to routing server!\n");

    while(true){
        display_menu();
        choice = get_user_choice();
        switch(choice){
            case 1: handle_add_route(data_socket, choice); break;
            case 2: handle_update_route(data_socket, choice); break;
            case 3: handle_delete_route(data_socket, choice); break;
            case 4: handle_list_routes(data_socket, choice); break;
            case 5: handle_exit(data_socket); break;
            default: printf("Invalid choice");
        } 
    };

    exit(EXIT_SUCCESS);
}

void
clear_input_buffer (void)
{
    while ( getchar() != '\n' );
}

void 
display_menu(void)
{
    printf("\n=== Routing Table Management ===\n");
    printf("1. Add Route Entry\n");
    printf("2. Update Route Entry\n");
    printf("3. Delete Route Entry\n");
    printf("4. List All Routes\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

int
get_user_choice(void)
{
    int choice;
    scanf("%d", &choice);
    clear_input_buffer();
    return choice;
}

void
get_user_input(const char* msg , char *src, size_t msg_size)
{
    printf("%s", msg);
    if(fgets(src, msg_size, stdin) != NULL){
        // Remove new line from string
        src[strcspn(src, "\n")] = '\0';
    };
}

void
send_data(int data_socket, const char* msg, size_t msg_size)
{
    int ret;
    ret = -1;
    ret = write(data_socket, msg, msg_size);
    if(ret == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }
    printf("Data sent.\n");
}

void 
handle_add_route(int data_socket, int choice)
{
    char source[24];
    char destination[24];
    char interface[32];
    get_user_input("Enter source ip/mask: ", source, sizeof(source));
    get_user_input("Enter destination: ", destination, sizeof(destination));
    get_user_input("Enter interface: ", interface, sizeof(interface));
    sprintf(buffer, "%d:%s:%s:%s", choice, source, destination, interface);
    printf("sending to server : %d:%s:%s:%s\n", choice, source, destination, interface);
    send_data(data_socket, buffer, strlen(buffer));
    memset(buffer, 0, sizeof(buffer));
    int ret;
    ret = 0;
    ret = read(data_socket, buffer, sizeof(buffer));
    if(ret == -1) {
        error_handler("read back.");
    }
    printf("Server ack: %s\n", buffer);
    memset(buffer, 0, sizeof(buffer));
}

void 
handle_update_route(int data_socket, int choice)
{
    return;
}

void 
handle_delete_route(int data_socket, int choice)
{
    return;
}

void 
handle_list_routes(int data_socket, int choice)
{
    char buffer[1024];
    int ret;
    sprintf(buffer, "%d:", choice);
    printf("requesting route list");
    send_data(data_socket, buffer, strlen(buffer));
    memset(buffer, 0, sizeof(buffer));
    ret = read(data_socket, buffer, sizeof(buffer)-1);
    if (ret == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }
    buffer[ret] = '\0';  // Ensure string termination
    printf("Current routing table:\n%s\n", buffer);
}

void 
handle_exit(int data_socket)
{
    close(data_socket);
    printf("Client socket closed, client sutting down.\n");
    exit(EXIT_SUCCESS);
}
