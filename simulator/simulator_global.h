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

        chain = new FutureEventChain(event);
    }

    virtual void Simulate() override
    {

    }

protected:

    FutureEventChain *chain;
};

#endif // SIMULATOR_GLOBAL_H
