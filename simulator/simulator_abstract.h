#ifndef SIMULATOR_ABSTRACT_H
#define SIMULATOR_ABSTRACT_H

#include <vector>

#include "task.h"

using namespace std;

class SimulatorAbstract
{
public:

    SimulatorAbstract(vector<Task> tasks, int processor_number)
    {
        this->tasks = tasks;
        this->processor_number = processor_number;
    }

    virtual void Simulate() = 0;

protected:

    vector<Task> tasks;

    int processor_number;

};

#endif // SIMULATOR_ABSTRACT_H
