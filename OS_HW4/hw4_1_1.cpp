#include <bits/stdc++.h>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

#define llong long long
#define MAX_THREAD 4

int total_thread;
string input;
pthread_t thread_id[MAX_THREAD];
llong input_length,ans[3];
sem_t mux[3];

void *runner(void* data);

int main(){
    cin >> total_thread >> input_length >> input;
    for (int i=0; i<3; i++){
        sem_init(&mux[i], 0, 1);
    }
    for (int i=0; i<total_thread; ++i) {
        pthread_create(&thread_id[i], NULL, runner, (void*)(intptr_t)i);
    }
    for (int i=0; i<total_thread; ++i) {
        pthread_join(thread_id[i], NULL);
    }
    for (int i=0; i<3; ++i) {
        printf("%d: %lld\n", i, ans[i]);
    }
    return 0;
}

void *runner(void* data) {
    int tid = (intptr_t)data;
    llong left_bound = input_length * (tid / (double)total_thread);
    llong right_bound = input_length * ((tid + 1) / (double)total_thread);
    llong tmp;
    for (int i=left_bound; i<right_bound; ++i) {
        tmp = input[i] - '0';
        sem_wait(&mux[tmp]);
        ans[tmp]+=1;
        sem_post(&mux[tmp]);
    }
    return NULL;
}
