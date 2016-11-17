#ifndef SIMULATOR_GLOBAL_H
#define SIMULATOR_GLOBAL_H

#include <vector>
#include <algorithm>
#include <iostream>

#include "simulator_abstract.h"
#include "future_event_chain.h"

class SimulatorGlobal : public SimulatorAbstract
{
public:

    SimulatorGlobal(vector<Task*> tasks, int processor_number, bool show_simulation) : SimulatorAbstract(tasks, processor_number, show_simulation)
    {
        vector<int> event;
        event.push_back(max_offset + 2 * hyper_period);

        for (unsigned int i = 0; i < tasks.size(); i++)
        {
            event.push_back(tasks.at(i)->getOffset());
            event.push_back(-1);
            event.push_back(-1);
        }

        for (int i = 0; i < processor_number; i++)
            free_processor_id.push_back(i);

        chain = new FutureEventChain(event);
    }

    virtual void Simulate() override
    {
        while (true)
        {
            int event = chain->DetermineNextEvent();

            if (chain->Last_difference > 0)
                for (unsigned int i = 0; i < tasks.size(); i++)
                    if ((tasks.at(i)->Left > 0) && (tasks.at(i)->IsWorking))
                        tasks.at(i)->Left -= chain->Last_difference;

            if (this->show_simulation)
                if (chain->Last_difference > 0)
                {
                    cout << "[" << chain->getTime() - chain->Last_difference << ";" << chain->getTime() << "]" << endl;

                }

            if (event == 0)
                break;
            else
            {
                int index = (event - 1) / 3;
                int action = event - index * 3;

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

                if (action == 3)   // job deadline
                {

                }
            }

            int a = 1; // set breakpoint here
        }
    }

protected:

    // input: the current list of tasks
    // output: affects the chain
    void reassignTasks(vector<Task*> tasks)
    {
        for (unsigned int i = 0; i < tasks.size(); i++)  // select awaiting jobs
            tasks.at(i)->MemorizeWorking();


        for (unsigned int i = 0; i < tasks_sorted.size(); i++) // unassign all tasks
            tasks_sorted.at(i)->IsWorking = false;

        int processors_free = this->processor_number; // reassign n most priorited tasks

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

        for (unsigned int i = 0; i < tasks.size(); i++)
        {
            if (tasks.at(i)->WasWorking && !tasks.at(i)->IsWorking)
            {
                free_processor_id.push_back(tasks.at(i)->Processor_Id);
                tasks.at(i)->Processor_Id = -1;
            }
        }

        for (unsigned int i = 0; i < tasks.size(); i++)
        {
            if (!tasks.at(i)->WasWorking && tasks.at(i)->IsWorking)
            {
                tasks.at(i)->Processor_Id = free_processor_id[free_processor_id.size() - 1];
                free_processor_id.pop_back();

                if (tasks.at(i)->Left > 0)
                    chain->setEvent(i * 3 + 2, chain->getTime() + tasks.at(i)->Left);
                else
                    chain->setEvent(i * 3 + 2, chain->getTime() + tasks.at(i)->getWcet());
            }
        }
    }

    vector<int> free_processor_id;

    FutureEventChain *chain;
};

#endif // SIMULATOR_GLOBAL_H
