#ifndef INPUT_H
#define INPUT_H

#include <vector>
#include <string>
#include "Process.h"

using namespace std;

vector<Process> readProcesses(const string& filename);

#endif