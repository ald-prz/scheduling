#ifndef TASK_H
#define TASK_H

class Task
{
public:

    Task();

    Task(int offset, int period, int deadline, int wcet);

    int getOffset() const;
    void setOffset(int value);

    int getPeriod() const;
    void setPeriod(int value);

    int getDeadline() const;
    void setDeadline(int value);

    int getWcet() const;
    void setWcet(int value);

    int Left; // time left to finish the current job

    bool IsWorking; // is currently working

    int Id;

private:

    int offset;

    int period;

    int deadline;

    int wcet;
};

#endif // TASK_H


