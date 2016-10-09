#ifndef GENERATOR_H
#define GENERATOR_H

#include <vector>

#include "generator_abstract.h"

using namespace std;

class Generator : public GeneratorAbstract
{
public:

    Generator(Configuration *configuration);

    virtual vector<Task *> Generate() override;
};




#endif // GENERATOR_H

