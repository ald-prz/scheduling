#include <iostream>
#include <string.h>
#include <vector>

#include "simulator_abstract.h"
#include "simulator_global.h"
#include "future_event_chain.h"
#include "task_loader.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 4)
        throw exception();
    bool is_global = strcmp(argv[1], "-g") == 0;
    char *task_file_address = argv[2];
    int processor_number = atoi(argv[3]);

    TaskReader *task_loader = new TaskReader(task_file_address);
    vector<Task> tasks = task_loader->Read();

    vector<int> v;
    v.push_back(3);
    v.push_back(2);
    v.push_back(4);
    FutureEventChain *chain = new FutureEventChain(v);
    int a = chain->DetermineNextEvent();

    cout << "finished" << endl;

    return 0;
}
