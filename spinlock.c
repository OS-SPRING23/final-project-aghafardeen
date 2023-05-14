#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>

#define SPINLOCK_INIT 0
#define SPINLOCK_LOCKED 1
void *thread_func(void *arg);
static unsigned int spinlock = SPINLOCK_INIT;

int main()
{
    pthread_t thread_id[10];
    int i;

    for (i = 0; i < 2; i++) {
        pthread_create(&thread_id[i], NULL, thread_func, NULL);
    }

    for (i = 0; i < 2; i++) {
        pthread_join(thread_id[i], NULL);
    }

    return 0;
}

void *thread_func(void *arg)
{
    while (syscall(335, &spinlock)) {
        
    }

    printf("Thread %ld acquired the spinlock\n", syscall(SYS_gettid));

    syscall(336, &spinlock);
   
    printf("Thread %ld released the spinlock\n", syscall(SYS_gettid));

    pthread_exit(NULL);
}
