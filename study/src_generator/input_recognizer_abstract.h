#ifndef INPUTRECOGNIZERABSTRACT_H
#define INPUTRECOGNIZERABSTRACT_H

#include "configuration.h"

class InputRecognizerAbstract
{
public:

    virtual Configuration *Recognize(int argc, char *argv[]) = 0;
};

#endif // INPUTRECOGNIZERABSTRACT_H
