#ifndef SIMULATOR_PARTITIONED_H
#define SIMULATOR_PARTITIONED_H

#include <vector>
#include <algorithm>
#include <iostream>

#include "simulator_abstract.h"
#include "simulation_result.h"
#include "best_fit_packer.h"

class SimulatorPartitioned : public SimulatorAbstract
{
public:

    SimulatorPartitioned(vector<Task*> tasks, int processor_number, bool show_simulation);

    SimulationResult Simulate() override;

protected:

    /*!
     * \brief Reassigns tasks over the processors according to partitioned DM strategy
     * \param tasks Vector of tasks which should be reassigned
     */
    void reassignTasks(vector<Task*> tasks);

    void recalculateLeft();

    void recalculateIdle();

    void showSimulationStep();

    bool processNextEvent(int event);
};

#endif // SIMULATOR_PARTITIONED_H
