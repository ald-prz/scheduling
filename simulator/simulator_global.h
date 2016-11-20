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

    /*!
     * \brief Processes next event (simulation end, job start, job end, job deadline missing)
     * \param Index of the next event
     * \return Flag if simulation should stop
     */
    bool processNextEvent(int event);

    /*!
     * \brief Construct task_sorted index for task vector
     */
    void sortTasks();

    /*!
     * \brief Vector of indexes of free processors
     */
    vector<int> free_processor_id;    

    /*!
     * \brief Index of sorted tasks
     */
    vector<Task*> task_sorted;
};

#endif // SIMULATOR_GLOBAL_H
