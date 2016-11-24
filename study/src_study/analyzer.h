#ifndef ANALYZER_H
#define ANALYZER_H

#include <fstream>
#include <vector>

#include "src_generator/configuration.h"
#include "src_generator/generator.h"
#include "src_simulator/simulator_partitioned.h"
#include "src_simulator/simulator_global.h"
#include "src_simulator/minimum_determiner.h"
#include "src_study/task.h"
#include "src_study/test_plan.h"

using namespace std;

class Analyzer
{
public:

    Analyzer(TestPlan plan);

    void Analyze();

    void OutputToFile(char *output_file_path);

protected:

    int processor_num;
    vector<double> utilisation;
    vector<int> task_num;

    vector<vector<double>> load_p, load_g;
    vector<vector<int>> processor_p, processor_g;
    vector<vector<bool>> schedulable_p, schedulable_g;
};

#endif // ANALYZER_H
