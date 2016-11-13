#ifndef SIMULATOR_GLOBAL_H
#define SIMULATOR_GLOBAL_H

#include <simulator_abstract.h>

class SimulatorGlobal : public SimulatorAbstract
{
public:

    SimulatorGlobal(vector<Task> tasks, int processor_number) : SimulatorAbstract(tasks, processor_number)
    {
    }

    virtual void Simulate() override
    {

    }
};

#endif // SIMULATOR_GLOBAL_H
