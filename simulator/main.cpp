#include <iostream>
#include <string.h>
#include <vector>

#include "simulator_abstract.h"
#include "simulator_global.h"
#include "future_event_chain.h"
#include "task_reader.h"
#include "least_common_multiple.h"
#include "simulation_result.h"
#include "best_fit_packer.h"

using namespace std;

bool is_global;
char *task_file_address;
int processor_num;

void GetArguments(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    GetArguments(argc, argv);


    TaskReader task_loader(task_file_address);
    vector<Task*> task = task_loader.Read();

    BestFitPacker packer(task, processor_num);
    bool t = packer.Pack();

    SimulatorAbstract *simulator;

    if (is_global)
        simulator = new SimulatorGlobal(task, processor_num, true);

    SimulationResult result = simulator->Simulate();
    result.Print("result.txt");

    cout << "finished" << endl;

    return 0;
}


void GetArguments(int argc, char *argv[])
{
    if (argc < 4)
        throw exception();
    is_global = strcmp(argv[1], "-g") == 0;
    task_file_address = argv[2];
    processor_num = atoi(argv[3]);
}
