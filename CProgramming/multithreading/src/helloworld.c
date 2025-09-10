/*
 * compile using :
 * gcc -Wall -Wextra -pedantic -std=c11 -Wstrict-prototypes -g -c src/helloworld.c -o obj/helloworld.o
 * gcc -g obj/helloworld.o -o run/helloworld -lpthread
 * Run : ./hello_world
 */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> /* for pause and sleep */
#include <errno.h> /* for using global errno */

/* A thread callback fn must have following prototypes
 * void *(*thread_fn)(void *)
 */
static void *thread_callback(void *arg) {
    /* cast the void pointer to chars */
    char *input = (char *)arg;
    while (1) {
        printf("from callback: %s\n", input);
        sleep(1);
    }
}

void thread_create(void) {
    pthread_t pthread1;

    /* has to be from heap or outside function stack */
    static char *thread_input1 = "this is thread 1.";

    /* Return 0 on success, otherwise returns errorcode, all
     * pthread functions return -ve error code on failure, they
     * do not set global 'errno' variable */
    int rc = pthread_create(
        &pthread1,       /* address of pthread_t */
        NULL,            /* null means default initialization of thread */
        thread_callback, /* function that the thread will call */
        (void *)thread_input1); /* args passed to call back function */
    
    if(rc != 0){
        printf("Error occurred, thread could not be created, errno = %d\n", rc);
		exit(EXIT_FAILURE);
    }
}

int main(void) {
    printf("this is main thread.\n");
    thread_create();
    printf("Main thread pausing.\n");
    pause();
    return 0;
}
