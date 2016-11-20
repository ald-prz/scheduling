#ifndef BEST_FIT_PACKER_H
#define BEST_FIT_PACKER_H

#include <vector>

#include "src_study/task.h"

using namespace std;

class BestFitPacker
{
public:

    BestFitPacker(vector<Task*> task, int processor_num);

    /*!
     * \brief Packs tasks over [processor_num] processors according to Best Fit Strategy (sets Task->Processor_id)
     * \return Flag if packing is done successfully
     */
    bool Pack();

protected:

    unsigned int processor_num;

    vector<Task*> task;
};

#endif // BEST_FIT_PACKER_H
