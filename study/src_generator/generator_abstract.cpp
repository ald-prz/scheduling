#include "generator_abstract.h"



GeneratorAbstract::GeneratorAbstract(Configuration *configuration)
{
    this->configuration = configuration;

    srand(time(NULL));

    for (int i = 0; i < this->configuration->getTaskNumber(); i++)
        this->result.push_back(new Task());
}

double GeneratorAbstract::random(double min, double max)
{
    return (double)(rand()) / RAND_MAX * (max - min) + min;
}
