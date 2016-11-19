#ifndef SIMULATOR_GLOBAL_H
#define SIMULATOR_GLOBAL_H

#include <vector>
#include <algorithm>
#include <iostream>

#include "simulator_abstract.h"
#include "simulation_result.h"

class SimulatorGlobal : public SimulatorAbstract
{
public:

    SimulatorGlobal(vector<Task*> task, int processor_num, bool show_simulation);

    SimulationResult Simulate() override;

protected:

    /*!
     * \brief Reassigns tasks over the processors according to global DM strategy
     * \param tasks Vector of tasks which should be reassigned
     */
    void reassignTasks(vector<Task*> task);

    bool processNextEvent(int event);

    void sortTasks();

    vector<int> free_processor_id;    

    vector<Task*> task_sorted;
};

#endif // SIMULATOR_GLOBAL_H
