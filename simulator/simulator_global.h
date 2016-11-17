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

    SimulatorGlobal(vector<Task*> tasks, int processor_number, bool show_simulation);

    virtual void Simulate() override;

protected:

    /*!
     * \brief reassignTasks Reassigns tasks over the processors
     * \param tasks Task vector for which tasks should be reassigned
     * Reassignment works according to DM global strategy.
     * As result of work it changes tasks and processors assignment attributes
     */
    void reassignTasks(vector<Task*> tasks);

    vector<int> free_processor_id;

    FutureEventChain *chain;
};

#endif // SIMULATOR_GLOBAL_H

