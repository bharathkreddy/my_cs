/* takes a number from user and creates multiple threads that give back squres of the numbers in n, n-1,n-2 etc. reducer thread aggregates these and prints the sequence*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void thread_create(pthread_t *pthread_handle, int arg);
void *thread_callback(void *args);

int
main(void){
    int num; 
    printf("Number: ");
    scanf("%d", &num);

    pthread_t *threads = malloc((num+1)* sizeof(pthread_t));

    for(int i = 0; i <= num ; ++i){
        int n = i;
        thread_create(&threads[i], n);
    }
    
    for(int i = num; i >= 0; --i){
        void *thread_result = NULL;
        pthread_join(threads[i], &thread_result);
        if(thread_result){
            printf("%d\n", *(int*)thread_result);
            free(thread_result);
        } else {
            printf("Thread result not procured.\n");
        }
    } 
    free(threads);
    return 0;
}

void
thread_create(pthread_t *pthread_handle, int arg){
    int *pthread_arg = malloc(sizeof(int));
    *pthread_arg = arg;

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    int rc = pthread_create(
            pthread_handle,
            &attr,
            thread_callback,
            pthread_arg
            );
    if(rc != 0){
        printf("Error creating thread, errno = %d", rc);
        free(pthread_arg);
        exit(EXIT_FAILURE);
    }
    // after all pthread_create calls are done:
    pthread_attr_destroy(&attr);   // clean up the attribute object
}

void * 
thread_callback(void *args){
    int num = *(int *)args;
    free(args);
    int *result = malloc(sizeof(int));
    *result = num * 10;
    return (void *)result;
}
