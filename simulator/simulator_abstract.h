#ifndef SIMULATOR_ABSTRACT_H
#define SIMULATOR_ABSTRACT_H

#include <vector>

#include "task.h"
#include "least_common_multiple.h"

using namespace std;

class SimulatorAbstract
{
public:

    SimulatorAbstract(vector<Task> tasks, int processor_number)
    {
        this->tasks = tasks;
        this->processor_number = processor_number;

        vector<int> periods;

        for (int i = 0; i < tasks.size(); i++)
            periods.push_back(tasks[i].getPeriod());

        this->simulation_period = LeastCommonMultiple::Calculate(periods);
    }

    virtual void Simulate() = 0;

protected:

    vector<Task> tasks;

    int processor_number;

    int simulation_period;
};

#endif // SIMULATOR_ABSTRACT_H
