#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Process{
    int ProcessId = 0;
    int waitingTime = 0;
    int TurnaroundTime = 0;
    int arrivalTime = 0;
    int initialArrivalTime = 0;
    int burstTime = 0;
    int proceedTime = 0;
    bool finished = false;
};

bool cmp_arrivalTime(const Process &a, const Process &b) {
    return (a.arrivalTime < b.arrivalTime) || ((a.arrivalTime == b.arrivalTime) && (a.proceedTime < b.proceedTime));
}

void RoundRobin(vector<Process> &vec, int numofprocess, int quantum){
    int finished_process = 0;
    int timeCount = 0;
    int tmpIndex = 0;

    vector <Process> que = vec;

    while (finished_process != numofprocess) {
        sort(que.begin(), que.end(), cmp_arrivalTime);
        int tt_index;
        int selectedId = -1;
        for (int i = 0; i < numofprocess; i++) {
            if (!que[i].finished) {
                tt_index = que[i].ProcessId;
                for (int j = 0; j < numofprocess; j++) {
                    if (vec[j].ProcessId == tt_index) {
                        selectedId = j;
                        break;
                    }
                }
                tmpIndex = i;
                break;
            }
        }
        if (selectedId == -1) {
            timeCount = que[0].arrivalTime;
            selectedId = que[0].ProcessId;
            tmpIndex = 0;
        }
        que[tmpIndex].proceedTime += 1;
        vec[selectedId].waitingTime += timeCount - que[tmpIndex].arrivalTime;
        if (vec[selectedId].burstTime <= quantum) {
            timeCount += vec[selectedId].burstTime;
            vec[selectedId].TurnaroundTime = timeCount - vec[selectedId].initialArrivalTime;
            que[tmpIndex].finished = true;
            finished_process += 1;
        }
        else {
            timeCount += quantum;
            vec[selectedId].burstTime -= quantum;
            que[tmpIndex].arrivalTime = timeCount;
        }
    }
    
}

void output(vector<Process> vec, int numofprocess){
    int waitingTime_total = 0;
    int TurnAroundTime_total = 0;

    for (int i = 0; i < numofprocess; ++i) {
        waitingTime_total += vec[i].waitingTime;
        TurnAroundTime_total += vec[i].TurnaroundTime;
        cout << vec[i].waitingTime << " " << vec[i].TurnaroundTime << endl;
    }
    cout << waitingTime_total << endl;
    cout << TurnAroundTime_total;
}

int main(){

    int numofprocess;
    cin>>numofprocess;
    vector<Process> vec(numofprocess);

    for(int i=0;i<numofprocess;i++){
        cin >> vec[i].arrivalTime;
        vec[i].ProcessId = i;
        vec[i].initialArrivalTime = vec[i].arrivalTime;
    }

    for(int i=0;i<numofprocess;i++){
        cin >> vec[i].burstTime;
    }

    int quantum;
    cin >> quantum;

    RoundRobin(vec, numofprocess, quantum);

    output(vec, numofprocess);

    return 0;
}
