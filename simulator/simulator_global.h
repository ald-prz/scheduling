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
            free_processor_id.push_back(processor_number - i - 1);

        chain = new FutureEventChain(event);
    }

    virtual void Simulate() override;

protected:

    /*!
     * \brief Reassigns tasks over the processors by global DM strategy
     * \param tasks Vector of tasks which should be reassigned
     */
    void reassignTasks(vector<Task*> tasks);

    void recalculateLeft();

    void recalculateIdle();

    void showSimulationStep();

    bool processNextEvent(int event);

    vector<int> free_processor_id;

    FutureEventChain *chain;
};

#endif // SIMULATOR_GLOBAL_H
