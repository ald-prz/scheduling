#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor
{
public:

    Processor(int id);

    int Id;

    long long Idle;

    double Utilisation;

    long long Preemtions;

    int Task_id;

    long long Hyper_period;

    long long Max_offset;

    long long Simulation_time; // actual simulation time

    long long Intended_time; // interval I
};

#endif // PROCESSOR_H
