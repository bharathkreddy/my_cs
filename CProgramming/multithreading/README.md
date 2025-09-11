# MULTI THREADING
1. Each process has at least one thread called the main thread - i.e. a process is a main thread.
2. A thread can create other threads.
3. Point at which a thread creates another thread is called a `Fork Point`.
4. A thread is a basic unit of execution flow.
5. If main thread terminates all other threads also get terminated except when main thread terminates via `pthread_exit(0)`.
6. Every thread is identified by a data strcuture `pthread_t` defined in `pthread.h`. This data strcuture is popularly called a `thread handle`.
7. A new thread is created using `pthread_create` api.
8. Any thread can cancel any other thread. On receiving cancellation , the reciving thread terminates immediately. 
9. Threads terminate in these ways
    - Thread fn returns.
    - pthread_exit(0);
    - Thread cancellation.
10. Multiple threads of a process, share the same Virtual Address space of the process. Resources allocated by one thread is visible to other threads. These resources are 
    - heap memory
    - Sockets
    - file descriptors etc
    - Global variables.
11. Threads do not share their stack memory.
12. Kernel does not schedule processes, it schedules threads. It does so via its scheduling prolicy.
13. If a thread seg-faults, then entire process is terminated including all its threads.
14. Signals are delivered per process, not per thread.
15. When a thread is created, it uses pre-existing resources of main thread like 
    - page table (map of programs virtual address space to physical memory address space)
    - shared libraries which are loaded
    - Sockets which are open etc.
16. When thread dies, kernel doesnt have to clean up all of resources as the process might be using those. These might be resources like heap memory, opened files, IPCs, sockets etc. 
17. context switching is fast between threads than between processes as 
    - entire page table has to be flused and updated.
    - register cashes has to be flused and updated
    - Translation look aside buffers (TLB) has to be updated.
    - entire cpu context has to be saved (registers, stack and pointers) 
with thread switching none of these are required, it generally means stack pointers are updated and some registers change.
18. for inter-thread communication, IPC methods(sockets, msg queues, pipes and shared memory) are not the recommended way for data exchange. The preferre way is through callbacks/fn pointers. Reasons are :
    - very fast, because no actual transfer of data, but only transfer of computation.
    - no special attention is needed from kernel, completely run in user space, hence no kernel resource need to be explicitly created.
19. 

# CODE EXAMPLES
1. [hello world](./src/helloworld.c)
2. [joinable and detached threads](./src/joinable.c)
3. [program to take in a num (5) and spawn a thread for each n, n-1, n-2, ..., 0, each thread returns the number * 10 to reducer thread](./src/countdown.c) 
