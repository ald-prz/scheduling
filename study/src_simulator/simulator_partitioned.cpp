#include "simulator_partitioned.h"

SimulatorPartitioned::SimulatorPartitioned(vector<Task *> tasks, int processor_number, bool show_simulation) : SimulatorAbstract(tasks, processor_number, show_simulation)
{
    BestFitPacker packer(tasks, processor_number);
    packedSuccessfully = packer.Pack();
}

SimulationResult SimulatorPartitioned::Simulate()
{
    if (packedSuccessfully && (processor.size() > 0))
    {
        bool mustFinish = false;
        is_schedulable = true;

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
    else
        is_schedulable = false;

    return SimulationResult(processor, is_schedulable, chain->getTime(), chain->getEvent(0));
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

    for (unsigned int i = 0; i < processor.size(); i++)
    {
        int index = -1;
        int min_deadline;

        // find an appropriate task for [i] processor

        for (unsigned int j = 0; j < tasks.size(); j++)
            if ((tasks.at(j)->Processor_id == i) && (tasks.at(j)->Left > 0))
                if (index != -1)
                {
                    if (tasks.at(j)->getDeadline() < min_deadline)
                    {
                        index = j;
                        min_deadline = tasks.at(j)->getDeadline();
                    }
                }
                else
                {
                    index = j;
                    min_deadline = tasks.at(j)->getDeadline();
                }

        // assign the task to the processor if found

        if (index != -1)
        {
            if (processor.at(i)->Task_id != index)
            {
                if (processor.at(i)->Task_id != -1)
                {
                    processor.at(i)->Preemtions++;
                    chain->setEvent(processor.at(i)->Task_id * 3 + 2, -1);
                }

                processor.at(i)->Task_id = index;


                if (tasks.at(index)->Left > 0)
                    chain->setEvent(index * 3 + 2, chain->getTime() + tasks.at(index)->Left);
                else
                    chain->setEvent(index * 3 + 2, chain->getTime() + tasks.at(index)->getWcet());
            }

            tasks.at(index)->IsWorking = true;
        }
        else
            processor.at(i)->Task_id = -1;
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
            if (chain->getEvent(index * 3 + 3) > 0)
            {
                is_schedulable = false;
                return true;
            }

            task.at(index)->Left = task.at(index)->getWcet();
            chain->setEvent(index * 3 + 1, chain->getTime() + task.at(index)->getPeriod());
            chain->setEvent(index * 3 + 3, chain->getTime() + task.at(index)->getDeadline());

            reassignTasks(task);
        }

        if (action == 2)   // job end
        {
            chain->setEvent(index * 3 + 2, -1);
            chain->setEvent(index * 3 + 3, -1);

            processor.at(task.at(index)->Processor_id)->Task_id = -1;

            reassignTasks(task);
        }

        if (action == 3)   // job deadline (simulation failed if got here)
        {
            is_schedulable = false;
            return true;
        }
    }

    return false;
}
