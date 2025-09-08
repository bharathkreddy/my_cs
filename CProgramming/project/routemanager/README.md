# Project Breakdown: C Server-Client with Routing Table Synchronization

Here's a comprehensive stage-by-stage breakdown of your project with clear objectives and learning paths:

## Stage 1: Foundation - Basic AF_UNIX Socket Infrastructure

**Duration:** 1-2 days

**Objectives:**

- Understand AF_UNIX socket fundamentals and file system addressing[^1][^2]
- Implement basic server that can accept one client connection
- Learn socket creation, binding, listening, and accepting

**Key Learning Points:**

- Why AF_UNIX sockets use filesystem paths as addresses
- Understanding SOCK_STREAM for reliable, connection-oriented communication[^1]
- Error handling patterns in socket programming
- Resource cleanup (closing sockets, unlinking socket files)

**Deliverable:** Single-client server that can exchange basic messages with one client

## Stage 2: Multiplexing - Handling Multiple Clients

**Duration:** 2-3 days

**Objectives:**

- Implement I/O multiplexing using `select()`, `poll()`, or `epoll()` (Linux)[^3][^4]
- Allow server to handle exactly 3 concurrent client connections
- Understand non-blocking I/O and event-driven programming

**Key Learning Points:**

- Why multiplexing is superior to thread-per-connection for your use case[^5]
- File descriptor management and monitoring ready states[^3]
- Handling client connections and disconnections gracefully
- Managing connection lifecycle and cleanup

**Deliverable:** Server that simultaneously manages 3 client connections using a single process

## Stage 3: Routing Table Data Structure

**Duration:** 1-2 days

**Objectives:**

- Design and implement routing table data structure in C[^6][^7]
- Create functions for adding, deleting, and updating routing entries
- Implement table lookup and display functionality

**Key Learning Points:**

- Routing table components: source IP/mask, destination IP, outgoing interface[^7]
- IP address and subnet mask representation in C
- Dynamic memory management for table entries
- Search algorithms for routing table lookups

**Suggested Structure:**

```c
typedef struct routing_entry {
    char source_ip[^16];
    int subnet_mask;
    char dest_ip[^16];
    char interface[^32];
    struct routing_entry *next;
} routing_entry_t;
```

**Deliverable:** Complete routing table module with CRUD operations

## Stage 4: Message Protocol Design

**Duration:** 1 day

**Objectives:**

- Design message format for routing table operations
- Implement serialization/deserialization of routing table updates
- Define protocol for different message types (ADD, DELETE, UPDATE, SYNC)

**Key Learning Points:**

- Network byte order considerations
- Message framing and delimiting
- Protocol versioning and extensibility
- Error message handling

**Deliverable:** Protocol specification and message handling functions

## Stage 5: Server-Side Table Management

**Duration:** 2 days

**Objectives:**

- Integrate routing table with server socket handling
- Implement server commands for table manipulation
- Add input validation and error handling
- Create administrative interface (CLI or simple commands)

**Key Learning Points:**

- State management in network servers
- Input validation and sanitization
- Concurrent access considerations (even with single-threaded design)
- Logging and debugging capabilities

**Deliverable:** Server that can modify routing table through command interface

## Stage 6: Broadcast Synchronization Mechanism

**Duration:** 2-3 days

**Objectives:**

- Implement broadcast functionality to send updates to all connected clients[^8][^9]
- Ensure reliable delivery of routing table changes
- Handle partial client failures during broadcast

**Key Learning Points:**

- Broadcasting patterns in TCP-based systems[^10][^8]
- Maintaining client connection state
- Handling send failures and partial broadcasts
- Message queuing for unreachable clients

**Deliverable:** Server that automatically notifies all clients of routing table changes

## Stage 7: Client-Side Synchronization

**Duration:** 2 days

**Objectives:**

- Implement client-side routing table storage and updates
- Handle incoming synchronization messages from server
- Implement reconnection logic for dropped connections
- Add client-side table verification

**Key Learning Points:**

- Client state management and persistence
- Asynchronous message handling
- Connection recovery strategies
- Data consistency validation

**Deliverable:** Clients that maintain synchronized copies of server routing table

## Stage 8: Enhanced Features and Real-World Applications

**Duration:** 2-3 days

**Objectives:**

- Add sequence numbers for message ordering[^11]
- Implement basic authentication/authorization
- Add configuration file support
- Create comprehensive logging system
- Add performance monitoring

**Key Learning Points:**

- Distributed systems synchronization challenges[^11]
- Security considerations in network applications
- Configuration management patterns
- Performance monitoring and optimization
- Production-ready error handling

**Real-World Extensions:**

- Add support for routing table persistence (file/database)
- Implement backup server for high availability
- Add network partition detection and recovery
- Support for different routing protocols (static, dynamic)
- Integration with actual network interfaces


## Stage 9: Testing and Robustness

**Duration:** 1-2 days

**Objectives:**

- Create comprehensive test scenarios
- Test failure conditions (client crashes, network issues)
- Validate synchronization under various conditions
- Performance testing with rapid table updates

**Key Learning Points:**

- Distributed systems testing strategies
- Fault injection and recovery testing
- Load testing methodologies
- Debugging distributed applications

**Deliverable:** Robust, tested system ready for production-like scenarios

## Technical Architecture Notes:

**Communication Flow:**

1. Server maintains master routing table
2. Clients connect and receive initial table state
3. Server operations trigger immediate broadcast to all clients
4. Clients apply updates and acknowledge receipt
5. Server handles acknowledgment timeouts and retries

**Key Design Decisions:**

- Use AF_UNIX for same-machine optimization[^2][^1]
- Single-threaded server with multiplexing for simplicity
- Push-based synchronization for immediate consistency[^11]
- Structured logging for debugging distributed state issues

This progression takes you from basic socket programming through advanced distributed systems concepts, providing a solid foundation for real-world network application development.
<span style="display:none">[^12][^13][^14][^15][^17][^18][^19][^20][^21][^22]</span>

<div style="text-align: center">⁂</div>

[^1]: https://www.c-pointers.com/lsp/sockets/af_unix_tcp/select/select.html

[^2]: https://www.c-pointers.com/lsp/sockets/af_unix_tcp/Basic_example/Basic_example.html

[^3]: https://austingwalters.com/io-multiplexing/

[^4]: https://nima101.github.io/io_multiplexing

[^5]: https://long-zhou.github.io/2012/12/21/epoll-vs-kqueue.html

[^6]: https://vocal.media/education/distance-vector-routing-protocol-program-in-c

[^7]: https://www.geeksforgeeks.org/computer-networks/routing-tables-in-computer-network/

[^8]: https://forum.qt.io/topic/100682/how-to-send-a-message-from-a-tcpserver-to-all-connected-clients

[^9]: https://stackoverflow.com/questions/35381611/c-sockets-client-server-pthreads-server-broadcast

[^10]: https://www.codeproject.com/Articles/21398/Broadcasting-Using-Socket-Oriented-Approach

[^11]: https://www.geeksforgeeks.org/computer-networks/synchronization-in-distributed-systems/

[^12]: https://idiotdeveloper.com/tcp-client-server-implementation-in-c/

[^13]: https://www.ia.pw.edu.pl/~tkruk/edu/rso.b/lecture/pre/rso03_pre.pdf

[^14]: https://www.geeksforgeeks.org/computer-networks/simple-client-server-application-in-c/

[^15]: https://docs.oracle.com/cd/E19620-01/805-4041/6j3r8iu2l/index.html

[^16]: https://oasis.library.unlv.edu/cgi/viewcontent.cgi?article=4333\&context=rtds

[^17]: https://www.tutorialspoint.com/client-server-architecture-everything-you-should-know

[^18]: https://dev.to/nikos_katsanos/brushing-up-my-c-building-a-unix-domain-socket-client-server-part-i-324g

[^19]: https://www.geeksforgeeks.org/system-design/client-server-model/

[^20]: https://docs.python.org/3/library/select.html

[^21]: https://stackoverflow.com/questions/33595778/how-would-i-be-able-to-create-a-routing-table-lookup-in-c

[^22]: https://stackoverflow.com/questions/2347416/how-to-broadcast-a-message-in-a-network/2347450

