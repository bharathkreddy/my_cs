/* joinable and detached threads */
/* gcc -Wall -Wextra -pedantic -std=c11 -Wstrict-prototypes -g -c src/joinable.c -o obj/joinable.o */
/* gcc -g obj/joinable.o -o run/joinable.bin -lpthread */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void thread_create(pthread_t *pthread_handle, int arg);
void *thread_callback(void* arg);

int
main(void){
    
    /* step1: create 2 threads */
    pthread_t thread2;
    pthread_t thread3;

    thread_create(&thread2, 10); 
    thread_create(&thread3, 2); 
    
    printf("Main thread blocked on thread 2 join now.\n");
    void *thread_result2 = NULL; /* thread callback returns void pointer */
    pthread_join(thread2, &thread_result2);
    if(thread_result2){
        printf("return from thread 2: %d\n", *(int*)thread_result2);
        free(thread_result2); /* result was calloc's so free that */
        thread_result2 = NULL;
    }

    printf("Main thread blocked on thread 3 join now.\n");
    void *thread_result3 = NULL; /* thread callback returns void pointer */
    pthread_join(thread3, &thread_result3);
    if(thread_result3){
        printf("return from thread 3: %d\n", *(int*)thread_result3);
        free(thread_result3); /* result was calloc's so free that */
        thread_result3 = NULL;
    }

    return 0;
}

void 
thread_create(pthread_t *pthread_handle, int arg){
    /* we have to pass args from a heap memory and not stack memory
     * this is because stack would be destroyed once this fn returns
     * we create a pointer to heap and pointer points to arg value */
    int *thread_arg = calloc(1, sizeof(int));
    *thread_arg = arg;
    
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE /* PTHREAD_CREATE_DETACHED  */);

    int rc = pthread_create(
            pthread_handle,
            &attr,
            thread_callback,
            (void*)thread_arg
            );

    if(rc != 0){
        printf("Error creating thread, errno = %d", rc);
        exit(EXIT_FAILURE);
    }
}

void *
thread_callback(void *args){
    /* cast args from void to (int *), and then derefernce it with '*' */
    int time = *(int *) args; 

    /* we dont need args anymore so free the memory */
    free(args);

    /* thread work */
    int rc = 0;
    while(rc != time){
        printf("Thread with arg (%d) doing work\n", time);
        sleep(1);
        rc++;
    };

    /* we need to return a pointer, hence cant be a stack memory
     * hence we allocate heap memory and return it */
    int *result = calloc(1, sizeof(int));
    *result = time * time;
    return (void *)result;
}
