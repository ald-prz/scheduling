#ifndef TASK_H
#define TASK_H

class Task
{
public:

    Task();
    Task(double offset, double period, double deadline, double wcet);

    double getOffset() const;
    void setOffset(double value);

    double getPeriod() const;
    void setPeriod(double value);

    double getDeadline() const;
    void setDeadline(double value);

    double getWcet() const;
    void setWcet(double value);

private:

    double offset;

    double period;

    double deadline;

    double wcet;
};

#endif // TASK_H


