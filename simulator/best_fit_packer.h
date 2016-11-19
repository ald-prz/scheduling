#ifndef BEST_FIT_PACKER_H
#define BEST_FIT_PACKER_H

#include <vector>

#include "task.h"

using namespace std;

class BestFitPacker
{
public:

    BestFitPacker(vector<Task*> task, int processor_num)
    {
        this->task = task;
        this->processor_num = processor_num;
    }

    bool Pack()
    {
        vector<double> utilisation_left;

        for (int i = 0; i < processor_num; i++)
            utilisation_left.push_back(1.0);

        for (int i = 0; i < task.size(); i++)
        {
            int min_index = -1;
            int min_value = 0.0;

            for (int j = 0; j < processor_num; j++)
                if (task.at(i)->Utilisation <= utilisation_left.at(j))
                    if (min_index == -1)
                    {
                        min_index = j;
                        min_value = utilisation_left.at(j);
                    }
                    else
                        if (utilisation_left.at(j) < min_value)
                        {
                            min_index = j;
                            min_value = utilisation_left.at(j);
                        }

            if (min_index == -1)
                return false;
            else
            {
                utilisation_left.at(min_index) -= task.at(i)->Utilisation;
                task.at(i)->Processor_id = min_index;
            }
        }
    }

protected:

    int processor_num;

    vector<Task*> task;
};

#endif // BEST_FIT_PACKER_H
