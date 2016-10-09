#include "generator_abstract.h"



GeneratorAbstract::GeneratorAbstract(Configuration *configuration)
{
    this->configuration = configuration;

    for (int i = 0; i < this->configuration->getTask_number(); i++)
        this->result.push_back(new Task());
}

double GeneratorAbstract::random(double min, double max)
{
    return (double)(rand()) / RAND_MAX * (max - min) + min;
}
