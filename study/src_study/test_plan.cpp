#include "test_plan.h"

TestPlan::TestPlan(char *input_file_path)
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
