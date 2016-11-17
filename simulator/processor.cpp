#include "processor.h"

Processor::Processor(int id)
{
    this->Id = id;
    Idle = 0;
    Utilisation = 0.0;
    Preemtions = 0;
    Task_id = -1;
}
