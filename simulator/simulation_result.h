#ifndef SIMULATION_RESULT_H
#define SIMULATION_RESULT_H

#include <vector>
#include <iostream>

#include "processor.h"

using namespace std;

class SimulationResult
{
public:

    SimulationResult(vector<Processor*> processors, bool is_schedulable, long long simulation_time);

    void Print();

    bool IsSchedulable;

    double Total_utilisation;

    vector<Processor*> Processors;

    long long Simulation_time;

    int Preemtions;

    long long Idle;

protected:

    void recalculateUtilisations();

};

#endif // SIMULATION_RESULT_H
