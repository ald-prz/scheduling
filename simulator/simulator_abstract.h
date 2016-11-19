#ifndef SIMULATOR_ABSTRACT_H
#define SIMULATOR_ABSTRACT_H

#include <vector>

#include "task.h"
#include "least_common_multiple.h"
#include "processor.h"
#include "simulation_result.h"
#include "future_event_chain.h"

using namespace std;

class SimulatorAbstract
{
public:

    SimulatorAbstract(vector<Task*> tasks, int processor_number, bool show_simulation);

    virtual SimulationResult Simulate() = 0;

protected:

    vector<Task*> tasks;

    vector<Processor*> processors;

    int processor_number;

    long long hyper_period;

    long long max_offset;

    bool show_simulation;

    bool schedulable;

    FutureEventChain *chain;

private:

    void setAttributes();

    void initializeProcessors();
};

#endif // SIMULATOR_ABSTRACT_H
