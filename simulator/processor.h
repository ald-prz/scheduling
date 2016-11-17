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
    }

    int Id;
    long long Idle;
    double Utilisation;
    long long Preemtions;


};

#endif // PROCESSOR_H
