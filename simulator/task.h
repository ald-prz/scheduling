#ifndef TASK_H
#define TASK_H

class Task
{
public:

    Task();

    Task(long long offset, long long period, long long deadline, long long wcet);

    void MemorizeWorking();

    long long GetOffset() const;
    void SetOffset(long long value);

    long long GetPeriod() const;
    void SetPeriod(long long value);

    long long GetDeadline() const;
    void SetDeadline(long long value);

    long long GetWcet() const;
    void SetWcet(long long value);

    long long GetLeft() const;
    void SetLeft(long long value);
    void SubstractLeft(long long value);

    bool GetIsWorking() const;
    void SetIsWorking(bool value);

    bool GetWasWorking() const;
    void SetWasWorking(bool value);

    long long GetProcessorId() const;
    void SetProcessorId(long long value);

    long long GetTaskId() const;
    void SetTaskId(long long value);

private:

    long long offset;

    long long period;

    long long deadline;

    long long wcet;

    long long left; // time left to finish the current job

    bool is_working; // is currently working

    bool was_working; // was working at previous step

    long long processor_id;

    long long task_id;
};





#endif // TASK_H


