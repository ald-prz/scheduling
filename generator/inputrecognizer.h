#ifndef INPUTRECOGNIZER_H
#define INPUTRECOGNIZER_H

#include "all.h"

using namespace std;

class InputRecognizer: public InputRecognizerAbstract
{
public:
    virtual Configuration *Recognize(int argc, char *argv[]) override;
};

#endif // INPUTRECOGNIZER_H


