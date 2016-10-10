#include "configuration.h"



Configuration::Configuration(const double utilisation, const int task_number, const string output_filename)
{
    this->utilisation = utilisation;
    this->task_number = task_number;
    this->output_filename = output_filename;
}

double Configuration::getUtilisation() const
{
    return utilisation;
}

int Configuration::getTaskNumber() const
{
    return task_number;
}

string Configuration::getOutputFilename() const
{
    return output_filename;
}

ostream &operator<<(ostream &output, const Configuration &c)
{
    output.precision(5);

    output << "Input:" << endl << "Task number = " << c.getTaskNumber()
           << endl << "Utilisation = " << c.getUtilisation()
           << endl <<"Output filename = " << c.getOutputFilename() << endl << endl;

    return output;
}
