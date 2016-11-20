#include "task.h"

Task::Task()
{
    this->offset = 0;
    this->period = 0;
    this->deadline = 0;;
    this->wcet = 0;
    this->Task_id = -1;
    this->Reset();
}

Task::Task(long long offset, long long period, long long deadline, long long wcet)
{
    this->offset = offset;
    this->period = period;
    this->deadline = deadline;
    this->wcet = wcet;
    this->Task_id = -1;
    this->Reset();

    if ((wcet > deadline) || (deadline > period))
        throw exception();
}

long long Task::getOffset() const
{
    return offset;
}

void Task::setOffset(long long value)
{
    offset = value;
}

long long Task::getPeriod() const
{
    return period;
}

void Task::setPeriod(long long value)
{
    period = value;

    if (this->period != 0)
        this->Utilisation = ((double) this->wcet) / this->period;
}

long long Task::getDeadline() const
{
    return deadline;
}

void Task::setDeadline(long long value)
{
    deadline = value;
}

long long Task::getWcet() const
{
    return wcet;
}

void Task::setWcet(long long value)
{
    wcet = value;

    if (this->period != 0)
        this->Utilisation = ((double) this->wcet) / this->period;
}

void Task::MemorizeWorking()
{
    WasWorking = IsWorking;
}

void Task::Reset()
{
    this->Left = 0;
    this->IsWorking = false;
    this->WasWorking = false;
    this->Processor_id = -1;
}
