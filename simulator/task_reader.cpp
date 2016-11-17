#include "task_reader.h"

TaskReader::TaskReader(char *task_file_addess)
{
    this->task_file_path = task_file_addess;
}

vector<Task *> TaskReader::Read()
{
    ifstream myfile;
    myfile.open(task_file_path);
    vector<Task*> result;

    int id = 0;

    for (char *buffer = new char[20]; !myfile.eof();)
    {
        Task* task = new Task();

        sprintf(buffer, "\0");

        myfile >> buffer;
        task->SetOffset(atoi(buffer));

        if (strcmp(buffer, "\0") == 0)
        {
            delete buffer;
            delete task;
            break;
        }

        myfile >> buffer;
        task->SetPeriod(atoi(buffer));

        myfile >> buffer;
        task->SetDeadline(atoi(buffer));

        myfile >> buffer;
        task->SetWcet(atoi(buffer));

        task->SetTaskId(id++);

        result.push_back(task);
    }

    myfile.close();

    return result;
}
