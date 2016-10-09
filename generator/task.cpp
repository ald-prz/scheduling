#include "task.h"




Task::Task()
{
    this->offset = 0.0;
    this->period = 0.0;
    this->deadline = 0.0;;
    this->wcet = 0.0;
}

Task::Task(double offset, double period, double deadline, double wcet)
{
    this->offset = offset;
    this->period = period;
    this->deadline = deadline;
    this->wcet = wcet;
}

double Task::getOffset() const
{
    return offset;
}

void Task::setOffset(double value)
{
    offset = value;
}

double Task::getPeriod() const
{
    return period;
}

void Task::setPeriod(double value)
{
    period = value;
}

double Task::getDeadline() const
{
    return deadline;
}

void Task::setDeadline(double value)
{
    deadline = value;
}

double Task::getWcet() const
{
    return wcet;
}

void Task::setWcet(double value)
{
    wcet = value;
}
