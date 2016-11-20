#ifndef TASK_LOADER_H
#define TASK_LOADER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>

#include "task.h"

using namespace std;

class TaskReader
{
public:

    TaskReader(char *task_file_address);

    vector<Task*> Read();

protected:

    char *task_file_address;
};

#endif // TASK_LOADER_H
