#include "simulator_global.h"

void SimulatorGlobal::Simulate()
{
    bool mustFinish = false;

    while (mustFinish == false)
    {
        int event = chain->DetermineNextEvent();

        recalculateLeft();

        recalculateIdle();

        if (this->show_simulation)
            showSimulationStep();

        mustFinish = processNextEvent(event);
    }
}

void SimulatorGlobal::reassignTasks(vector<Task *> tasks)
{
    // remember previous state of each task

    for (unsigned int i = 0; i < tasks.size(); i++)
        tasks.at(i)->MemorizeWorking();

    // unassign all tasks

    for (unsigned int i = 0; i < tasks_sorted.size(); i++)
        tasks_sorted.at(i)->IsWorking = false;

    // reassign n most priorited tasks

    int processors_free = this->processor_number;

    for (unsigned int i = 0; i < tasks_sorted.size(); i++)
        if (processors_free > 0)
        {
            if (tasks_sorted.at(i)->Left > 0)
            {
                tasks_sorted.at(i)->IsWorking = true;
                processors_free--;
            }
        }
        else
            break;

    // process tasks which stopped working

    for (unsigned int i = 0; i < tasks.size(); i++)
    {
        if (tasks.at(i)->WasWorking && !tasks.at(i)->IsWorking)
        {
            free_processor_id.push_back(tasks.at(i)->Processor_id);
            processors.at(tasks.at(i)->Processor_id)->Task_id = -1;

            if (tasks.at(i)->Left > 0)
            {
                processors.at(tasks.at(i)->Processor_id)->Preemtions++;
            }

            tasks.at(i)->Processor_id = -1;
        }
    }

    // process tasks which started working

    for (unsigned int i = 0; i < tasks.size(); i++)
    {
        if (!tasks.at(i)->WasWorking && tasks.at(i)->IsWorking)
        {
            tasks.at(i)->Processor_id = free_processor_id[free_processor_id.size() - 1];
            free_processor_id.pop_back();

            processors.at(tasks.at(i)->Processor_id)->Task_id = tasks.at(i)->Task_id;

            if (tasks.at(i)->Left > 0)
                chain->setEvent(i * 3 + 2, chain->getTime() + tasks.at(i)->Left);
            else
                chain->setEvent(i * 3 + 2, chain->getTime() + tasks.at(i)->getWcet());
        }
    }
}

void SimulatorGlobal::recalculateLeft()
{
    if (chain->Time_difference > 0)
        for (unsigned int i = 0; i < tasks.size(); i++)
            if ((tasks.at(i)->Left > 0) && (tasks.at(i)->IsWorking))
                tasks.at(i)->Left -= chain->Time_difference;
}


void SimulatorGlobal::recalculateIdle()
{
    if (chain->Time_difference > 0)
        for (unsigned int i = 0; i < processors.size(); i++)
            if (processors.at(i)->Task_id == -1)
                processors.at(i)->Idle += chain->Time_difference;
}

void SimulatorGlobal::showSimulationStep()
{
    if (chain->Time_difference > 0)
    {
        cout << "[" << chain->getTime() - chain->Time_difference << ";" << chain->getTime() << "]" << endl;

        for (int i = 0; i < processor_number; i++)
            if (processors.at(i)->Task_id != -1)
                cout << "#" << i + 1 << " " << processors.at(i)->Task_id + 1 << endl;
            else
                cout << "#" << i + 1 << " -" << endl;

        cout << endl;
    }
}

bool SimulatorGlobal::processNextEvent(int event)
{
    if (event == 0) // simulation time over
        return true;
    else
    {
        int index = (event - 1) / 3;     // index of task which event is applied to
        int action = event - index * 3;  // type of action which is applied by the task

        if (action == 1)   // job start
        {
            tasks.at(index)->Left = tasks.at(index)->getWcet();
            chain->setEvent(index * 3 + 1, chain->getTime() + tasks.at(index)->getPeriod());
            chain->setEvent(index * 3 + 3, chain->getTime() + tasks.at(index)->getDeadline());

            reassignTasks(tasks);
        }

        if (action == 2)   // job end
        {
            chain->setEvent(index * 3 + 2, -1);
            chain->setEvent(index * 3 + 3, -1);

            reassignTasks(tasks);
        }

        if (action == 3)   // job deadline (simulation failed if got here)
        {

        }
    }

    return false;
}
