# MULTI THREADING
1. Each process has at least one thread called the main thread - i.e. a process is a main thread.
2. A thread can create other threads.
3. Point at which a thread creates another thread is called a `Fork Point`.
4. A thread is a basic unit of execution flow.
5. If main thread terminates all other threads also get terminated except when main thread terminates via `pthread_exit(0)`.
6. Every thread is identified by a data strcuture `pthread_t` defined in `pthread.h`. This data strcuture is popularly called a `thread handle`.
7. A new thread is created using `pthread_create` api.
8. Any thread can cancel any other thread. On receiving cancellation , the reciving thread terminates immediately. 
9. 
