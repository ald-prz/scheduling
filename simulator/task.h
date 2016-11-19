#ifndef TASK_H
#define TASK_H

class Task
{
public:

    Task();

    Task(long long offset, long long period, long long deadline, long long wcet);

    long long getOffset() const;
    void setOffset(long long value);

    long long getPeriod() const;
    void setPeriod(long long value);

    long long getDeadline() const;
    void setDeadline(long long value);

    long long getWcet() const;
    void setWcet(long long value);

    double Utilisation;

    void MemorizeWorking();

    long long Left; // time left to finish the current job

    bool IsWorking; // is currently working

    bool WasWorking; // was working at previous step

    long long Processor_id;

    long long Task_id;

private:

    long long offset;

    long long period;

    long long deadline;

    long long wcet;
};

#endif // TASK_H


