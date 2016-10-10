#ifndef GENERATOR_ABSTRACT_H
#define GENERATOR_ABSTRACT_H

#include <vector>
#include <stdlib.h>
#include <memory>
#include <time.h>

#include "configuration.h"
#include "task.h"

using namespace std;

class GeneratorAbstract
{
public:

    GeneratorAbstract(Configuration *configuration);

    virtual vector<Task *> Generate() = 0;

protected:

    Configuration *configuration;

    vector<Task *> result;

    double random(double min, double max);
};



#endif // GENERATOR_ABSTRACT_H

