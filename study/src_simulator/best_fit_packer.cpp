#include "best_fit_packer.h"

BestFitPacker::BestFitPacker(vector<Task *> task, int processor_num)
{
    this->task = task;
    this->processor_num = processor_num;
}

bool BestFitPacker::Pack()
{
    vector<double> utilisation_left;

    // set initial full-available processors

    for (unsigned int i = 0; i < processor_num; i++)
        utilisation_left.push_back(1.0);

    // assigns tasks to processors for future partitioned simulation

    for (unsigned int i = 0; i < task.size(); i++)
    {
        int min_index = -1;
        int min_value = 0.0;

        // find an appropriate processor

        for (unsigned int j = 0; j < processor_num; j++)
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

        if (min_index == -1) // not found an appropriate processor
            return false;
        else                 // found one
        {
            utilisation_left.at(min_index) -= task.at(i)->Utilisation;
            task.at(i)->Processor_id = min_index;
        }
    }

    return true;
}
