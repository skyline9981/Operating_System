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
    int burstTime = 0;
    bool finished = false;
};

// sort by burstTime
bool cmpBurstTime(Process a, Process b) {
    return a.burstTime < b.burstTime;
}

void SJF(vector<Process> &vec, int numofprocess){
    int finished_process = 0;
    int timeCount = 0;
    vector <Process> que;

    while (finished_process != numofprocess) {
        int index = 0;

        if (!que.empty()) {
            int tmp_index = que[0].ProcessId;
            for (int i = 0; i < numofprocess; i++) {
                if (vec[i].ProcessId == tmp_index) {
                    index = i;
                    break;
                }
            }
            vec[index].waitingTime = timeCount - vec[index].arrivalTime;
            vec[index].TurnaroundTime = timeCount + vec[index].burstTime - vec[index].arrivalTime;
            timeCount += vec[index].burstTime;
            vec[index].finished = true;
            finished_process += 1;
        }

        que.clear();

        bool allFinished = true;

        for (int i = 0; i < numofprocess; ++i) {
            if (!vec[i].finished)
                allFinished = false;
            if (vec[i].arrivalTime <= timeCount && !vec[i].finished) {
                que.push_back(vec[i]);
            }
        }

        if (!allFinished && que.empty()) {
            for (int i = 0; i < numofprocess; ++i) {
                if (!vec[i].finished) {
                    timeCount = vec[i].arrivalTime;
                    que.push_back(vec[i]);
                }
            }
        }

        sort(que.begin(), que.end(), cmpBurstTime);
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

int main() {
    int numofprocess;
    cin >> numofprocess;
    vector <Process> vec(numofprocess);

    for (int i = 0; i < numofprocess; ++i) {
        vec[i].ProcessId = i;
        cin >> vec[i].arrivalTime;
    }

    for (int i = 0; i < numofprocess; ++i) {
        cin >> vec[i].burstTime;
    }

    SJF(vec, numofprocess);

    output(vec, numofprocess);

    return 0;
}
