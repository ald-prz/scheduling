#include "analyzer.h"

Analyzer::Analyzer(TestPlan plan)
{
    this->processor_num = plan.processor_num;
    this->utilisation = plan.utilisation;
    this->task_num = plan.task_num;

    // allocate test result matrixes

    vector<double> row_double;
    vector<int> row_int;
    vector<bool> row_bool;
    for (unsigned int i = 0; i < utilisation.size(); i++)
    {
        row_double.push_back(0.0);
        row_int.push_back(0);
        row_bool.push_back(false);
    }

    for (unsigned int i = 0; i < task_num.size(); i++)
    {
        load_p.push_back(row_double);
        load_g.push_back(row_double);
        processor_p.push_back(row_int);
        processor_g.push_back(row_int);
        schedulable_p.push_back(row_bool);
        schedulable_g.push_back(row_bool);
    }
}

void Analyzer::Analyze()
{
    int min;

    for (unsigned int i = 0; i < task_num.size(); i++)
        for (unsigned int j = 0; j < utilisation.size(); j++)
        {
            Configuration c(utilisation.at(j), task_num.at(i), "", 100.0);
            Generator generator(&c);
            vector<Task *> task = generator.Generate();

            min = MinimumDeterminer::Determine(task, true);
            processor_g.at(i).at(j) = min;
            min = MinimumDeterminer::Determine(task, false);
            processor_p.at(i).at(j) = min;

            SimulatorGlobal global(task, processor_num, false);
            SimulationResult result = global.Simulate();
            load_g.at(i).at(j) = result.Total_utilisation;
            schedulable_g.at(i).at(j) = result.IsSchedulable;

            SimulatorPartitioned partitioned(task, processor_num, false);
            result = partitioned.Simulate();
            load_p.at(i).at(j) = result.Total_utilisation;
            schedulable_p.at(i).at(j) = result.IsSchedulable;
        }
}

void Analyzer::OutputToFile(char *output_file_path)
{
    ofstream file;
    file.open(output_file_path);

    file << "-------------------[utilisation]----------------------" << endl;

    for (unsigned int i = 0; i < utilisation.size(); i++)
        file << utilisation.at(i) << endl;

    file << "-------------------[load][global]----------------------" << endl;

    for (unsigned int i = 0; i < task_num.size(); i++)
    {
        file << "[task_num]=" << task_num.at(i) << endl;

        for (unsigned int j = 0; j < utilisation.size(); j++)
            file << load_g.at(i).at(j) << endl;
    }

    file << "-------------------[load][partitioned]----------------------" << endl;

    for (unsigned int i = 0; i < task_num.size(); i++)
    {
        file << "[task_num]=" << task_num.at(i) << endl;

        for (unsigned int j = 0; j < utilisation.size(); j++)
            file << load_p.at(i).at(j) << endl;
    }

    file << "-------------------[minimal_processors][global]----------------------" << endl;

    for (unsigned int i = 0; i < task_num.size(); i++)
    {
        file << "[task_num]=" << task_num.at(i) << endl;

        for (unsigned int j = 0; j < utilisation.size(); j++)
            file << processor_g.at(i).at(j) << endl;
    }

    file << "-------------------[minimal_processors][partitioned]----------------------" << endl;

    for (unsigned int i = 0; i < task_num.size(); i++)
    {
        file << "[task_num]=" << task_num.at(i) << endl;

        for (unsigned int j = 0; j < utilisation.size(); j++)
            file << processor_p.at(i).at(j) << endl;
    }

    file << "-------------------[schedulable][global]----------------------" << endl;

    for (unsigned int i = 0; i < task_num.size(); i++)
    {
        file << "[task_num]=" << task_num.at(i) << endl;

        for (unsigned int j = 0; j < utilisation.size(); j++)
            if (schedulable_g.at(i).at(j))
                file << "yes" << endl;
            else
                file << "no" << endl;
    }

    file << "-------------------[schedulable][partitioned]----------------------" << endl;

    for (unsigned int i = 0; i < task_num.size(); i++)
    {
        file << "[task_num]=" << task_num.at(i) << endl;

        for (unsigned int j = 0; j < utilisation.size(); j++)
            if (schedulable_p.at(i).at(j))
                file << "yes" << endl;
            else
                file << "no" << endl;
    }

    file.close();
}
