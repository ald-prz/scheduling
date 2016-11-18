#include "simulation_result.h"

SimulationResult::SimulationResult(vector<Processor *> processors, bool is_schedulable, long long simulation_time)
{
    this->IsSchedulable = is_schedulable;
    this->Processors = processors;
    this->Simulation_time = simulation_time;
    this->Preemtions = 0;
    this->Idle = 0;

    recalculateUtilisations();
}

void SimulationResult::Print()
{
    if (this->IsSchedulable)
    {
        cout << "[schedulable]=yes" << endl;
        cout << "[interval]=[0;" << Simulation_time << "]" << endl;

        cout << "[preemtions_total]=" << Preemtions << endl;
        for (int i = 0; i < Processors.size(); i++)
            cout << "[preemtions_" << i + 1 << "]=" << Processors.at(i)->Preemtions << endl;


        cout << "[idle_total]=" << this->Idle << endl;
        for (int i = 0; i < Processors.size(); i++)
            cout << "[idle_" << i + 1 << "]=" << Processors.at(i)->Idle << endl;

        cout << "[utilisation_total]=" << Total_utilisation * 100 << endl;
        for (int i = 0; i < Processors.size(); i++)
            cout << "[utilisation_" << i + 1 << "]=" << Processors.at(i)->Utilisation * 100 << endl;
    }
    else
    {
        cout << "[schedulable]=no" << endl;
        cout << "[interval]=[0;" << Simulation_time << "]" << endl;
    }

    cout << endl;
}

void SimulationResult::recalculateUtilisations()
{
    long long sum = 0;

    for (int i = 0; i < Processors.size(); i++)
    {
        Processors.at(i)->Utilisation = ((double)(Simulation_time - Processors.at(i)->Idle)) / Simulation_time;
        sum += Simulation_time - Processors.at(i)->Idle;
        this->Preemtions += Processors.at(i)->Preemtions;
        this->Idle += Processors.at(i)->Idle;
    }

    Total_utilisation = ((double)sum) / (Processors.size() * Simulation_time);
}
