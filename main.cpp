#include <iostream>
#include <vector>
#include "Process.h"
#include "input.h"
#include "algorithms.h"

using namespace std;

string policyToString(QueuePolicy policy) {
    switch (policy) {
        case QueuePolicy::FCFS: return "FCFS";
        case QueuePolicy::SJF: return "SJF";
        case QueuePolicy::PRIORITY: return "PRIORITY";
        case QueuePolicy::RR: return "RR";
        default: return "UNKNOWN";
    }
}

QueuePolicy choosePolicy() {
    int option;

    cout << "\nSeleccione el algoritmo para esta cola:\n";
    cout << "1. FCFS\n";
    cout << "2. SJF\n";
    cout << "3. PRIORITY\n";
    cout << "4. RR\n";
    cout << "Opcion: ";
    cin >> option;

    while (option < 1 || option > 4) {
        cout << "Opcion invalida. Intente de nuevo: ";
        cin >> option;
    }

    switch (option) {
        case 1: return QueuePolicy::FCFS;
        case 2: return QueuePolicy::SJF;
        case 3: return QueuePolicy::PRIORITY;
        case 4: return QueuePolicy::RR;
        default: return QueuePolicy::FCFS;
    }
}

string finalPolicyToString(FinalPolicy policy) {
    switch (policy) {
        case FinalPolicy::FCFS: return "FCFS";
        case FinalPolicy::SJF: return "SJF";
        case FinalPolicy::PRIORITY: return "PRIORITY";
        default: return "UNKNOWN";
    }
}

FinalPolicy chooseFinalPolicy() {
    int option;

    cout << "\nSeleccione el algoritmo para la ultima cola:\n";
    cout << "1. FCFS\n";
    cout << "2. SJF\n";
    cout << "3. PRIORITY\n";
    cout << "Opcion: ";
    cin >> option;

    while (option < 1 || option > 3) {
        cout << "Opcion invalida. Intente de nuevo: ";
        cin >> option;
    }

    switch (option) {
        case 1: return FinalPolicy::FCFS;
        case 2: return FinalPolicy::SJF;
        case 3: return FinalPolicy::PRIORITY;
        default: return FinalPolicy::FCFS;
    }
}

void showProcesses(const vector<Process>& processes) {
    cout << "\nProcesos cargados:\n";
    cout << "ID\tBT\tAT\tQ\tPriority\n";

    for (const Process& p : processes) {
        cout << p.id << "\t"
             << p.burstTime << "\t"
             << p.arrivalTime << "\t"
             << p.queueLevel << "\t"
             << p.priority << "\n";
    }
}

void ejecutarAlgoritmos(const vector<Process>& processes) {

    int option;

    while (true) {

        cout << "\nSeleccione el algoritmo a ejecutar:\n";
        cout << "1. FCFS\n";
        cout << "2. SJF\n";
        cout << "3. STCF / PSJF\n";
        cout << "4. Round Robin\n";
        cout << "5. Priority Scheduling\n";
        cout << "6. Multi-Level Queue (MLQ)\n";
        cout << "7. Multi-Level Feedback Queue (MLFQ)\n";
        cout << "0. Cambiar archivo\n";
        cout << "Opcion: ";

        cin >> option;

        if (option == 0)
            break;

        switch (option) {

            case 1: {
                vector<Process> temp = processes;
                fcfs(temp);
                break;
            }

            case 2: {
                vector<Process> temp = processes;
                sjf(temp);
                break;
            }

            case 3: {
                vector<Process> temp = processes;
                stcf(temp);
                break;
            }

            case 4: {
                vector<Process> temp = processes;
                int quantum;

                cout << "Ingrese el quantum para Round Robin: ";
                cin >> quantum;

                roundRobin(temp, quantum);
                break;
            }

            case 5: {
                vector<Process> temp = processes;
                priorityScheduling(temp);
                break;
            }

            case 6: {
                vector<Process> temp = processes;

                int numQueues = 3;
                cout << "\nMLQ usa 3 colas (Q1, Q2, Q3).\n";

                vector<QueueConfig> configs;

                for (int i = 0; i < numQueues; i++) {

                    QueueConfig config;
                    config.level = i + 1;

                    cout << "\n--- Configuracion de la cola " << config.level << " ---\n";

                    config.policy = choosePolicy();

                    if (config.policy == QueuePolicy::RR) {
                        cout << "Ingrese el quantum para RR: ";
                        cin >> config.quantum;
                    } else {
                        config.quantum = 0;
                    }

                    configs.push_back(config);
                }

                cout << "\nConfiguracion seleccionada:\n";

                for (const QueueConfig& config : configs) {

                    cout << "Q" << config.level << " -> "
                         << policyToString(config.policy);

                    if (config.policy == QueuePolicy::RR)
                        cout << " (q=" << config.quantum << ")";

                    cout << endl;
                }

                mlq(temp, configs);

                break;
            }

            case 7: {
                vector<Process> temp = processes;

                MLFQConfig config;

                int numRRQueues;

                cout << "\nCuantas colas Round Robin desea antes de la cola final? ";
                cin >> numRRQueues;

                while (numRRQueues < 1) {

                    cout << "Debe haber al menos 1 cola RR. Intente de nuevo: ";
                    cin >> numRRQueues;
                }

                config.quantums.resize(numRRQueues);

                for (int i = 0; i < numRRQueues; i++) {

                    cout << "Ingrese el quantum para Q" << (i + 1) << ": ";
                    cin >> config.quantums[i];
                }

                config.finalPolicy = chooseFinalPolicy();

                cout << "Q" << (numRRQueues + 1)
                     << " -> "
                     << finalPolicyToString(config.finalPolicy)
                     << endl;

                mlfq(temp, config);

                break;
            }

            default:
                cout << "Opcion invalida.\n";
                break;
        }
    }
}

int main() {
    int opcionArchivo;

    while (true) {
        cout << "\nSeleccione el archivo de procesos:\n";
        cout << "1. processes.txt\n";
        cout << "2. processes1.txt\n";
        cout << "3. processes2.txt\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcionArchivo;

        if (opcionArchivo == 0) {
            break;
        }

        vector<Process> processes;
        bool archivoValido = true;
        // modificar a futuro para que sea automatico en base a cuantos .txt de ejemplos haya en x carpeta
        switch (opcionArchivo) {
            case 1:
                processes = readProcesses("processes.txt");
                break;
            case 2:
                processes = readProcesses("processes1.txt");
                break;
            case 3:
                processes = readProcesses("processes2.txt");
                break;
            default:
                cout << "Opcion invalida\n";
                archivoValido = false;
                break;
        }

        if (archivoValido) {
            cout << "\nArchivo cargado correctamente.\n";
            showProcesses(processes);
            ejecutarAlgoritmos(processes);
        }
    }

    cout << "\nPrograma finalizado.\n";
    return 0;
}