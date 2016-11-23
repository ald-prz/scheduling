#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>
#include <iostream>

using namespace std;

class Configuration
{
public:

    Configuration(const double utilisation, const int task_number, const string output_filename, const double average_wcet);

    double getUtilisation() const;

    int getTaskNumber() const;

    string getOutputFilename() const;

    double getAverageWcet() const;

    friend ostream &operator<<(ostream &output, const Configuration &C);

private:

    double utilisation;

    int task_number;

    string output_filename;

    double average_wcet;
};

#endif // CONFIGURATION_H


