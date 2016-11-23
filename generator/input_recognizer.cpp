#include "input_recognizer.h"

Configuration* InputRecognizer::Recognize(int argc, char *argv[])
{
    if (argc < 7)
        throw ExceptionInput("-u flag is missing\n");
    else if (strcmp(argv[1], "-u") != 0)
        throw ExceptionInput("-u flag is missing\n");
    else if (strcmp(argv[3], "-n") != 0)
        throw ExceptionInput("-n flag is missing\n");
    else if (strcmp(argv[5], "-o") != 0)
        throw ExceptionInput("-o flag is missing\n");
    else
    {
        if (argc >= 9)
            return new Configuration(atof(argv[2]), atoi(argv[4]), argv[6], atof(argv[8]));
        else
            return new Configuration(atof(argv[2]), atoi(argv[4]), argv[6], -1.0);
    }
}
