#include "task.h"

Task::Task()
{
    this->offset = 0;
    this->period = 0;
    this->deadline = 0;;
    this->wcet = 0;
    this->left = 0;
    this->is_working = false;
    this->was_working = false;
    this->task_id = -1;
    this->processor_id = -1;
}

Task::Task(long long offset, long long period, long long deadline, long long wcet)
{
    this->offset = offset;
    this->period = period;
    this->deadline = deadline;
    this->wcet = wcet;
}

long long Task::GetOffset() const
{
    return offset;
}

void Task::SetOffset(long long value)
{
    offset = value;
}

long long Task::GetPeriod() const
{
    return period;
}

void Task::SetPeriod(long long value)
{
    period = value;
}

long long Task::GetDeadline() const
{
    return deadline;
}

void Task::SetDeadline(long long value)
{
    deadline = value;
}

long long Task::GetWcet() const
{
    return wcet;
}

void Task::SetWcet(long long value)
{
    wcet = value;
}

void Task::MemorizeWorking()
{
    was_working = is_working;
}

long long Task::GetProcessorId() const
{
    return processor_id;
}

void Task::SetProcessorId(long long value)
{
    processor_id = value;
}

long long Task::GetTaskId() const
{
    return task_id;
}

void Task::SetTaskId(long long value)
{
    task_id = value;
}

bool Task::GetWasWorking() const
{
    return was_working;
}

void Task::SetWasWorking(bool value)
{
    was_working = value;
}

bool Task::GetIsWorking() const
{
    return is_working;
}

void Task::SetIsWorking(bool value)
{
    is_working = value;
}

long long Task::GetLeft() const
{
    return left;
}

void Task::SetLeft(long long value)
{
    left = value;
}

void Task::SubstractLeft(long long value)
{
    this->left -= value;
}
