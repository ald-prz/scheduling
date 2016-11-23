#include "simulator_global.h"

SimulatorGlobal::SimulatorGlobal(vector<Task *> task, int processor_number, bool show_simulation) : SimulatorAbstract(task, processor_number, show_simulation)
{
    sortTasks();

    for (int i = 0; i < processor_number; i++)
        free_processor_id.push_back(processor_number - i - 1);


    // Global DM must not have task pre-assignment over the processors

    for (int i = 0; i < task.size(); i++)
        task.at(i)->Processor_id = -1;
}

SimulationResult SimulatorGlobal::Simulate()
{
    this->set();

    if (processor.size() > 0)
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

    for (unsigned int i = 0; i < tasks.size(); i++)                 // for every task
    {
        if (tasks.at(i)->WasWorking && !tasks.at(i)->IsWorking)        // if [i] job stopped working
        {
            free_processor_id.push_back(tasks.at(i)->Processor_id);    // add its processor to free processors for redistribution
            processor.at(tasks.at(i)->Processor_id)->Task_id = -1;     // free the processor of this task

            if (tasks.at(i)->Left > 0)                                 // if the finish was a preemtion
                processor.at(tasks.at(i)->Processor_id)->Preemtions++; // catch a preemtion
            else
                chain->setEvent(processor.size() + i * 3 + 2, -1);  // successfully finished before deadline for [i] job

            chain->setEvent(processor.size() + i * 3 + 1, -1);      // do not expect job finish (cause stopped)

            tasks.at(i)->Processor_id = -1;                         // unassign task processor
        }
    }

    // process tasks which started working

    for (unsigned int i = 0; i < tasks.size(); i++)
    {
        if (!tasks.at(i)->WasWorking && tasks.at(i)->IsWorking)
        {
            tasks.at(i)->Processor_id = free_processor_id[free_processor_id.size() - 1];
            free_processor_id.pop_back();

            processor.at(tasks.at(i)->Processor_id)->Task_id = i;

            if (tasks.at(i)->Left > 0)
                chain->setEvent(processor.size() + i * 3 + 1, chain->getTime() + tasks.at(i)->Left);
            else
                chain->setEvent(processor.size() + i * 3 + 1, chain->getTime() + tasks.at(i)->getWcet());
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
    int index, action;
    bool mustFinish = true;

    // check if we still have processore to simulate

    for (int i = 0; i < processor.size(); i++)
        if (chain->getEvent(i) > 0)
        {
            mustFinish = false;
            break;
        }

    if (mustFinish) // if no then finish
        return true;

    // determine index (of task or processor depending on action type ) and action type

    if (event >= processor.size())
    {
        event -= processor.size();
        index = event / 3;     // index of task which event is applied to
        action = event - index * 3 + 1;  // type of action which is applied by the task
    }
    else
    {
        index = event;
        action = 0;
    }

    // process the next event

    if (action == 0)
    {
        chain->setEvent(index, -1);
        processor.at(index)->Task_id = -1;
    }

    if (action == 1)   // job start
    {
        if (chain->getEvent(processor.size() + index * 3 + 0) < chain->getEvent(processor.size() + index * 3 + 2))
        {
            is_schedulable = false;
            return true;
        }

        task.at(index)->Left = task.at(index)->getWcet();
        chain->setEvent(processor.size() + index * 3 + 0, chain->getTime() + task.at(index)->getPeriod());
        chain->setEvent(processor.size() + index * 3 + 2, chain->getTime() + task.at(index)->getDeadline());

        reassignTasks(task);
    }

    if (action == 2)   // job end
    {
        chain->setEvent(processor.size() + index * 3 + 1, -1);
        chain->setEvent(processor.size() + index * 3 + 2, -1);

        reassignTasks(task);
    }

    if (action == 3)   // job deadline (simulation failed if got here)
    {
        is_schedulable = false;
        return true;
    }

    return false;
}

void SimulatorGlobal::sortTasks()
{
    task_sorted = task;

    for (unsigned int i = 0; i < task_sorted.size() - 1; i++) // sort them by period in ascending order
        for (unsigned int j = 0; j <= i; j++)
            if (task_sorted.at(j)->getDeadline() > task_sorted.at(j + 1)->getDeadline())
            {
                Task *change;
                change = task_sorted.at(j);
                task_sorted.at(j) = task_sorted.at(j + 1);
                task_sorted.at(j + 1) = change;
            }
}

void SimulatorGlobal::calculateMaxOffset()
{
    this->max_offset = task.at(0)->getOffset();

    for (unsigned int i = 1; i < task.size(); i++)
        if (max_offset < task.at(i)->getOffset())
            max_offset = task.at(i)->getOffset();

    for (unsigned int i = 0; i < processor.size(); i++)
        processor.at(i)->Max_offset = this->max_offset;
}

void SimulatorGlobal::calculateHyperperiod()
{
    vector<long long> periods;

    for (unsigned int i = 0; i < task.size(); i++)
        periods.push_back(task[i]->getPeriod());

    this->hyper_period = LeastCommonMultiple::Calculate(periods);

    for (unsigned int i = 0; i < processor.size(); i++)
        processor.at(i)->Hyper_period = this->hyper_period;
}
