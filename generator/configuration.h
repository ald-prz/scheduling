#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "all.h"

using namespace std;

class Configuration
{
public:

    Configuration(double utilisation, int task_number, string output_filename);

    double getUtilisation() const;

    int getTask_number() const;

    string getOutput_filename() const;

private:

    double utilisation;

    int task_number;

    string output_filename;
};

#endif // CONFIGURATION_H


