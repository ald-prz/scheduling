#ifndef SIMULATOR_ABSTRACT_H
#define SIMULATOR_ABSTRACT_H

#include <vector>

#include "task.h"
#include "least_common_multiple.h"
#include "processor.h"

using namespace std;

class SimulatorAbstract
{
public:

    SimulatorAbstract(vector<Task*> tasks, int processor_number, bool show_simulation)
    {
        this->tasks = tasks;
        this->processor_number = processor_number;
        this->show_simulation = show_simulation;

        setAttributes();
        sortTasks();
        initializeProcessors();
    }

    virtual void Simulate() = 0;

protected:

    vector<Task*> tasks;
    vector<Task*> tasks_sorted;

    vector<Processor*> processors;

    int processor_number;
    long long hyper_period;
    long long max_offset;

    bool show_simulation;

private:

    void setAttributes()
    {
        vector<long long> periods;
        vector<long long> offsets;

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
    }

    void sortTasks()
    {
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

    void initializeProcessors()
    {
        for (int i = 0; i < processor_number; i++)
            processors.push_back(new Processor(i));
    }

};

#endif // SIMULATOR_ABSTRACT_H
