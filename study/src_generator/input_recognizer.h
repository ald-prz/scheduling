#ifndef INPUTRECOGNIZER_H
#define INPUTRECOGNIZER_H

#include <string.h>

#include "exception_input.h"
#include "input_recognizer_abstract.h"

class InputRecognizer: public InputRecognizerAbstract
{
public:

    Configuration *Recognize(int argc, char *argv[]) override;
};

#endif // INPUTRECOGNIZER_H


