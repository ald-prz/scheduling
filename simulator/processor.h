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
};

#endif // PROCESSOR_H
