#ifndef SIMULATION_RESULT_H
#define SIMULATION_RESULT_H

#include <vector>
#include <iostream>
#include <fstream>

#include "processor.h"

using namespace std;

/*!
 * \brief A class instatnce is an object which is returned by any simulator after simulation
 */
class SimulationResult
{
public:

    SimulationResult(vector<Processor*> processors, bool is_schedulable, long long simulation_time, long long intended_time);

    void Print(char *output_file_path);

    bool IsSchedulable;

    double Total_utilisation;

    vector<Processor*> Processors;

    int Preemtions;

    long long Idle;

protected:

    void recalculateUtilisations();
};

#endif // SIMULATION_RESULT_H
