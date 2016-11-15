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

private:

    long long offset;

    long long period;

    long long deadline;

    long long wcet;
};

#endif // TASK_H


