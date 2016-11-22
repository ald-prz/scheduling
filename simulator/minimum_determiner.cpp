#include "minimum_determiner.h"

int MinimumDeterminer::Determine(vector<Task *> task, bool is_global)
{
    SimulatorAbstract *simulator;

    for (int i = 1; i <= task.size(); i++) // increment processor number until feasible
    {
        if (is_global)
            simulator = new SimulatorGlobal(task, i, false);
        else
            simulator = new SimulatorPartitioned(task, i, false);

        SimulationResult result = simulator->Simulate();

        if (result.IsSchedulable)
            return i;
    }

    // if [task.size] processors is not enough then not feasible

    return -1;
}