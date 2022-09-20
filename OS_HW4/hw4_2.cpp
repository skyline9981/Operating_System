#include <bits/stdc++.h>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

#define INTERVAL 100000
#define llong long long
#define MAX_THREAD 4

int total_thread;
llong test_point, out_get = 0;
sem_t mux;
pthread_t thread_id[MAX_THREAD];
void *runner(void* data);

int main(){
    scanf("%d %lld", &total_thread, &test_point);
    
    sem_init(&mux, 0, 1);

    for (int i=0; i < total_thread; ++i) {
        pthread_create(&thread_id[i], NULL, runner, (void*)(intptr_t)i);
    }

    for (int i=0; i<total_thread; ++i) {
        pthread_join(thread_id[i], NULL);
    }

    double pi = (double)(out_get * 4) / test_point;
    printf("get: %lld\n", out_get);
    printf("Pi: %.5lf\n", pi);

    return 0;
}

void *runner(void* data){
    int thread_id = (intptr_t)data;
    srand(time(NULL));
    double rand_x;
    double rand_y;

    llong test = test_point / total_thread;
    while(test--){
        rand_x = double(rand() % (INTERVAL + 1)) / INTERVAL;
        rand_y = double(rand() % (INTERVAL + 1)) / INTERVAL;
        double origin = rand_x * rand_x + rand_y * rand_y;
        if (origin <= 1){
            sem_wait(&mux);
            out_get++;
            sem_post(&mux);
        }
    }
    return NULL;
}
