#include "task.h"




Task::Task()
{
    this->offset = 0;
    this->period = 0;
    this->deadline = 0;;
    this->wcet = 0;
    this->Left = 0;
    this->IsWorking = false;
    this->WasWorking = false;
    this->TaskId = -1;
    this->Processor_Id = -1;
}

Task::Task(int offset, int period, int deadline, int wcet)
{
    this->offset = offset;
    this->period = period;
    this->deadline = deadline;
    this->wcet = wcet;
}

int Task::getOffset() const
{
    return offset;
}

void Task::setOffset(int value)
{
    offset = value;
}

int Task::getPeriod() const
{
    return period;
}

void Task::setPeriod(int value)
{
    period = value;
}

int Task::getDeadline() const
{
    return deadline;
}

void Task::setDeadline(int value)
{
    deadline = value;
}

int Task::getWcet() const
{
    return wcet;
}

void Task::setWcet(int value)
{
    wcet = value;
}
