#ifndef PROCESS_H
#define PROCESS_H

#include <string>
using namespace std;

struct Process {
    string id;
    int burstTime;
    int arrivalTime;
    int remainingTime;
    int queueLevel;
    int priority;

    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int responseTime;

    bool started;
    bool finished;
};

#endif