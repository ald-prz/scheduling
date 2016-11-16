#ifndef SIMULATOR_ABSTRACT_H
#define SIMULATOR_ABSTRACT_H

#include <vector>

#include "task.h"
#include "least_common_multiple.h"

using namespace std;

class SimulatorAbstract
{
public:

    SimulatorAbstract(vector<Task*> tasks, int processor_number)
    {
        this->tasks = tasks;
        this->processor_number = processor_number;

        vector<int> periods;
        vector<int> offsets;
        for (unsigned int i = 0; i < tasks.size(); i++)
        {
            periods.push_back(tasks[i]->getPeriod());
            offsets.push_back(tasks[i]->getOffset());
        }

        this->hyper_period = LeastCommonMultiple::Calculate(periods);

        this->max_offset = offsets.at(0);
        for (unsigned int i = 1; i < offsets.size(); i++)
            if (max_offset < offsets.at(i))
                max_offset = offsets.at(i);

        tasks_sorted = tasks;

        for (unsigned int i = 0; i < tasks_sorted.size() - 1; i++) // sort them by period in ascending order
            for (unsigned int j = 0; j <= i; j++)
                if (tasks_sorted.at(j)->getPeriod() > tasks_sorted.at(j + 1)->getPeriod())
                {
                    Task *change;
                    change = tasks_sorted.at(j);
                    tasks_sorted.at(j) = tasks_sorted.at(j + 1);
                    tasks_sorted.at(j + 1) = change;
                }
    }

    virtual void Simulate() = 0;

protected:

    vector<Task*> tasks;
    vector<Task*> tasks_sorted;

    int processor_number;

    int hyper_period;

    int max_offset;
};

#endif // SIMULATOR_ABSTRACT_H
