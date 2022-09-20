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

void FCFS(vector<Process> &vec, int numofprocess){
    int finished_process = 0;
    int timeCount = 0;

    while (finished_process != numofprocess) {
        bool all_Finished = true;
        int index = 0;
        for (int i = 0; i < numofprocess; ++i) {
            if (!vec[i].finished){
                all_Finished = false;
                index = i;
                break;
            }
        }
        if(!all_Finished){
            vec[index].waitingTime = timeCount - vec[index].arrivalTime;
            vec[index].TurnaroundTime = timeCount + vec[index].burstTime - vec[index].arrivalTime;
            timeCount += vec[index].burstTime;
            vec[index].finished = true;
            finished_process += 1;
        }
    }
        
}

void output(vector<Process> vec, int numofprocess){
    int waitTime_total = 0;
    int turnAroundTime_total = 0;

    for (int i = 0; i < numofprocess; ++i) {
        waitTime_total += vec[i].waitingTime;
        turnAroundTime_total += vec[i].TurnaroundTime;
        cout << vec[i].waitingTime << " " << vec[i].TurnaroundTime << endl;
    }
    cout << waitTime_total << endl;
    cout << turnAroundTime_total;
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

    FCFS(vec, numofprocess);
    output(vec, numofprocess);
    return 0;
}
