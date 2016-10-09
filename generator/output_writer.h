#ifndef OUTPUT_WRITER_H
#define OUTPUT_WRITER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "task.h"

using namespace std;

class OutputWriter
{
public:

    OutputWriter(string filename, vector<Task *> tasks);

    void Write();

private:

    string filename;

    vector<Task *> tasks;
};

#endif // OUTPUT_WRITER_H

