#include "simulator_global.h"

SimulatorGlobal::SimulatorGlobal(vector<Task *> tasks, int processor_number, bool show_simulation) : SimulatorAbstract(tasks, processor_number, show_simulation)
{
    vector<int> event;
    event.push_back(max_offset + 2 * hyper_period);

    for (unsigned int i = 0; i < tasks.size(); i++)
    {
        event.push_back(tasks.at(i)->GetOffset());
        event.push_back(-1);
        event.push_back(-1);
    }

    for (int i = 0; i < processor_number; i++)
        free_processor_id.push_back(processor_number - i - 1);

    chain = new FutureEventChain(event);
}

void SimulatorGlobal::Simulate()
{
    while (true)
    {
        int event = chain->DetermineNextEvent();

        if (chain->GetTimeDifference() > 0)
            for (unsigned int i = 0; i < tasks.size(); i++)
                if ((tasks.at(i)->GetLeft() > 0) && (tasks.at(i)->GetIsWorking()))
                    tasks.at(i)->SubstractLeft(chain->GetTimeDifference());

        if (this->show_simulation)
            if (chain->GetTimeDifference() > 0)
            {
                cout << "[" << chain->GetCurrentTime() - chain->GetTimeDifference() << ";" << chain->GetCurrentTime() << "]" << endl;

                for (int i = 0; i < processor_number; i++)
                    if (processors.at(i)->GetTaskId() != -1)
                        cout << "#" << i + 1 << " " << processors.at(i)->GetTaskId() + 1 << endl;
                    else
                        cout << "#" << i + 1 << " -" << endl;

                cout << endl;
            }

        if (event == 0)
            break;
        else
        {
            int index = (event - 1) / 3;
            int action = event - index * 3;

            if (action == 1)   // job start
            {
                tasks.at(index)->Left = tasks.at(index)->getWcet();
                chain->SetEvent(index * 3 + 1, chain->GetCurrentTime() + tasks.at(index)->getPeriod());
                chain->SetEvent(index * 3 + 3, chain->GetCurrentTime() + tasks.at(index)->getDeadline());

                reassignTasks(tasks);
            }

            if (action == 2)   // job end
            {
                chain->SetEvent(index * 3 + 2, -1);
                chain->SetEvent(index * 3 + 3, -1);

                reassignTasks(tasks);
            }

            if (action == 3)   // job deadline
            {

            }
        }

        int a = 1; // set breakpoint here
    }
}

void SimulatorGlobal::reassignTasks(vector<Task *> tasks)
{
    for (unsigned int i = 0; i < tasks.size(); i++)  // select awaiting jobs
        tasks.at(i)->MemorizeWorking();


    for (unsigned int i = 0; i < tasks_sorted.size(); i++) // unassign all tasks
        tasks_sorted.at(i)->Is_working = false;

    int processors_free = this->processor_number; // reassign n most priorited tasks

    for (unsigned int i = 0; i < tasks_sorted.size(); i++)
        if (processors_free > 0)
        {
            if (tasks_sorted.at(i)->Left > 0)
            {
                tasks_sorted.at(i)->Is_working = true;
                processors_free--;
            }
        }
        else
            break;

    for (unsigned int i = 0; i < tasks.size(); i++)
    {
        if (tasks.at(i)->Was_working && !tasks.at(i)->Is_working)
        {
            free_processor_id.push_back(tasks.at(i)->Processor_id);
            processors.at(tasks.at(i)->Processor_id)->GetTaskId() = -1;
            tasks.at(i)->GetProcessorId() = -1;
        }
    }

    for (unsigned int i = 0; i < tasks.size(); i++)
    {
        if (!tasks.at(i)->Was_working && tasks.at(i)->Is_working)
        {
            tasks.at(i)->Processor_id = free_processor_id[free_processor_id.size() - 1];
            free_processor_id.pop_back();
            processors.at(tasks.at(i)->GetProcessorId())->GetTaskId() = tasks.at(i)->GetTaskId();

            if (tasks.at(i)->Left > 0)
                chain->SetEvent(i * 3 + 2, chain->GetCurrentTime() + tasks.at(i)->Left);
            else
                chain->SetEvent(i * 3 + 2, chain->GetCurrentTime() + tasks.at(i)->getWcet());
        }
    }
}
