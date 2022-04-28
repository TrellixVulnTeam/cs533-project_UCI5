#include <stdio.h>
#include <stdbool.h>
#include <netdb.h>
#include <stdint.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <time.h>
#include <sys/select.h>
#include <pthread.h>
#include <unistd.h>
typedef uint64_t pktlab_time_t;
void *thread(void *arg) {
    printf("this is thread %p\n", arg);
    return NULL;
}

void parent(void) { printf("this is the parent\n"); }

void child(void) { printf("this is the child\n"); }

int main() {
    // pthread_t id[10];
    // int err;

    // for (int i = 0; i < 10; ++i) {
    //     err = pthread_create(&id[i], NULL, thread, (void *)i + 1);
    //     if (err) {
    //         perror("pthread create");
    //     }
    // }

    // for (int i = 0; i < 10; ++i) {
    //     pthread_join(id[i], NULL);
    // }

    // return 0;

    printf("hello world!\n");
    volatile int32_t i[16] = {};
    // i[0] = 1;
    __asm__ volatile("clflush (%0)" ::"r"(&i[0]));

    printf("hello world %d %d!\n", i[0], i[1]);
    // printf("hello world2!\n");
    // printf("hello world3!\n");
    // printf("hello world4!\n");
    return 0;

    if (fork()) {
        parent();
    } else {
        child();
    }
    return 0;
}