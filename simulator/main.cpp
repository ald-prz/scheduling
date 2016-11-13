#include <iostream>
#include <string.h>
#include <vector>

#include "task_loader.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 4)
        throw exception();

    bool is_global = strcmp(argv[1], "-g") == 0;

    char *task_file_address = argv[2];

    int processor_number = atoi(argv[3]);

    TaskLoader *task_loader = new TaskLoader(task_file_address);
    vector<Task> tasks = task_loader->Execute();

    return 0;
}
