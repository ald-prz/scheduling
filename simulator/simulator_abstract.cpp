#include "simulator_abstract.h"

SimulatorAbstract::SimulatorAbstract(vector<Task *> tasks, int processor_number, bool show_simulation)
{
    this->tasks = tasks;
    this->processor_number = processor_number;
    this->show_simulation = show_simulation;

    setAttributes();
    sortTasks();
    initializeProcessors();
}

void SimulatorAbstract::setAttributes()
{
    vector<long long> periods;
    vector<long long> offsets;

    for (unsigned int i = 0; i < tasks.size(); i++)
    {
        periods.push_back(tasks[i]->GetPeriod());
        offsets.push_back(tasks[i]->GetOffset());
    }

    this->hyper_period = LeastCommonMultiple::Calculate(periods);

    this->max_offset = offsets.at(0);

    for (unsigned int i = 1; i < offsets.size(); i++)
        if (max_offset < offsets.at(i))
            max_offset = offsets.at(i);
}

void SimulatorAbstract::sortTasks()
{
    tasks_sorted = tasks;

    for (unsigned int i = 0; i < tasks_sorted.size() - 1; i++) // sort them by period in ascending order
        for (unsigned int j = 0; j <= i; j++)
            if (tasks_sorted.at(j)->GetPeriod() > tasks_sorted.at(j + 1)->GetPeriod())
            {
                Task *change;
                change = tasks_sorted.at(j);
                tasks_sorted.at(j) = tasks_sorted.at(j + 1);
                tasks_sorted.at(j + 1) = change;
            }
}

void SimulatorAbstract::initializeProcessors()
{
    for (int i = 0; i < processor_number; i++)
        processors.push_back(new Processor(i));
}
