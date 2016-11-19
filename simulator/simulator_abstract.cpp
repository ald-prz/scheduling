#include "simulator_abstract.h"

SimulatorAbstract::SimulatorAbstract(vector<Task *> tasks, int processor_number, bool show_simulation)
{
    this->tasks = tasks;
    this->processor_number = processor_number;
    this->show_simulation = show_simulation;

    setAttributes();

    initializeProcessors();

    vector<int> event;
    event.push_back(max_offset + 2 * hyper_period);

    for (unsigned int i = 0; i < tasks.size(); i++)
    {
        event.push_back(tasks.at(i)->getOffset());
        event.push_back(-1);
        event.push_back(-1);
    }

    chain = new FutureEventChain(event);
}

void SimulatorAbstract::setAttributes()
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

void SimulatorAbstract::initializeProcessors()
{
    for (int i = 0; i < processor_number; i++)
        processors.push_back(new Processor(i));
}
