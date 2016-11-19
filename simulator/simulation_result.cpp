#include "simulation_result.h"

SimulationResult::SimulationResult(vector<Processor*> processors, bool is_schedulable, long long simulation_time, long long intended_time)
{
    this->IsSchedulable = is_schedulable;
    this->Processors = processors;
    this->Simulation_time = simulation_time;
    this->Intended_time = intended_time;
    this->Preemtions = 0;
    this->Idle = 0;

    recalculateUtilisations();
}

void SimulationResult::Print(char *output_file_path)
{
    ofstream file;
    file.open(output_file_path);

    if (IsSchedulable)
    {
        cout << "[schedulable]=yes" << endl;
        file << "[schedulable]=yes" << endl;
    }
    else
    {
        cout << "[schedulable]=no" << endl;
        file << "[schedulable]=no" << endl;
    }

    cout << "[interval]=[0;" << Intended_time << "]" << endl;
    file << "[interval]=[0;" << Intended_time << "]" << endl;

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

    if (Total_utilisation > 0.0)
    {
        cout << "[utilisation_total]=" << Total_utilisation * 100 << endl;
        file << "[utilisation_total]=" << Total_utilisation * 100 << endl;
    }
    else
    {
        cout << "[utilisation_total]=?" << endl;
        file << "[utilisation_total]=?" << endl;
    }

    for (unsigned int i = 0; i < Processors.size(); i++)
    {
        if (Processors.at(i)->Utilisation > 0.0)
        {
            cout << "[utilisation_" << i << "]=" << Processors.at(i)->Utilisation * 100 << endl;
            file << "[utilisation_" << i << "]=" << Processors.at(i)->Utilisation * 100 << endl;
        }
        else
        {
            cout << "[utilisation_" << i << "]=?" << endl;
            file << "[utilisation_" << i << "]=?" << endl;
        }
    }

    cout << endl;
    file << endl;

    file.close();
}

void SimulationResult::recalculateUtilisations()
{
    long long sum = 0;

    if (Simulation_time > 0.0)
    {
        for (unsigned int i = 0; i < Processors.size(); i++)
        {
            Processors.at(i)->Utilisation = ((double)(Simulation_time - Processors.at(i)->Idle)) / Simulation_time;
            sum += Simulation_time - Processors.at(i)->Idle;
            this->Preemtions += Processors.at(i)->Preemtions;
            this->Idle += Processors.at(i)->Idle;
        }

        Total_utilisation = ((double)sum) / (Processors.size() * Simulation_time);
    }
    else
    {
        Total_utilisation = -1.0;
    }
}
