#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor
{
public:

    Processor(int id)
    {
        this->Id = id;
        Idle = 0;
        Utilisation = 0.0;
        Preemtions = 0;
        Task_id = -1;
    }

    int Id;
    long long Idle;
    double Utilisation;
    long long Preemtions;
    int Task_id;


};

#endif // PROCESSOR_H
