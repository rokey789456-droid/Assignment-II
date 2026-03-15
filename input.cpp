#include "input.h"
#include <fstream>
#include <sstream>
#include <iostream>

vector<Process> readProcesses(const string& filename) {
    vector<Process> processes;
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error: no se pudo abrir el archivo " << filename << endl;
        return processes;
    }

    string line;

    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        stringstream ss(line);
        string token;

        Process p;

        getline(ss, p.id, ';');

        getline(ss, token, ';');
        p.burstTime = stoi(token);

        getline(ss, token, ';');
        p.arrivalTime = stoi(token);

        getline(ss, token, ';');
        p.queueLevel = stoi(token);

        getline(ss, token, ';');
        p.priority = stoi(token);

        p.remainingTime = p.burstTime;
        p.completionTime = 0;
        p.turnaroundTime = 0;
        p.waitingTime = 0;
        p.responseTime = -1;
        p.started = false;
        p.finished = false;

        processes.push_back(p);
    }

    file.close();
    return processes;
}