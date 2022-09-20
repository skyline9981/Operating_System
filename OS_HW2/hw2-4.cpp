#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Process {
    int ProcessId = 0;
    int arrivalTime = 0;
    int burstTime = 0;
    int proceedTime = 0;
    int waitingTime = 0;
    int TurnaroundTime = 0;
};

bool cmp_burstTime(Process a, Process b) {
    if(a.burstTime == b.burstTime){
        return a.arrivalTime < b.arrivalTime;
    }else{
        return a.burstTime < b.burstTime;
    }
}

void output(vector<Process>& vec, int numofprocess){
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


int main(){    
    int numofprocess;
    cin >> numofprocess;
    vector<Process> vec(numofprocess);
    for(int i = 0; i < numofprocess; i++){
        cin >> vec[i].arrivalTime;
        vec[i].ProcessId = i;
        vec[i].proceedTime = 0;
    }
    for(int i = 0; i < numofprocess; i++){
        cin >> vec[i].burstTime;
    }
    int quantum;
    cin >> quantum;

    int timeCount = vec[0].arrivalTime;
    int current_quan = 0;
    int unfinishedprocess = vec.size();

    vector<Process> First_Level;
    vector<Process> Second_Level;

    First_Level.push_back(vec[0]);

    int unfinished = -1;

    while(unfinishedprocess > 0){
        if(First_Level.size() > 0){
            timeCount++;
            vec[First_Level[0].ProcessId].proceedTime++;
            current_quan++;
            //finished
            if(vec[First_Level[0].ProcessId].proceedTime == vec[First_Level[0].ProcessId].burstTime){
                current_quan = 0;
                unfinishedprocess--;

                vec[First_Level[0].ProcessId].TurnaroundTime = timeCount - vec[First_Level[0].ProcessId].arrivalTime;

                vec[First_Level[0].ProcessId].waitingTime = vec[First_Level[0].ProcessId].TurnaroundTime - vec[First_Level[0].ProcessId].burstTime;
                
                First_Level.erase(First_Level.begin());
            }else if(current_quan == quantum){
                current_quan = 0;
                Process temp = vec[First_Level[0].ProcessId];
                vec[First_Level[0].ProcessId].burstTime = vec[First_Level[0].ProcessId].burstTime-vec[First_Level[0].ProcessId].proceedTime;
                
                Second_Level.push_back(vec[First_Level[0].ProcessId]);
                First_Level.erase(First_Level.begin());
            }

        }
        else if(Second_Level.size() > 0){
            timeCount++;
            vec[Second_Level[0].ProcessId].burstTime--;
            Second_Level[0].burstTime--;
            vec[Second_Level[0].ProcessId].proceedTime++;
            
            if(vec[Second_Level[0].ProcessId].burstTime == 0) {
                unfinishedprocess--;
                vec[Second_Level[0].ProcessId].TurnaroundTime = timeCount - vec[Second_Level[0].ProcessId].arrivalTime;
                vec[Second_Level[0].ProcessId].waitingTime = vec[Second_Level[0].ProcessId].TurnaroundTime - vec[Second_Level[0].ProcessId].proceedTime;
                Second_Level.erase(Second_Level.begin());
            }
        }else{
            timeCount++;
        }
        for(int i = vec.size()-unfinishedprocess; i < vec.size(); i++){
            if(timeCount == vec[i].arrivalTime){
                First_Level.push_back(vec[i]);
            }
        }
        sort(Second_Level.begin(), Second_Level.end(), cmp_burstTime);
    }

    output(vec, numofprocess);
        
    return 0;
}

