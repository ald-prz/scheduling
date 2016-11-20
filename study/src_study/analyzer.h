#ifndef ANALYZER_H
#define ANALYZER_H

#include <stdlib.h>
#include <vector>

#include "src_generator/configuration.h"
#include "src_generator/generator.h"
#include "src_simulator/simulator_partitioned.h"
#include "src_simulator/simulator_global.h"
#include "src_simulator/minimum_determiner.h"
#include "src_study/task.h"


using namespace std;

class Analyzer
{
public:

    Analyzer()
    {
        utilisation = {1.0, 5.0, 10.0, 25.0, 50.0, 75.0, 90.0, 95.0, 99.0, 100.0};
        task_num = {1, 5, 10};

        vector<double> row_double;
        vector<int> row_int;
        vector<bool> row_bool;
        for (int i = 0; i < utilisation.size(); i++)
        {
            row_double.push_back(0.0);
            row_int.push_back(0);
            row_bool.push_back(false);
        }

        for (int i = 0; i < task_num.size(); i++)
        {
            load_p.push_back(row_double);
            load_g.push_back(row_double);
            processor_p.push_back(row_int);
            processor_g.push_back(row_int);
            schedulable_p.push_back(row_bool);
            schedulable_g.push_back(row_bool);
        }
    }

    void Analyze()
    {

        for (int i = 0; i < task_num.size(); i++)
            for (int j = 0; j < utilisation.size(); j++)
            {
                Configuration c(utilisation.at(j), task_num.at(i), "");
                Generator generator(&c);
                vector<Task *> task = generator.Generate();
                int min = MinimumDeterminer::Determine(task, true);
                processor_g.at(i).at(j) = min;
            }


    }

protected:

    vector<double> utilisation;
    vector<int> task_num;

    vector<vector<double>> load_p, load_g;
    vector<vector<int>> processor_p, processor_g;
    vector<vector<bool>> schedulable_p, schedulable_g;
};

#endif // ANALYZER_H
