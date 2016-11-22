#include "processor.h"

Processor::Processor(int id)
{
    this->Id = id;
    Idle = 0;
    Utilisation = -1.0;
    Preemtions = 0;
    Task_id = -1;
    Hyper_period = -1;
    Simulation_time = -1;
    Intended_time = -1;
}
