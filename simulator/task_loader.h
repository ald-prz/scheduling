#ifndef TASK_LOADER_H
#define TASK_LOADER_H

#include <iostream>
#include <fstream>
#include <vector>

#include "task.h"

using namespace std;

class TaskReader
{
public:
    TaskReader(char *task_file_addess)
    {
        this->task_file_addess = task_file_addess;
    }

    vector<Task> Read()
    {
        ifstream myfile;
        myfile.open(task_file_addess);
        vector<Task> *result = new vector<Task>();

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

            result->push_back(*task);
        }

        myfile.close();

        return *result;
    }

protected:
    char *task_file_addess;
};

#endif // TASK_LOADER_H
