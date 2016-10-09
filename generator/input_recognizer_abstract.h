#ifndef INPUTRECOGNIZERABSTRACT_H
#define INPUTRECOGNIZERABSTRACT_H

#include "configuration.h"

using namespace std;

class InputRecognizerAbstract
{
public:

    virtual Configuration *Recognize(int argc, char *argv[]) = 0;
};

#endif // INPUTRECOGNIZERABSTRACT_H
