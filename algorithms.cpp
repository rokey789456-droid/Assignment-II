#include "algorithms.h"
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

// en general debo re-hacer las funciones para reducir codigo repetido teniendo en mente usarlas en mlfq y mlq.


void priorityScheduling(vector<Process> processes) {

    int n = processes.size();
    int completed = 0;
    int currentTime = 0;

    while (completed < n) {

        int selected = -1;

        for (int i = 0; i < n; i++) {

            if (!processes[i].finished && processes[i].arrivalTime <= currentTime) {

                if (selected == -1 || processes[i].priority > processes[selected].priority) {
                    selected = i;
                }
                else if (processes[i].priority == processes[selected].priority) {

                    if (processes[i].arrivalTime < processes[selected].arrivalTime) {
                        selected = i;
                    }
                }
            }
        }

        if (selected == -1) {

            // CPU idle
            currentTime++;

        } else {

            if (!processes[selected].started) {
                processes[selected].responseTime =
                    currentTime - processes[selected].arrivalTime;

                processes[selected].started = true;
            }

            currentTime += processes[selected].burstTime;

            processes[selected].remainingTime = 0;

            processes[selected].completionTime = currentTime;

            processes[selected].turnaroundTime =
                processes[selected].completionTime -
                processes[selected].arrivalTime;

            processes[selected].waitingTime =
                processes[selected].turnaroundTime -
                processes[selected].burstTime;

            processes[selected].finished = true;

            completed++;
        }
    }

    cout << "\n --- Priority Scheduling ---\n";
    cout << "ID\tBT\tAT\tPR\tCT\tTAT\tWT\tRT\n";

    double totalTAT = 0;
    double totalWT = 0;
    double totalRT = 0;

    for (const Process& p : processes) {

        cout << p.id << "\t"
             << p.burstTime << "\t"
             << p.arrivalTime << "\t"
             << p.priority << "\t"
             << p.completionTime << "\t"
             << p.turnaroundTime << "\t"
             << p.waitingTime << "\t"
             << p.responseTime << "\n";

        totalTAT += p.turnaroundTime;
        totalWT += p.waitingTime;
        totalRT += p.responseTime;
    }

    cout << "\nPromedio TAT: " << totalTAT / n << endl;
    cout << "Promedio WT : " << totalWT / n << endl;
    cout << "Promedio RT : " << totalRT / n << endl;
}

void roundRobin(vector<Process> processes, int quantum) {

    int n = processes.size();
    int completed = 0;
    int currentTime = 0;

    queue<int> readyQueue;
    vector<bool> inQueue(n, false);

    while (completed < n) {

        for (int i = 0; i < n; i++) {
            if (!processes[i].finished &&
                !inQueue[i] &&
                processes[i].arrivalTime <= currentTime) {

                readyQueue.push(i);
                inQueue[i] = true;
            }
        }

        if (readyQueue.empty()) {

            // CPU idle
            currentTime++;

        } else {

            int current = readyQueue.front();
            readyQueue.pop();
            inQueue[current] = false;

            if (!processes[current].started) {
                processes[current].responseTime =
                    currentTime - processes[current].arrivalTime;
                processes[current].started = true;
            }

            int executionTime;

            if (processes[current].remainingTime < quantum) {
                executionTime = processes[current].remainingTime;
            } else {
                executionTime = quantum;
            }

            processes[current].remainingTime -= executionTime;
            currentTime += executionTime;

            for (int i = 0; i < n; i++) {
                if (!processes[i].finished &&
                    !inQueue[i] &&
                    i != current &&
                    processes[i].arrivalTime <= currentTime) {

                    readyQueue.push(i);
                    inQueue[i] = true;
                }
            }

            if (processes[current].remainingTime > 0) {

                readyQueue.push(current);
                inQueue[current] = true;

            } else {

                processes[current].finished = true;

                processes[current].completionTime = currentTime;

                processes[current].turnaroundTime =
                    processes[current].completionTime -
                    processes[current].arrivalTime;

                processes[current].waitingTime =
                    processes[current].turnaroundTime -
                    processes[current].burstTime;

                completed++;
            }
        }
    }

    cout << "\n--- Round Robin ---\n";
    cout << "Quantum: " << quantum << "\n";
    cout << "ID\tBT\tAT\tCT\tTAT\tWT\tRT\n";

    double totalTAT = 0;
    double totalWT = 0;
    double totalRT = 0;

    for (const Process& p : processes) {

        cout << p.id << "\t"
             << p.burstTime << "\t"
             << p.arrivalTime << "\t"
             << p.completionTime << "\t"
             << p.turnaroundTime << "\t"
             << p.waitingTime << "\t"
             << p.responseTime << "\n";

        totalTAT += p.turnaroundTime;
        totalWT += p.waitingTime;
        totalRT += p.responseTime;
    }

    cout << "\nPromedio TAT: " << totalTAT / n << endl;
    cout << "Promedio WT : " << totalWT / n << endl;
    cout << "Promedio RT : " << totalRT / n << endl;
}

void fcfs(vector<Process> processes) {

    int n = processes.size();

    sort(processes.begin(), processes.end(),
        [](Process a, Process b) {
            return a.arrivalTime < b.arrivalTime;
        });

    int currentTime = 0;

    for (int i = 0; i < n; i++) {

        if (currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime;
        }

        processes[i].responseTime =
            currentTime - processes[i].arrivalTime;

        currentTime += processes[i].burstTime;

        processes[i].completionTime = currentTime;

        processes[i].turnaroundTime =
            processes[i].completionTime - processes[i].arrivalTime;

        processes[i].waitingTime =
            processes[i].turnaroundTime - processes[i].burstTime;
    }

    cout << "\n--- FCFS Scheduling ---\n";
    cout << "ID\tBT\tAT\tCT\tTAT\tWT\tRT\n";

    double totalTAT = 0;
    double totalWT = 0;
    double totalRT = 0;

    for (const Process& p : processes) {

        cout << p.id << "\t"
             << p.burstTime << "\t"
             << p.arrivalTime << "\t"
             << p.completionTime << "\t"
             << p.turnaroundTime << "\t"
             << p.waitingTime << "\t"
             << p.responseTime << "\n";

        totalTAT += p.turnaroundTime;
        totalWT += p.waitingTime;
        totalRT += p.responseTime;
    }

    cout << "\nPromedio TAT: " << totalTAT / n << endl;
    cout << "Promedio WT : " << totalWT / n << endl;
    cout << "Promedio RT : " << totalRT / n << endl;
}

void sjf(vector<Process> processes) {

    int n = processes.size();
    int completed = 0;
    int currentTime = 0;

    while (completed < n) {

        int selected = -1;

        for (int i = 0; i < n; i++) {

            if (!processes[i].finished &&
                processes[i].arrivalTime <= currentTime) {

                if (selected == -1 ||
                    processes[i].burstTime < processes[selected].burstTime) {

                    selected = i;
                }
            }
        }

        if (selected == -1) {

            currentTime++;

        } else {

            if (!processes[selected].started) {
                processes[selected].responseTime =
                    currentTime - processes[selected].arrivalTime;

                processes[selected].started = true;
            }

            currentTime += processes[selected].burstTime;

            processes[selected].completionTime = currentTime;

            processes[selected].turnaroundTime =
                processes[selected].completionTime -
                processes[selected].arrivalTime;

            processes[selected].waitingTime =
                processes[selected].turnaroundTime -
                processes[selected].burstTime;

            processes[selected].finished = true;

            completed++;
        }
    }

    cout << "\n--- SJF Scheduling ---\n";
    cout << "ID\tBT\tAT\tCT\tTAT\tWT\tRT\n";

    double totalTAT = 0;
    double totalWT = 0;
    double totalRT = 0;

    for (const Process& p : processes) {

        cout << p.id << "\t"
             << p.burstTime << "\t"
             << p.arrivalTime << "\t"
             << p.completionTime << "\t"
             << p.turnaroundTime << "\t"
             << p.waitingTime << "\t"
             << p.responseTime << "\n";

        totalTAT += p.turnaroundTime;
        totalWT += p.waitingTime;
        totalRT += p.responseTime;
    }

    cout << "\nPromedio TAT: " << totalTAT / n << endl;
    cout << "Promedio WT : " << totalWT / n << endl;
    cout << "Promedio RT : " << totalRT / n << endl;
}

void stcf(vector<Process> processes) {

    int n = processes.size();
    int completed = 0;
    int currentTime = 0;

    while (completed < n) {

        int selected = -1;

        for (int i = 0; i < n; i++) {

            if (!processes[i].finished &&
                processes[i].arrivalTime <= currentTime) {

                if (selected == -1 ||
                    processes[i].remainingTime <
                    processes[selected].remainingTime) {

                    selected = i;
                }
            }
        }

        if (selected == -1) {

            currentTime++;

        } else {

            if (!processes[selected].started) {
                processes[selected].responseTime =
                    currentTime - processes[selected].arrivalTime;

                processes[selected].started = true;
            }

            processes[selected].remainingTime--;
            currentTime++;

            if (processes[selected].remainingTime == 0) {

                processes[selected].finished = true;
                completed++;

                processes[selected].completionTime = currentTime;

                processes[selected].turnaroundTime =
                    processes[selected].completionTime -
                    processes[selected].arrivalTime;

                processes[selected].waitingTime =
                    processes[selected].turnaroundTime -
                    processes[selected].burstTime;
            }
        }
    }

    cout << "\n--- STCF Scheduling ---\n";
    cout << "ID\tBT\tAT\tCT\tTAT\tWT\tRT\n";

    double totalTAT = 0;
    double totalWT = 0;
    double totalRT = 0;

    for (const Process& p : processes) {

        cout << p.id << "\t"
             << p.burstTime << "\t"
             << p.arrivalTime << "\t"
             << p.completionTime << "\t"
             << p.turnaroundTime << "\t"
             << p.waitingTime << "\t"
             << p.responseTime << "\n";

        totalTAT += p.turnaroundTime;
        totalWT += p.waitingTime;
        totalRT += p.responseTime;
    }

    cout << "\nPromedio TAT: " << totalTAT / n << endl;
    cout << "Promedio WT : " << totalWT / n << endl;
    cout << "Promedio RT : " << totalRT / n << endl;
}

void mlq(vector<Process> processes, const vector<QueueConfig>& configs) {
    int n = processes.size();
    int completed = 0;
    int currentTime = 0;

    vector<bool> inQueue(n, false);
    vector<queue<int>> rrQueues(configs.size());

    auto getConfigIndexByLevel = [&](int level) -> int {
        for (int i = 0; i < (int)configs.size(); i++) {
            if (configs[i].level == level) {
                return i;
            }
        }
        return -1;
    };

    while (completed < n) {

        for (int i = 0; i < n; i++) {
            if (!processes[i].finished && processes[i].arrivalTime <= currentTime) {
                int configIndex = getConfigIndexByLevel(processes[i].queueLevel);

                if (configIndex != -1 &&
                    configs[configIndex].policy == QueuePolicy::RR &&
                    !inQueue[i]) {
                    rrQueues[configIndex].push(i);
                    inQueue[i] = true;
                }
            }
        }

        int selected = -1;
        int selectedConfigIndex = -1;

        for (int c = 0; c < (int)configs.size(); c++) {
            int level = configs[c].level;
            QueuePolicy policy = configs[c].policy;

            if (policy == QueuePolicy::RR) {
                if (!rrQueues[c].empty()) {
                    selectedConfigIndex = c;
                    break;
                }
            } else {
                int candidate = -1;

                for (int i = 0; i < n; i++) {
                    if (!processes[i].finished &&
                        processes[i].queueLevel == level &&
                        processes[i].arrivalTime <= currentTime) {

                        if (candidate == -1) {
                            candidate = i;
                        } else {
                            if (policy == QueuePolicy::FCFS) {
                                if (processes[i].arrivalTime < processes[candidate].arrivalTime) {
                                    candidate = i;
                                }
                            } else if (policy == QueuePolicy::SJF) {
                                if (processes[i].burstTime < processes[candidate].burstTime) {
                                    candidate = i;
                                }
                            } else if (policy == QueuePolicy::PRIORITY) {
                                if (processes[i].priority > processes[candidate].priority) {
                                    candidate = i;
                                }
                            }
                        }
                    }
                }

                if (candidate != -1) {
                    selected = candidate;
                    selectedConfigIndex = c;
                    break;
                }
            }
        }

        if (selectedConfigIndex == -1) {

            currentTime++;

        } else {

            QueuePolicy currentPolicy = configs[selectedConfigIndex].policy;

            if (currentPolicy == QueuePolicy::RR) {
                int current = rrQueues[selectedConfigIndex].front();
                rrQueues[selectedConfigIndex].pop();
                inQueue[current] = false;

                if (!processes[current].started) {
                    processes[current].responseTime =
                        currentTime - processes[current].arrivalTime;
                    processes[current].started = true;
                }

                int quantum = configs[selectedConfigIndex].quantum;
                int executionTime = min(processes[current].remainingTime, quantum);

                processes[current].remainingTime -= executionTime;
                currentTime += executionTime;

                for (int i = 0; i < n; i++) {
                    if (!processes[i].finished &&
                        processes[i].arrivalTime <= currentTime) {

                        int configIndex = getConfigIndexByLevel(processes[i].queueLevel);

                        if (configIndex != -1 &&
                            configs[configIndex].policy == QueuePolicy::RR &&
                            !inQueue[i] &&
                            i != current) {
                            rrQueues[configIndex].push(i);
                            inQueue[i] = true;
                        }
                    }
                }

                if (processes[current].remainingTime > 0) {
                    rrQueues[selectedConfigIndex].push(current);
                    inQueue[current] = true;
                } else {
                    processes[current].finished = true;
                    processes[current].completionTime = currentTime;
                    processes[current].turnaroundTime =
                        processes[current].completionTime - processes[current].arrivalTime;
                    processes[current].waitingTime =
                        processes[current].turnaroundTime - processes[current].burstTime;
                    completed++;
                }

            } else {

                if (!processes[selected].started) {
                    processes[selected].responseTime =
                        currentTime - processes[selected].arrivalTime;
                    processes[selected].started = true;
                }

                currentTime += processes[selected].remainingTime;
                processes[selected].remainingTime = 0;
                processes[selected].finished = true;
                processes[selected].completionTime = currentTime;
                processes[selected].turnaroundTime =
                    processes[selected].completionTime - processes[selected].arrivalTime;
                processes[selected].waitingTime =
                    processes[selected].turnaroundTime - processes[selected].burstTime;
                completed++;
            }
        }
    }

    cout << "\n--- Multi-Level Queue (MLQ) ---\n";
    cout << "ID\tBT\tAT\tQ\tPR\tCT\tTAT\tWT\tRT\n";

    double totalTAT = 0;
    double totalWT = 0;
    double totalRT = 0;

    for (const Process& p : processes) {
        cout << p.id << "\t"
             << p.burstTime << "\t"
             << p.arrivalTime << "\t"
             << p.queueLevel << "\t"
             << p.priority << "\t"
             << p.completionTime << "\t"
             << p.turnaroundTime << "\t"
             << p.waitingTime << "\t"
             << p.responseTime << "\n";

        totalTAT += p.turnaroundTime;
        totalWT += p.waitingTime;
        totalRT += p.responseTime;
    }

    cout << "\nPromedio TAT: " << totalTAT / n << endl;
    cout << "Promedio WT : " << totalWT / n << endl;
    cout << "Promedio RT : " << totalRT / n << endl;
}

void mlfq(vector<Process> processes, const MLFQConfig& config) {
    int n = processes.size();
    int completed = 0;
    int currentTime = 0;

    int numLevels = config.quantums.size() + 1; // colas RR + cola final

    vector<queue<int>> rrQueues(config.quantums.size());
    vector<int> currentLevel(n, 0);   // todos empiezan en Q1
    vector<bool> inQueue(n, false);

    auto selectFromFinalQueue = [&](int finalLevel) -> int {
        int selected = -1;

        for (int i = 0; i < n; i++) {
            if (!processes[i].finished &&
                !inQueue[i] &&
                processes[i].arrivalTime <= currentTime &&
                currentLevel[i] == finalLevel) {

                if (selected == -1) {
                    selected = i;
                } else {
                    if (config.finalPolicy == FinalPolicy::FCFS) {
                        if (processes[i].arrivalTime < processes[selected].arrivalTime) {
                            selected = i;
                        } else if (processes[i].arrivalTime == processes[selected].arrivalTime &&
                                   processes[i].id < processes[selected].id) {
                            selected = i;
                        }
                    }
                    else if (config.finalPolicy == FinalPolicy::SJF) {
                        if (processes[i].burstTime < processes[selected].burstTime) {
                            selected = i;
                        } else if (processes[i].burstTime == processes[selected].burstTime &&
                                   processes[i].arrivalTime < processes[selected].arrivalTime) {
                            selected = i;
                        }
                    }
                    else if (config.finalPolicy == FinalPolicy::PRIORITY) {
                        if (processes[i].priority > processes[selected].priority) {
                            selected = i;
                        } else if (processes[i].priority == processes[selected].priority &&
                                   processes[i].arrivalTime < processes[selected].arrivalTime) {
                            selected = i;
                        }
                    }
                }
            }
        }

        return selected;
    };

    while (completed < n) {

        // Meter procesos nuevos en sus colas RR correspondientes
        for (int i = 0; i < n; i++) {
            if (!processes[i].finished &&
                !inQueue[i] &&
                processes[i].arrivalTime <= currentTime &&
                currentLevel[i] < (int)config.quantums.size()) {

                rrQueues[currentLevel[i]].push(i);
                inQueue[i] = true;
            }
        }

        int current = -1;
        int level = -1;

        // Buscar primero en las colas RR de mayor prioridad
        for (int l = 0; l < (int)config.quantums.size(); l++) {
            if (!rrQueues[l].empty()) {
                current = rrQueues[l].front();
                rrQueues[l].pop();
                inQueue[current] = false;
                level = l;
                break;
            }
        }

        // Si no hay procesos en RR, buscar en la cola final
        if (current == -1) {
            int finalLevel = numLevels - 1;
            current = selectFromFinalQueue(finalLevel);

            if (current != -1) {
                level = finalLevel;
            }
        }

        // Si no hay nada listo, CPU idle
        if (current == -1) {

            currentTime++;

        } else {

            // Primera vez que responde
            if (!processes[current].started) {
                processes[current].responseTime =
                    currentTime - processes[current].arrivalTime;
                processes[current].started = true;
            }

            // Caso 1: está en una cola RR
            if (level < (int)config.quantums.size()) {

                int quantum = config.quantums[level];
                int executionTime = min(processes[current].remainingTime, quantum);

                processes[current].remainingTime -= executionTime;
                currentTime += executionTime;

                // Durante la ejecución pudieron llegar procesos nuevos
                for (int i = 0; i < n; i++) {
                    if (!processes[i].finished &&
                        !inQueue[i] &&
                        i != current &&
                        processes[i].arrivalTime <= currentTime &&
                        currentLevel[i] < (int)config.quantums.size()) {

                        rrQueues[currentLevel[i]].push(i);
                        inQueue[i] = true;
                    }
                }

                if (processes[current].remainingTime == 0) {

                    processes[current].finished = true;
                    processes[current].completionTime = currentTime;
                    processes[current].turnaroundTime =
                        processes[current].completionTime - processes[current].arrivalTime;
                    processes[current].waitingTime =
                        processes[current].turnaroundTime - processes[current].burstTime;
                    completed++;

                } else {

                    // Baja de nivel si no terminó
                    currentLevel[current]++;

                    if (currentLevel[current] < (int)config.quantums.size()) {
                        rrQueues[currentLevel[current]].push(current);
                        inQueue[current] = true;
                    }
                    // Si bajó a la cola final, no se encola aquí.
                    // Será tomado luego por selectFromFinalQueue.
                }

            } else {

                // Caso 2: está en la última cola
                currentTime += processes[current].remainingTime;
                processes[current].remainingTime = 0;

                processes[current].finished = true;
                processes[current].completionTime = currentTime;
                processes[current].turnaroundTime =
                    processes[current].completionTime - processes[current].arrivalTime;
                processes[current].waitingTime =
                    processes[current].turnaroundTime - processes[current].burstTime;
                completed++;
            }
        }
    }

    cout << "\n--- Multi-Level Feedback Queue (MLFQ) ---\n";

    for (int i = 0; i < (int)config.quantums.size(); i++) {
        cout << "Q" << (i + 1) << " = RR(q=" << config.quantums[i] << ")\n";
    }

    cout << "Q" << numLevels << " = ";
    if (config.finalPolicy == FinalPolicy::FCFS) {
        cout << "FCFS\n";
    } else if (config.finalPolicy == FinalPolicy::SJF) {
        cout << "SJF\n";
    } else if (config.finalPolicy == FinalPolicy::PRIORITY) {
        cout << "PRIORITY\n";
    }

    cout << "\nID\tBT\tAT\tCT\tTAT\tWT\tRT\n";

    double totalTAT = 0;
    double totalWT = 0;
    double totalRT = 0;

    for (const Process& p : processes) {
        cout << p.id << "\t"
             << p.burstTime << "\t"
             << p.arrivalTime << "\t"
             << p.completionTime << "\t"
             << p.turnaroundTime << "\t"
             << p.waitingTime << "\t"
             << p.responseTime << "\n";

        totalTAT += p.turnaroundTime;
        totalWT += p.waitingTime;
        totalRT += p.responseTime;
    }

    cout << "\nPromedio TAT: " << totalTAT / n << endl;
    cout << "Promedio WT : " << totalWT / n << endl;
    cout << "Promedio RT : " << totalRT / n << endl;
}

