#include "simulator_partitioned.h"

SimulatorPartitioned::SimulatorPartitioned(vector<Task *> tasks, int processor_number, bool show_simulation) : SimulatorAbstract(tasks, processor_number, show_simulation)
{
    BestFitPacker packer(tasks, processor_number);
    packer.Pack();
}

SimulationResult SimulatorPartitioned::Simulate()
{
    bool mustFinish = false;
    schedulable = true;

    while (mustFinish == false)
    {
        int event = chain->DetermineNextEvent();

        recalculateLeft();

        recalculateIdle();

        if (this->show_simulation)
            showSimulationStep();

        mustFinish = processNextEvent(event);
    }

    return SimulationResult(processors, schedulable, chain->getTime());
}

void SimulatorPartitioned::reassignTasks(vector<Task *> tasks)
{
    // memorize previous state of each task

    for (unsigned int i = 0; i < tasks.size(); i++)
        tasks.at(i)->MemorizeWorking();

    // unassign all tasks

    for (unsigned int i = 0; i < tasks.size(); i++)
        tasks.at(i)->IsWorking = false;

    // reassign tasks over the processors

    for (unsigned int i = 0; i < processors.size(); i++)
    {
        int index = -1;
        int min_period;

        for (unsigned int j = 0; j < tasks.size(); j++)
            if ((tasks.at(j)->Processor_id == i) && (tasks.at(j)->Left > 0))
                if (index != -1)
                {
                    if (tasks.at(j)->getPeriod() < min_period)
                    {
                        index = j;
                        min_period = tasks.at(j)->getPeriod();
                    }
                }
                else
                {
                    index = j;
                    min_period = tasks.at(j)->getPeriod();
                }

        if (index != -1)
        {
            if (processors.at(i)->Task_id != index)
            {
                if (processors.at(i)->Task_id != -1)
                {
                    processors.at(i)->Preemtions++;
                    chain->setEvent(processors.at(i)->Task_id * 3 + 2, -1);
                }

                processors.at(i)->Task_id = index;


                if (tasks.at(index)->Left > 0)
                    chain->setEvent(index * 3 + 2, chain->getTime() + tasks.at(index)->Left);
                else
                    chain->setEvent(index * 3 + 2, chain->getTime() + tasks.at(index)->getWcet());
            }

            tasks.at(index)->IsWorking = true;
        }
        else
            processors.at(i)->Task_id = -1;
    }
}

void SimulatorPartitioned::recalculateLeft()
{
    if (chain->Time_difference > 0)
        for (unsigned int i = 0; i < tasks.size(); i++)
            if ((tasks.at(i)->Left > 0) && (tasks.at(i)->IsWorking))
                tasks.at(i)->Left -= chain->Time_difference;
}

void SimulatorPartitioned::recalculateIdle()
{
    if (chain->Time_difference > 0)
        for (unsigned int i = 0; i < processors.size(); i++)
            if (processors.at(i)->Task_id == -1)
                processors.at(i)->Idle += chain->Time_difference;
}

void SimulatorPartitioned::showSimulationStep()
{
    if (chain->Time_difference > 0)
    {
        cout << "[" << chain->getTime() - chain->Time_difference << ";" << chain->getTime() << "]" << endl;

        for (int i = 0; i < processor_number; i++)
            if (processors.at(i)->Task_id != -1)
                cout << "#" << i << " " << processors.at(i)->Task_id << endl;
            else
                cout << "#" << i << " -" << endl;

        cout << endl;
    }
}

/*!
 * \brief Processes the next event in the event list according to FEC algorithm
 * \param event Index of the next event
 * \return Flag if must finish the simulation
 */
bool SimulatorPartitioned::processNextEvent(int event)
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

            processors.at(tasks.at(index)->Processor_id)->Task_id = -1;

            reassignTasks(tasks);
        }

        if (action == 3)   // job deadline (simulation failed if got here)
        {
            schedulable = false;
            return true;
        }
    }

    return false;
}
