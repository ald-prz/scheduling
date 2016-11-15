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

    double actual_util = 0;

    for (int i = 0; i < this->tasks.size(); i++)
    {
        outfile << this->tasks.at(i)->getOffset() << " " << this->tasks.at(i)->getPeriod() << " "
            << this->tasks.at(i)->getDeadline() << " " << this->tasks.at(i)->getWcet() << endl;

        actual_util += ((double)this->tasks.at(i)->getWcet())/((double)this->tasks.at(i)->getPeriod());
    }

    cout <<"Actual utilisation = " << actual_util * 100 << endl;

    outfile.close();
}
