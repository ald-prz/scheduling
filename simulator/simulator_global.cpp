#include "simulator_global.h"

SimulatorGlobal::SimulatorGlobal(vector<Task *> tasks, int processor_number, bool show_simulation) : SimulatorAbstract(tasks, processor_number, show_simulation)
{
    sortTasks();

    for (int i = 0; i < processor_number; i++)
        free_processor_id.push_back(processor_number - i - 1);
}

SimulationResult SimulatorGlobal::Simulate()
{
    if (processor.size() > 0)
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
    }
    else
        schedulable = false;

    return SimulationResult(processor, schedulable, chain->getTime(), chain->getEvent(0));
}

void SimulatorGlobal::reassignTasks(vector<Task *> tasks)
{
    // memorize previous state of each task

    for (unsigned int i = 0; i < tasks.size(); i++)
        tasks.at(i)->MemorizeWorking();

    // unassign all tasks

    for (unsigned int i = 0; i < task_sorted.size(); i++)
        task_sorted.at(i)->IsWorking = false;

    // reassign n most priorited tasks

    int processors_free = this->processor_num;

    for (unsigned int i = 0; i < task_sorted.size(); i++)
        if (processors_free > 0)
        {
            if (task_sorted.at(i)->Left > 0)
            {
                task_sorted.at(i)->IsWorking = true;
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
            processor.at(tasks.at(i)->Processor_id)->Task_id = -1;

            if (tasks.at(i)->Left > 0)
                processor.at(tasks.at(i)->Processor_id)->Preemtions++;
            else
                chain->setEvent(i * 3 + 3, -1);

            chain->setEvent(i * 3 + 2, -1);

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

            processor.at(tasks.at(i)->Processor_id)->Task_id = tasks.at(i)->Task_id;

            if (tasks.at(i)->Left > 0)
                chain->setEvent(i * 3 + 2, chain->getTime() + tasks.at(i)->Left);
            else
                chain->setEvent(i * 3 + 2, chain->getTime() + tasks.at(i)->getWcet());
        }
    }
}

/*!
 * \brief Processes the next event in the event list according to FEC algorithm
 * \param event Index of the next event
 * \return Flag if must finish the simulation
 */
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
            task.at(index)->Left = task.at(index)->getWcet();
            chain->setEvent(index * 3 + 1, chain->getTime() + task.at(index)->getPeriod());
            chain->setEvent(index * 3 + 3, chain->getTime() + task.at(index)->getDeadline());

            reassignTasks(task);
        }

        if (action == 2)   // job end
        {
            chain->setEvent(index * 3 + 2, -1);
            chain->setEvent(index * 3 + 3, -1);

            reassignTasks(task);
        }

        if (action == 3)   // job deadline (simulation failed if got here)
        {
            schedulable = false;
            return true;
        }
    }

    return false;
}

void SimulatorGlobal::sortTasks()
{
    task_sorted = task;

    for (unsigned int i = 0; i < task_sorted.size() - 1; i++) // sort them by period in ascending order
        for (unsigned int j = 0; j <= i; j++)
            if (task_sorted.at(j)->getPeriod() > task_sorted.at(j + 1)->getPeriod())
            {
                Task *change;
                change = task_sorted.at(j);
                task_sorted.at(j) = task_sorted.at(j + 1);
                task_sorted.at(j + 1) = change;
            }
}
