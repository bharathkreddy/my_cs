#include <err.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SRC_LEN \
    24 /* includes space for terminating NUL: allows up to 23 chars + '\0' */
#define MASK_LEN 5 /* allows up to 4 chars + '\0' */
#define DEST_LEN 24
#define IFACE_LEN 7
#define SOCKET_NAME "/tmp/mysock.socket"
#define BUFFER_SIZE 128
#define LISTEN_BACKLOG 32
#define MAX_CLIENTS 32
#define error_handler(msg)                          \
    do {                                            \
        perror(msg);                                \
        fprintf(stderr, "\n%s\n", strerror(errno)); \
        exit(EXIT_FAILURE);                         \
    } while (0)

/* structs for route table as linked list */
struct Route {
    char *source;
    char *mask;
    char *destination;
    char *interface;
};

struct Node {
    struct Route route;
    struct Node *nextNode;
};

struct RouteList {
    int count;
    struct Node *head;
    struct Node *current;
};

/* function prototypes */
int find_max_fd(int master_socket_fd, int client_sockets[], int max_clients);
int add_client(int client_socket_fd, int client_sockets[], int max_clients, int client_pids[], bool is_intialized[]);
void handle_client(int client_socket_fd, int client_sockets[], int index,
                   char buffer[], int buffer_size, struct RouteList *routelist,
                   pid_t client_pids[], bool is_intialized[]);
void add_route(struct RouteList *routelist, int client_sockets[],
               int max_clients);
void delete_route(struct RouteList *routelist, int client_sockets[],
                  int max_clients);
void display_route(struct RouteList *routelist);
void ammend_route(struct RouteList *routelist, int client_sockets[],
                  int max_clients);
void cleanup(struct RouteList *routelist);
void broadcast_message(const char *msg, int client_sockets[], int max_clients);
void display_pid(int client_pids[], int max_clients);

int main(void) {
    int master_socket_fd;
    int client_socket_fd;
    int ret;
    char buffer[BUFFER_SIZE];
    fd_set read_fds;
    int client_sockets[MAX_CLIENTS];
    pid_t client_pids[MAX_CLIENTS];
    bool is_intialized[MAX_CLIENTS];
    int max_fd;

    /* initialize routing table */
    struct RouteList *routelist;
    routelist = malloc(sizeof(struct RouteList));
    routelist->count = 0;
    routelist->head = NULL;
    routelist->current = NULL;

    // initialize client_sockets , pids and initialized arrays
    for (int i = 0; i < MAX_CLIENTS; ++i) {
        client_sockets[i] = -1;
        client_pids[i] = -1;
        is_intialized[i] = false;
    }

    // Unlink socket file if it exists
    unlink(SOCKET_NAME);

    /* create a local socket */
    master_socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (master_socket_fd == -1) error_handler("Connection Socket");
    printf("Master socket fd created.\n");

    /* create address for socket */
    struct sockaddr_un name;
    memset(&name, 0, sizeof(name));
    name.sun_family = AF_UNIX;
    strncpy(name.sun_path, SOCKET_NAME, sizeof(name.sun_path) - 1);

    /* bind address to the local socket */
    ret = bind(master_socket_fd, (const struct sockaddr *)&name, sizeof(name));
    if (ret == -1) error_handler("bind");
    printf("master socket fd bind complete.\n");

    /* prepare for accepting connections */
    ret = listen(master_socket_fd, LISTEN_BACKLOG);
    if (ret == -1) error_handler("listen");
    printf("master socket listening.\n");

    /* main server loop */
    while (1) {
        // ROUTING MENU
        printf("\n\n====ROUTING TABLE MENU====\n");
        printf("type in below commands for routing table.\n");
        printf("ADD ROUTE <- to add a route.\n");
        printf("DELETE ROUTE <- to delete a route/\n");
        printf("DISPLAY ROUTE <- to display the routing table.\n");
        printf("AMMEND ROUTE <- to ammend an existing route.\n");
        printf("DISPLAY PID <- to see pids of all connected clients.\n");

        // initialize fd_set
        FD_ZERO(&read_fds);
        FD_SET(master_socket_fd, &read_fds);
        FD_SET(STDIN_FILENO,
               &read_fds);  // <-- also watch server admin input on stdin
        for (int i = 0; i < MAX_CLIENTS; ++i) {
            if (client_sockets[i] != -1) FD_SET(client_sockets[i], &read_fds);
        }

        // find max_fd
        max_fd = find_max_fd(master_socket_fd, client_sockets, MAX_CLIENTS);

        // Wait for activity on any socket
        ret = select(max_fd + 1, &read_fds, NULL, NULL, NULL);
        if (ret == -1) error_handler("select");

        // check for new connections
        if (FD_ISSET(master_socket_fd, &read_fds)) {
            struct sockaddr_un client_addr;
            socklen_t addr_len = sizeof(client_addr);
            client_socket_fd = accept(
                master_socket_fd, (struct sockaddr *)&client_addr, &addr_len);
            if (client_socket_fd == -1) error_handler("client socket");
            ret = add_client(client_socket_fd, client_sockets, MAX_CLIENTS, client_pids, is_intialized);
            if (ret == -1) error_handler("adding client_sockets");
        }

        // check data from clients
        for (int i = 0; i < MAX_CLIENTS; ++i) {
            int sock = client_sockets[i];
            if (sock != -1 && FD_ISSET(sock, &read_fds)) {
                handle_client(sock, client_sockets, i, buffer, BUFFER_SIZE,
                              routelist, client_pids, is_intialized);
            }
        }

        // check for admin input via stdin
        if (FD_ISSET(STDIN_FILENO, &read_fds)) {
            memset(buffer, 0, BUFFER_SIZE);
            fgets(buffer, BUFFER_SIZE, stdin);
            buffer[strcspn(buffer, "\n")] = '\0';  // Remove newline
            printf("STDIN :%s\n", buffer);
            if (strcmp(buffer, "ADD ROUTE") == 0)
                add_route(routelist, client_sockets, MAX_CLIENTS);
            if (strcmp(buffer, "DELETE ROUTE") == 0)
                delete_route(routelist, client_sockets, MAX_CLIENTS);
            if (strcmp(buffer, "DISPLAY ROUTE") == 0) display_route(routelist);
            if (strcmp(buffer, "AMMEND ROUTE") == 0)
                ammend_route(routelist, client_sockets, MAX_CLIENTS);
            if (strcmp(buffer, "DISPLAY PID") == 0)
                display_pid(client_pids, MAX_CLIENTS);
        }
    }

    /* cleanup before exit */
    for (int i = 0; i < MAX_CLIENTS; ++i) {
        if (client_sockets[i] != -1) close(client_sockets[i]);
    }

    cleanup(routelist);
    close(master_socket_fd);
    unlink(SOCKET_NAME);
    exit(EXIT_SUCCESS);
}

void handle_client(int client_socket_fd, int client_sockets[], int index,
                   char buffer[], int buffer_size, struct RouteList *routelist,
                   pid_t client_pids[], bool is_intialized[]) {
    memset(buffer, 0, buffer_size);  // Clear buffer
    int bytes_read = read(client_socket_fd, buffer, buffer_size - 1);
    if (bytes_read == -1) {
        close(client_socket_fd);
        client_sockets[index] = -1;
        client_pids[index] = -1;
        is_intialized[index] = false;
        return;  // continue the server loop and not exit on client termination
                 // or no read.
    } else if (bytes_read == 0) {
        printf("client disconnected.\n");
        close(client_socket_fd);
        client_sockets[index] = -1;
        client_pids[index] = -1;
        is_intialized[index] = false;
        return;
    }
    buffer[bytes_read] = '\0';  // null terminate the buffer.
    if (!is_intialized[index]) {
        if (strncmp(buffer, "PID:", 4) == 0) {
            client_pids[index] = atoi(buffer + 4);
            printf("Received PID %d from client at index %d.\n",
                   client_pids[index], index);

            // send table dump as multiple a: messages
            struct Node *temp = routelist->head;
            while (temp != NULL) {
                char msg[BUFFER_SIZE];
                sprintf(msg, "a:%s:%s:%s:%s", temp->route.source,
                        temp->route.mask, temp->route.destination,
                        temp->route.interface);
                int len = strlen(msg);
                int bytes_written = write(client_socket_fd, msg, len);
                if (bytes_written == -1 || bytes_written != len) {
                    fprintf(stderr, "write error on fd %d: %s\n",
                            client_socket_fd, strerror(errno));
                    close(client_socket_fd);
                    client_sockets[index] = -1;
                    client_pids[index] = -1;
                    is_intialized[index] = false;
                    return;
                }
                temp = temp->nextNode;
            }
            printf("Sent routing table dump to new client.\n");
            is_intialized[index] = true;
        } else {
            printf("Invalid PID from client.\n");
        }
    }
}

int find_max_fd(int master_socket_fd, int client_sockets[], int max_clients) {
    int max_fd = master_socket_fd;
    if (STDIN_FILENO > max_fd) max_fd = STDIN_FILENO;
    for (int i = 0; i < max_clients; ++i) {
        if (client_sockets[i] != -1 && client_sockets[i] > max_fd)
            max_fd = client_sockets[i];
    }
    return max_fd;
}

int add_client(int client_socket_fd, int client_sockets[], int max_clients, int client_pids[], bool is_intialized[]) {
    for (int i = 0; i < max_clients; ++i) {
        if (client_sockets[i] == -1) {
            client_sockets[i] = client_socket_fd;
            client_pids[i] = -1;
            is_intialized[i] = false;
            printf("client socket added at index %d.\n", i);
            return 0;
        }
    }
    return -1;  // no empty slot found.
}

void add_route(struct RouteList *routelist, int client_sockets[],
               int max_clients) {
    struct Node *temp;
    temp = malloc(sizeof(struct Node));
    if (temp == NULL) error_handler("Failed to allocate memory.\n");

    temp->route.source = malloc(SRC_LEN);
    temp->route.mask = malloc(MASK_LEN);
    temp->route.destination = malloc(DEST_LEN);
    temp->route.interface = malloc(IFACE_LEN);
    if (!temp->route.source || !temp->route.mask || !temp->route.destination ||
        !temp->route.interface) {
        free(temp->route.source);
        free(temp->route.mask);
        free(temp->route.destination);
        free(temp->route.interface);
        free(temp);
        error_handler("failed to allocate memory.");
    }

    printf("Enter information to add a route.\n");
    printf("SOURCE >");
    if (fgets(temp->route.source, SRC_LEN, stdin) == NULL) {
        fprintf(stderr, "Error reading source\n");
        free(temp->route.source);
        free(temp->route.mask);
        free(temp->route.destination);
        free(temp->route.interface);
        free(temp);
        return;
    }
    temp->route.source[strcspn(temp->route.source, "\n")] = '\0';

    printf("MASK >");
    if (fgets(temp->route.mask, MASK_LEN, stdin) == NULL) {
        fprintf(stderr, "Error reading mask\n");
        free(temp->route.source);
        free(temp->route.mask);
        free(temp->route.destination);
        free(temp->route.interface);
        free(temp);
        return;
    }
    temp->route.mask[strcspn(temp->route.mask, "\n")] = '\0';

    printf("DESTINATION >");
    if (fgets(temp->route.destination, DEST_LEN, stdin) == NULL) {
        fprintf(stderr, "Error reading destination\n");
        free(temp->route.source);
        free(temp->route.mask);
        free(temp->route.destination);
        free(temp->route.interface);
        free(temp);
        return;
    }
    temp->route.destination[strcspn(temp->route.destination, "\n")] = '\0';

    printf("INTERFACE >");
    if (fgets(temp->route.interface, IFACE_LEN, stdin) == NULL) {
        fprintf(stderr, "Error reading interface\n");
        free(temp->route.source);
        free(temp->route.mask);
        free(temp->route.destination);
        free(temp->route.interface);
        free(temp);
        return;
    }
    temp->route.interface[strcspn(temp->route.interface, "\n")] = '\0';

    temp->nextNode = NULL;
    if (routelist->head == NULL) {
        routelist->head = temp;
        routelist->current = temp;
    } else {
        routelist->current->nextNode = temp;
        routelist->current = temp;
    }
    routelist->count++;
    char msg[BUFFER_SIZE] = {0};
    sprintf(msg, "a:%s:%s:%s:%s", temp->route.source, temp->route.mask,
            temp->route.destination, temp->route.interface);
    broadcast_message(msg, client_sockets, max_clients);
}

void delete_route(struct RouteList *routelist, int client_sockets[],
                  int max_clients) {
    char source[SRC_LEN];
    printf("Enter Source of route you want to delete.\n");
    printf("SOURCE >");
    fgets(source, sizeof(source), stdin);
    source[strcspn(source, "\n")] = '\0';

    struct Node *temp = routelist->head;
    struct Node *prev = NULL;
    while (temp != NULL && strcmp(temp->route.source, source) != 0) {
        prev = temp;
        temp = temp->nextNode;
    }
    if (temp == NULL) {
        printf("Route not found.\n");
        return;
    }

    if (prev == NULL) {
        routelist->head = temp->nextNode;
    } else {
        prev->nextNode = temp->nextNode;
    }
    if (routelist->current == temp) {
        routelist->current = routelist->head;
    }
    free(temp->route.source);
    free(temp->route.mask);
    free(temp->route.destination);
    free(temp->route.interface);
    free(temp);
    routelist->count--;
    printf("Route deleted successfully.\n");
    char msg[BUFFER_SIZE] = {0};
    sprintf(msg, "d:%s", source);
    broadcast_message(msg, client_sockets, MAX_CLIENTS);
}

void display_route(struct RouteList *routelist) {
    if (routelist->head == NULL) {
        printf("Routing table is empty.\n");
        return;
    }
    printf("Routing Table (%d entries):\n", routelist->count);
    printf("SOURCE\t\tMASK\tDESTINATION\tINTERFACE\n");
    struct Node *current = routelist->head;
    while (current != NULL) {
        printf("%s\t\t%s\t%s\t\t%s\n", current->route.source,
               current->route.mask, current->route.destination,
               current->route.interface);
        current = current->nextNode;
    }
}

void ammend_route(struct RouteList *routelist, int client_sockets[],
                  int max_clients) {
    if (routelist->head == NULL) {
        printf("Routing table is empty.\n");
        return;
    }
    char source[SRC_LEN];
    printf("Enter source address to amend: ");
    if (fgets(source, SRC_LEN, stdin) == NULL) {
        fprintf(stderr, "Error reading source\n");
        return;
    }
    source[strcspn(source, "\n")] = '\0';

    struct Node *current = routelist->head;
    while (current != NULL && strcmp(current->route.source, source) != 0) {
        current = current->nextNode;
    }
    if (current == NULL) {
        printf("Route not found.\n");
        return;
    }

    printf("Enter new information for route.\n");
    printf("SOURCE >");
    if (fgets(current->route.source, 23, stdin) == NULL) {
        fprintf(stderr, "Error reading source\n");
        return;
    }
    current->route.source[strcspn(current->route.source, "\n")] = '\0';

    printf("MASK >");
    if (fgets(current->route.mask, MASK_LEN, stdin) == NULL) {
        fprintf(stderr, "Error reading mask\n");
        return;
    }
    current->route.mask[strcspn(current->route.mask, "\n")] = '\0';

    printf("DESTINATION >");
    if (fgets(current->route.destination, DEST_LEN, stdin) == NULL) {
        fprintf(stderr, "Error reading destination\n");
        return;
    }
    current->route.destination[strcspn(current->route.destination, "\n")] =
        '\0';

    printf("INTERFACE >");
    if (fgets(current->route.interface, IFACE_LEN, stdin) == NULL) {
        fprintf(stderr, "Error reading interface\n");
        return;
    }
    current->route.interface[strcspn(current->route.interface, "\n")] = '\0';
    printf("Route amended successfully.\n");
    char msg[BUFFER_SIZE] = {0};
    sprintf(msg, "c:%s:%s:%s:%s", current->route.source, current->route.mask,
            current->route.destination, current->route.interface);
    broadcast_message(msg, client_sockets, MAX_CLIENTS);
}

void broadcast_message(const char *msg, int client_sockets[], int max_clients) {
    for (int i = 0; i < max_clients; i++) {
        if (client_sockets[i] != -1) {
            int bytes_written = write(client_sockets[i], msg, strlen(msg));
            if (bytes_written == -1 || bytes_written != strlen(msg)) {
                fprintf(stderr, "broadcast error on fd %d: %s",
                        client_sockets[i], msg);
            }
        }
    }
    printf("Broadcasted update %s\n", msg);
}

void cleanup(struct RouteList *routelist) {
    struct Node *temp = routelist->head;
    while (temp != NULL) {
        struct Node *tempnext = temp->nextNode;
        free(temp->route.source);
        free(temp->route.destination);
        free(temp->route.mask);
        free(temp->route.interface);
        free(temp);
        temp = tempnext;
    }
    free(routelist);
}

void display_pid(int client_pids[], int max_clients) {
    printf("\nList of client pids.\n");
    for (int i = 0; i < max_clients; i++) {
        if (client_pids[i] != -1) printf("%d: %d\n", i, client_pids[i]);
    }
}
