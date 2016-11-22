#include "simulator_partitioned.h"

SimulatorPartitioned::SimulatorPartitioned(vector<Task *> task, int processor_number, bool show_simulation) : SimulatorAbstract(task, processor_number, show_simulation)
{
    BestFitPacker packer(task, processor_number);
    packedSuccessfully = packer.Pack();
}

SimulationResult SimulatorPartitioned::Simulate()
{
    this->set();

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
                    chain->setEvent(processor.size() + processor.at(i)->Task_id * 3 + 1, -1);
                }

                processor.at(i)->Task_id = index;


                if (tasks.at(index)->Left > 0)
                    chain->setEvent(processor.size() + index * 3 + 1, chain->getTime() + tasks.at(index)->Left);
                else
                    chain->setEvent(processor.size() + index * 3 + 1, chain->getTime() + tasks.at(index)->getWcet());
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
        if (chain->getEvent(processor.size() + index * 3 + 2) > 0)
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

        processor.at(task.at(index)->Processor_id)->Task_id = -1;

        reassignTasks(task);
    }

    if (action == 3)   // job deadline (simulation failed if got here)
    {
        is_schedulable = false;
        return true;
    }

    return false;
}

void SimulatorPartitioned::calculateMaxOffset()
{
    int max_offset;

    for (int i = 0; i < processor.size(); i++)
    {
        max_offset = -1;

        for (int j = 0; j < task.size(); j++)
            if (task.at(j)->Processor_id == i)
            {
                if (max_offset == -1)
                    max_offset = task.at(j)->getOffset();
                else
                    if (max_offset < task.at(j)->getOffset())
                        max_offset = task.at(j)->getOffset();
            }

        processor.at(i)->Max_offset = max_offset;
    }
}

void SimulatorPartitioned::calculateHyperperiod()
{
    vector<long long> periods;

    for (int i = 0; i < processor.size(); i++)
    {
        periods.clear();

        for (int j = 0; j < task.size(); j++)
            if (task.at(j)->Processor_id == i)
                periods.push_back(task.at(j)->getPeriod());

        if (periods.size() > 0)
            processor.at(i)->Hyper_period = LeastCommonMultiple::Calculate(periods);
        else
            processor.at(i)->Hyper_period = -1;
    }
}
