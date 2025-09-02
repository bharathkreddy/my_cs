# Networking
No layer is aware of layer above or below it.

1. Application layer
    - The application itself 
    - whatsapp, Ping, HTTP, all mobile apps etc.
    - generally session and presentation layers take care of encryption of decryption of data and are mixed in this and transport layer.
2. Transport layer
    - Responsible for Process to process delivery
    - UDP, TCP
3. Network Layer
    - Responsible for host/node to host/node delivery (server system to client system)
    - IP, IPv6
4. Data Link layer
    - Node to adjacent node (router to next router connected to it)
    - ethernet 
5. Physical layer. 


# Computer Architecture

APP <--> APP : IPC 
APP <--> Kernel : Netlinks skts, IOCTLS, Device Files, System Calls(malloc, free)
Kernel <--> Hardware : Device Drivers

IPC (inter process communication)
1. Unix domain sockets
2. Network sockets (different networks)
3. Message queue 
4. Shared Memory
5. Pipes (Outdated: not used in industry)
6. Signals

# 1. Sockets
- A bunch of socket based APIs
- Unix Domain sockets for processes on same machine, or Network sockets for processes running on different machines.
- Socket APIs use system calls to talk to the kernel.

### Steps
1. Remote the socker, if exists.
2. Create the unix socket *socket()*
3. Specify the socket name.
4. Bind the socket *bind()*
5. *listen()*
6. *accept()*
7. Read the data received on socket. *recvfrom()*
8. Send the result *sendto()*
9. *close* the data socket.
10. *close* the connection socket.
11. Remove the socket.
12. exit.

### client server message types
1. Connection Initiation Request (allways initiated by client, targeted to a server.) this causes a connection to be established with server.
2. Service Request Message (usual service requests from client to server, can be sent only once connection is fully established.)

### state machine of Socket based client server communication.
1. When server boots up, it creates a connection socket. This is also called **Master socket file descriptor** using *socket()*
    - In unix everything is a file. Think of unix providing same API for regardless where the stream of bytes is comming from, can be a file, a socket, a terminal etc.
    - Each process has a list of all files it uses, maintained by kernel. Kernel assigns an integer for each of these files, this no. is called *file Descriptor*. use `lsof -p <pid>` to see the process' list of file descriptors. 
2. *Master Socket File Descriptor* is mother of all *client handles*. Each time a client sends CIR, the M creates a client handle for the client, this handle is also called *data_sockets*. 
3. Once client handles are created for each client, server carries out data exchange with clients using client handle not M. Hence all SRM (service request messages) are sent by kernel to client handles.
4. *accept()* is the system call used on server side to create client handles.
5. Client handles are also called *communication file descriptors* or *data sockets*, 
6. M is called *Master socket file descriptor* or *Connection socket*.


