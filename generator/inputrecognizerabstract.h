#ifndef INPUTRECOGNIZERABSTRACT_H
#define INPUTRECOGNIZERABSTRACT_H

#include "all.h"

using namespace std;

class Configuration;

class InputRecognizerAbstract
{
public:
    virtual Configuration *Recognize(int argc, char *argv[]) = 0;
};

#endif // INPUTRECOGNIZERABSTRACT_H
