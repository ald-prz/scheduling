#include "output_writer.h"



OutputWriter::OutputWriter(string filename, vector<Task *> tasks)
{
    this->filename = filename;

    this->tasks = tasks;
}


void OutputWriter::Write()
{
    ofstream outfile;

    outfile.open(this->filename);

    for (int i = 0; i < this->tasks.size(); i++)
    {
        outfile << this->tasks.at(i)->getOffset() << " " << this->tasks.at(i)->getPeriod() << " "
            << this->tasks.at(i)->getDeadline() << " " << this->tasks.at(i)->getWcet() << endl;
    }

    outfile.close();
}
