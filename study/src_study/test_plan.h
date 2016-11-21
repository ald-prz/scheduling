#ifndef TEST_PLAN_H
#define TEST_PLAN_H

#include <vector>
#include <fstream>

using namespace std;

class TestPlan
{
public:

    TestPlan(char *input_file_path)
    {
        char *buffer = new char[30];
        ifstream file;
        file.open(input_file_path);

        file >> buffer;
        processor_num = atoi(buffer);

        file >> buffer;
        int task_num_num = atoi(buffer);

        for (int i = 0; i < task_num_num; i++)
        {
            file >> buffer;
            task_num.push_back(atoi(buffer));
        }

        file >> buffer;
        int utilisation_num = atoi(buffer);

        for (int i = 0; i < utilisation_num; i++)
        {
            file >> buffer;
            utilisation.push_back(atof(buffer));
        }
    }

    int processor_num;

    vector<double> utilisation;

    vector<int> task_num;
};

#endif // TEST_PLAN_H
