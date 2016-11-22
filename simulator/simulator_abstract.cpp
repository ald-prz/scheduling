#include "simulator_abstract.h"

SimulatorAbstract::SimulatorAbstract(vector<Task *> tasks, int processor_number, bool show_simulation)
{
    this->task = tasks;
    this->processor_num = processor_number;
    this->show_simulation = show_simulation;
}

void SimulatorAbstract::recalculateLeft()
{
    if (chain->Timespan > 0)
        for (unsigned int i = 0; i < task.size(); i++)
            if ((task.at(i)->Left > 0) && (task.at(i)->IsWorking))
                task.at(i)->Left -= chain->Timespan;
}

void SimulatorAbstract::recalculateIdle()
{
    if (chain->Timespan > 0)
        for (unsigned int i = 0; i < processor.size(); i++)
        {
            if (chain->getEvent(i) >= 0)
            {
                if (processor.at(i)->Task_id == -1)
                    processor.at(i)->Idle += chain->Timespan;

                processor.at(i)->Simulation_time = chain->getTime();
            }
        }
}

void SimulatorAbstract::showSimulationStep()
{
    if (chain->Timespan > 0)
    {
        cout << "[" << chain->getTime() - chain->Timespan << ";" << chain->getTime() << "]" << endl;

        for (int i = 0; i < processor_num; i++)
            if (processor.at(i)->Task_id != -1)
                cout << "#" << i << " " << processor.at(i)->Task_id << endl;
            else
                cout << "#" << i << " -" << endl;

        cout << endl;
    }
}

void SimulatorAbstract::set()
{
    initializeProcessors();

    this->calculateMaxOffset();
    this->calculateHyperperiod();

    vector<int> event;

    for (unsigned int i = 0; i < processor.size(); i++)
        if (processor.at(i)->Hyper_period >= 0)
        {
            event.push_back(processor.at(i)->Max_offset + 2 * processor.at(i)->Hyper_period);
            processor.at(i)->Intended_time = processor.at(i)->Max_offset + 2 * processor.at(i)->Hyper_period;
        }

    for (unsigned int i = 0; i < task.size(); i++)
    {
        task.at(i)->Reset();
        event.push_back(task.at(i)->getOffset());
        event.push_back(-1);
        event.push_back(-1);
    }

    chain = new FutureEventChain(event);
}

void SimulatorAbstract::initializeProcessors()
{
    for (int i = 0; i < processor_num; i++)
        processor.push_back(new Processor(i));
}
