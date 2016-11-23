#ifndef SIMULATOR_ABSTRACT_H
#define SIMULATOR_ABSTRACT_H

#include <vector>

#include "src_study/task.h"
#include "least_common_multiple.h"
#include "processor.h"
#include "simulation_result.h"
#include "future_event_chain.h"

using namespace std;

class SimulatorAbstract
{
public:

    SimulatorAbstract(vector<Task*> task, int processor_num, bool show_simulation);

    virtual SimulationResult Simulate() = 0;

protected:

    vector<Task*> task;

    vector<Processor*> processor;

    int processor_num;

    bool show_simulation;

    bool is_schedulable;

    FutureEventChain *chain;

    /*!
     * \brief Recalculates how much work left for each job after the passed timespan
     */
    void recalculateLeft();

    /*!
     * \brief Adds idles for non-working tasks for the passed timespan
     */
    void recalculateIdle();

    /*!
     * \brief Outputs the status of the task distribution of the current step to command line
     */
    void showSimulationStep();

    /*!
     * \brief Preparation before simulation (initializes processors, calculates Max_offests and Hyper_periods, sets events
     */
    void set();

    /*!
     * \brief Calculates max_offset
     */
    virtual void calculateMaxOffset() = 0;

    /*!
     * \brief Calculates hyper_period
     */
    virtual void calculateHyperperiod() = 0;

    /*!
     * \brief Initializes processor vector
     */
    void initializeProcessors();
};

#endif // SIMULATOR_ABSTRACT_H
