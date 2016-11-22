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

    SimulatorPartitioned(vector<Task*> task, int processor_num, bool show_simulation);

    SimulationResult Simulate() override;

protected:

    /*!
     * \brief Reassigns tasks over the processors according to partitioned DM strategy
     * \param tasks Vector of tasks which should be reassigned
     */
    void reassignTasks(vector<Task*> task);

    /*!
     * \brief Processes next event (simulation end, job start, job end, job deadline missing)
     * \param Index of the next event
     * \return Flag if simulation should stop
     */
    bool processNextEvent(int event);


    void calculateMaxOffset() override;

    void calculateHyperperiod() override;

    /*!
     * \brief Flag if packing was carried out successully
     */
    bool packedSuccessfully;
};

#endif // SIMULATOR_PARTITIONED_H
