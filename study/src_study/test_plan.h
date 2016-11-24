#ifndef TEST_PLAN_H
#define TEST_PLAN_H

#include <vector>
#include <fstream>

using namespace std;

class TestPlan
{
public:

    TestPlan(char *input_file_path);

    int processor_num;

    vector<double> utilisation;

    vector<int> task_num;
};

#endif // TEST_PLAN_H
