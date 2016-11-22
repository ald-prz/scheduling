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
            if (processor.at(i)->Task_id == -1)
                processor.at(i)->Idle += chain->Timespan;
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

void SimulatorAbstract::initializeProcessors()
{
    for (int i = 0; i < processor_num; i++)
        processor.push_back(new Processor(i));
}
