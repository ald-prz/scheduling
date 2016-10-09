#ifndef INPUTRECOGNIZER_H
#define INPUTRECOGNIZER_H

#include <string>
#include <string.h>

#include "exception_input.h"
#include "input_recognizer_abstract.h"


using namespace std;

class InputRecognizer: public InputRecognizerAbstract
{
public:

    virtual Configuration *Recognize(int argc, char *argv[]) override;
};

#endif // INPUTRECOGNIZER_H


