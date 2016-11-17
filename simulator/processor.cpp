#include "processor.h"

Processor::Processor(int id)
{
    this->id = id;
    idle = 0;
    utilisation = 0.0;
    preemtions = 0;
    task_id = -1;
}

int Processor::GetTaskId() const
{
    return task_id;
}

void Processor::SetTaskId(int value)
{
    task_id = value;
}

long long Processor::GetPreemtions() const
{
    return preemtions;
}

void Processor::SetPreemtions(long long value)
{
    preemtions = value;
}

double Processor::GetUtilisation() const
{
    return utilisation;
}

void Processor::SetUtilisation(double value)
{
    utilisation = value;
}

long long Processor::GetIdle() const
{
    return idle;
}

void Processor::SetIdle(long long value)
{
    idle = value;
}

int Processor::GetId() const
{
    return id;
}

void Processor::SetId(int value)
{
    id = value;
}
