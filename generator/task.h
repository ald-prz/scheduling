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

private:

    int offset;

    int period;

    int deadline;

    int wcet;
};

#endif // TASK_H


