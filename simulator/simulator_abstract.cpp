#include "simulator_abstract.h"

SimulatorAbstract::SimulatorAbstract(vector<Task *> tasks, int processor_number, bool show_simulation)
{
    this->task = tasks;
    this->processor_num = processor_number;
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

SimulatorAbstract::~SimulatorAbstract()
{
    for (unsigned int i = 0; i < task.size(); i++)
        delete task.at(i);
}

void SimulatorAbstract::recalculateLeft()
{
    if (chain->Time_difference > 0)
        for (unsigned int i = 0; i < task.size(); i++)
            if ((task.at(i)->Left > 0) && (task.at(i)->IsWorking))
                task.at(i)->Left -= chain->Time_difference;
}

void SimulatorAbstract::recalculateIdle()
{
    if (chain->Time_difference > 0)
        for (unsigned int i = 0; i < processor.size(); i++)
            if (processor.at(i)->Task_id == -1)
                processor.at(i)->Idle += chain->Time_difference;
}

void SimulatorAbstract::showSimulationStep()
{
    if (chain->Time_difference > 0)
    {
        cout << "[" << chain->getTime() - chain->Time_difference << ";" << chain->getTime() << "]" << endl;

        for (int i = 0; i < processor_num; i++)
            if (processor.at(i)->Task_id != -1)
                cout << "#" << i << " " << processor.at(i)->Task_id << endl;
            else
                cout << "#" << i << " -" << endl;

        cout << endl;
    }
}

void SimulatorAbstract::setAttributes()
{
    vector<long long> periods;
    vector<long long> offsets;

    for (unsigned int i = 0; i < task.size(); i++)
    {
        periods.push_back(task[i]->getPeriod());
        offsets.push_back(task[i]->getOffset());
    }

    this->hyper_period = LeastCommonMultiple::Calculate(periods);

    this->max_offset = offsets.at(0);

    for (unsigned int i = 1; i < offsets.size(); i++)
        if (max_offset < offsets.at(i))
            max_offset = offsets.at(i);
}

void SimulatorAbstract::initializeProcessors()
{
    for (int i = 0; i < processor_num; i++)
        processor.push_back(new Processor(i));
}
