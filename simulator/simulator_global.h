#ifndef SIMULATOR_GLOBAL_H
#define SIMULATOR_GLOBAL_H

#include "simulator_abstract.h"
#include "future_event_chain.h"

class SimulatorGlobal : public SimulatorAbstract
{
public:

    SimulatorGlobal(vector<Task> tasks, int processor_number) : SimulatorAbstract(tasks, processor_number)
    {
        vector<int> event;
        event.push_back(max_offset + 2 * hyper_period);

        for (int i = 0; i < tasks.size(); i++)
        {
            event.push_back(tasks.at(i).getOffset());
            event.push_back(-1);
            event.push_back(-1);
        }

        chain = new FutureEventChain(event);
    }

    virtual void Simulate() override
    {
        vector<Task> activeTasks;

        while (true)
        {
            int event = chain->DetermineNextEvent();

            if (event == 0)
                break;
            else
            {
                int index = (event - 1) / 3;
                int action = event - index * 3;

                if (action == 1)   // job start
                {
                    activeTasks.push_back(tasks.at(index));
                    chain->setEvent(index * 3 + action, chain->getTime() + tasks.at(index).getPeriod());
                }

                if (action == 2)   // job end
                {

                }

                if (action == 3)   // job deadline
                {

                }
            }
        }
    }

protected:

    FutureEventChain *chain;
};

#endif // SIMULATOR_GLOBAL_H
