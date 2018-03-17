#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <semaphore.h>


#define M 10
#define N 10000
static int numbers[N];

sem_t sema[M];

void * print(void * i) {
    for (int k = *(int*)i; k < N; k += M) {
        sem_wait(&sema[*(int*)i]);
        printf("%d %d\n", *(int*)i, k);
        sem_post(&sema[((*(int*)i) + 1) % M]);
    }
}
int main() {
    pthread_t t [M];
    for (int i = 1; i < M; i++) {
        sem_init(&sema[i], 0, 0);
    }
    sem_init(&sema[0], 0, 1);

    for(int i=0;i<M;i++){
        int * d = malloc (sizeof(int));
        *d = i;
        pthread_create(&t[i], NULL, print, (void*) d);
    }
    pthread_exit(NULL);
}
