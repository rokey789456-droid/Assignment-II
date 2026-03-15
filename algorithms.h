#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <vector>
#include "Process.h"

enum class QueuePolicy {
    FCFS,
    SJF,
    PRIORITY,
    RR
};

struct QueueConfig {
    int level;
    QueuePolicy policy;
    int quantum;
};

enum class FinalPolicy {
    FCFS,
    SJF,
    PRIORITY
};

struct MLFQConfig {
    vector<int> quantums;    
    FinalPolicy finalPolicy; 
};



// los 4 basicos de la actividad 
void roundRobin(vector<Process> processes, int quantum);
void fcfs(vector<Process> processes);
void sjf(vector<Process> processes);
void stcf(vector<Process> processes);

void priorityScheduling(vector<Process> processes);
void mlq(vector<Process> processes, const vector<QueueConfig>& configs);
void mlfq(vector<Process> processes, const MLFQConfig& config);

#endif