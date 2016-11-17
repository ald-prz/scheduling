#ifndef TASK_LOADER_H
#define TASK_LOADER_H

#include <fstream>
#include <vector>
#include <string.h>

#include "task.h"

using namespace std;

class TaskReader
{
public:

    TaskReader(char *task_file_path);

    vector<Task*> Read();

protected:

    char *task_file_path;
};

#endif // TASK_LOADER_H


