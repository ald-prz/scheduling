#ifndef SIMULATOR_ABSTRACT_H
#define SIMULATOR_ABSTRACT_H

#include <vector>

#include "task.h"
#include "least_common_multiple.h"
#include "processor.h"

using namespace std;

class SimulatorAbstract
{
public:

    SimulatorAbstract(vector<Task*> tasks, int processor_number, bool show_simulation);

    virtual void Simulate() = 0;

protected:

    vector<Task*> tasks;
    vector<Task*> tasks_sorted;

    vector<Processor*> processors;

    int processor_number;

    long long hyper_period;

    long long max_offset;

    bool show_simulation;

private:

    void setAttributes();

    void sortTasks();

    void initializeProcessors();

};

#endif // SIMULATOR_ABSTRACT_H


