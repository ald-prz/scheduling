#include "configuration.h"



Configuration::Configuration(double utilisation, int task_number, string output_filename)
{
    this->utilisation = utilisation;
    this->task_number = task_number;
    this->output_filename = output_filename;
}

double Configuration::getUtilisation() const
{
    return utilisation;
}

int Configuration::getTask_number() const
{
    return task_number;
}

string Configuration::getOutput_filename() const
{
    return output_filename;
}
