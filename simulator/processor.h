#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor
{
public:

    Processor(int id);

    int GetId() const;
    void SetId(int value);

    long long GetIdle() const;
    void SetIdle(long long value);

    double GetUtilisation() const;
    void SetUtilisation(double value);

    long long GetPreemtions() const;
    void SetPreemtions(long long value);

    int GetTaskId() const;
    void SetTaskId(int value);

protected:

    int id;

    long long idle;

    double utilisation;

    long long preemtions;

    int task_id;

};

#endif // PROCESSOR_H


