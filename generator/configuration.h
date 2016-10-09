#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>
#include <iostream>

using namespace std;

class Configuration
{
public:

    Configuration(const double utilisation, const int task_number, const string output_filename);

    double getUtilisation() const;

    int getTask_number() const;

    string getOutput_filename() const;

    friend ostream &operator<<(ostream &output, const Configuration &C);

private:

    double utilisation;

    int task_number;

    string output_filename;
};

#endif // CONFIGURATION_H


