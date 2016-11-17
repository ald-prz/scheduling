#include "task_reader.h"

TaskReader::TaskReader(char *task_file_addess)
{
    this->task_file_addess = task_file_addess;
}

vector<Task *> TaskReader::Read()
{
    ifstream myfile;
    myfile.open(task_file_addess);
    vector<Task*> result;

    int id = 0;
    for (char *buffer = new char[20]; !myfile.eof();)
    {
        Task* task = new Task();

        sprintf(buffer, "\0");

        myfile >> buffer;
        task->setOffset(atoi(buffer));

        if (strcmp(buffer, "\0") == 0)
        {
            delete buffer;
            delete task;
            break;
        }

        myfile >> buffer;
        task->setPeriod(atoi(buffer));

        myfile >> buffer;
        task->setDeadline(atoi(buffer));

        myfile >> buffer;
        task->setWcet(atoi(buffer));

        task->Task_id = id++;

        result.push_back(task);
    }

    myfile.close();

    return result;
}
