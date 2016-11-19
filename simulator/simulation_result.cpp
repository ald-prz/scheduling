#include "simulation_result.h"

SimulationResult::SimulationResult(vector<Processor*> processors, bool is_schedulable, long long simulation_time)
{
    this->IsSchedulable = is_schedulable;
    this->Processors = processors;
    this->Simulation_time = simulation_time;
    this->Preemtions = 0;
    this->Idle = 0;

    recalculateUtilisations();
}

void SimulationResult::Print(char *output_file_path)
{
    ofstream file;
    file.open(output_file_path);

    if (this->IsSchedulable)
    {
        cout << "[schedulable]=yes" << endl;
        file << "[schedulable]=yes" << endl;
        cout << "[interval]=[0;" << Simulation_time << "]" << endl;
        file << "[interval]=[0;" << Simulation_time << "]" << endl;

        cout << "[preemtions_total]=" << Preemtions << endl;
        file << "[preemtions_total]=" << Preemtions << endl;
        for (unsigned int i = 0; i < Processors.size(); i++)
        {
            cout << "[preemtions_" << i << "]=" << Processors.at(i)->Preemtions << endl;
            file << "[preemtions_" << i << "]=" << Processors.at(i)->Preemtions << endl;
        }

        cout << "[idle_total]=" << this->Idle << endl;
        file << "[idle_total]=" << this->Idle << endl;
        for (unsigned int i = 0; i < Processors.size(); i++)
        {
            cout << "[idle_" << i << "]=" << Processors.at(i)->Idle << endl;
            file << "[idle_" << i << "]=" << Processors.at(i)->Idle << endl;
        }

        cout << "[utilisation_total]=" << Total_utilisation * 100 << endl;
        file << "[utilisation_total]=" << Total_utilisation * 100 << endl;
        for (unsigned int i = 0; i < Processors.size(); i++)
        {
            cout << "[utilisation_" << i << "]=" << Processors.at(i)->Utilisation * 100 << endl;
            file << "[utilisation_" << i << "]=" << Processors.at(i)->Utilisation * 100 << endl;
        }
    }
    else
    {
        cout << "[schedulable]=no" << endl;
        cout << "[interval]=[0;" << Simulation_time << "]" << endl;
    }

    cout << endl;
    file << endl;

    file.close();
}

void SimulationResult::recalculateUtilisations()
{
    long long sum = 0;

    for (unsigned int i = 0; i < Processors.size(); i++)
    {
        Processors.at(i)->Utilisation = ((double)(Simulation_time - Processors.at(i)->Idle)) / Simulation_time;
        sum += Simulation_time - Processors.at(i)->Idle;
        this->Preemtions += Processors.at(i)->Preemtions;
        this->Idle += Processors.at(i)->Idle;
    }

    Total_utilisation = ((double)sum) / (Processors.size() * Simulation_time);
}
