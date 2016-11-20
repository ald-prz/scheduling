#ifndef MINIMUMDETERMINER_H
#define MINIMUMDETERMINER_H

#include <vector>

#include "simulator_abstract.h"
#include "simulator_global.h"
#include "simulator_partitioned.h"

using namespace std;

class MinimumDeterminer
{
public:

    static int Determine(vector<Task*> task, bool is_global);
};

#endif // MINIMUMDETERMINER_H
