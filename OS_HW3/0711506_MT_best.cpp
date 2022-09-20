#include <bits/stdc++.h>
#include <pthread.h>
#define fastio ios_base::sync_with_stdio(false),cin.tie(0)
#define ll long long

using namespace std;

int total_num=0;
vector<int> vec;
pthread_t id[7];

int low[7];
int high[7];

class struct_th {
public:
    pthread_t bubble_idx, merge_idx;
};

void *bubble_sort(void* pass);
void *merge(void* pass);

int main(int argc, const char * argv[]) {
    fastio;
    int in;
    while(cin >> in){
        vec.push_back(in);
        total_num++;
    }

    low[0] = 0;
    low[1] = high[0] = total_num / 4;
    low[2] = high[1] = total_num / 2;
    low[3] = high[2] = total_num * 3/4;
    high[3] = total_num;

    low[4] = 0;
    low[5] = high[4] = total_num / 2;
    high[5] = total_num;

    struct_th *total_thread[7];

    for (int i = 0; i < 7; i ++) {
        total_thread[i] = (struct_th*)malloc(sizeof(struct_th));
    }

    for (int i = 0; i < 4; i ++) {
        total_thread[i]->bubble_idx = i;
        pthread_create(&id[i], NULL,  bubble_sort, (void*)total_thread[i]);
    }

    total_thread[4]->bubble_idx = 0;
    total_thread[4]->merge_idx = 1;
    total_thread[5]->bubble_idx = 2;
    total_thread[5]->merge_idx = 3;
    total_thread[6]->bubble_idx = 4;
    total_thread[6]->merge_idx = 5;

    for(int i = 4; i < 7; i++){
        pthread_create(&id[i], NULL, merge, (void*)total_thread[i]);
    }

    pthread_join(id[6], NULL);

    for (int i = 0; i < total_num; i ++) {
        cout << vec[i] << ' ';
    }
    return 0;
}

void *bubble_sort(void* pass) {
    /* Sorting algorithm can be brute force methods, e.g., bubble sort */
    struct_th* thread_num = (struct_th*)pass;
    int low_b = low[thread_num->bubble_idx];
    int high_b = high[thread_num->bubble_idx];
    for (int i = low_b; i < high_b; i ++) {
        for (int j = i + 1; j < high_b; j ++) {
            if (vec[i] > vec[j]){
                int temp = vec[i];
                vec[i] = vec[j];
                vec[j] = temp;
            }   
        }
    }
}

void *merge(void* pass) {
    struct_th* thread_num = (struct_th*)pass;
    int bubble_idx = thread_num->bubble_idx;
    pthread_join(id[bubble_idx] ,NULL);

    int merge_idx = thread_num->merge_idx;
    pthread_join(id[merge_idx] ,NULL);
    
    vector<int> tmp_ans;
    int j = low[merge_idx];
    int i = low[bubble_idx];

    while (i < high[bubble_idx] && j < high[merge_idx]) {
        if (vec[i] < vec[j]){
            tmp_ans.push_back(vec[i++]);
        }
        else{
            tmp_ans.push_back(vec[j++]);
        }
    }

    while (j < high[merge_idx]){
        tmp_ans.push_back(vec[j++]);
    }

    while (i < high[bubble_idx]){
        tmp_ans.push_back(vec[i++]);
    }

    for (int i = 0; i < high[merge_idx] - low[bubble_idx]; i ++) {
        vec[low[bubble_idx] + i] = tmp_ans[i];
    }

}