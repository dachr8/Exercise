#include <stdio.h>
#include <windows.h>
#include <pthread.h>

void *thr_fn(void *arg) {
    printf("hThread is running\n");
}

int main(void) {
    pthread_t ntid;

    pthread_create(&ntid, NULL, thr_fn, NULL);

    printf("main thread is running\n");

    pthread_join(ntid, NULL);

    return 0;
}