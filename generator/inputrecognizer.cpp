#include "all.h"



Configuration* InputRecognizer::Recognize(int argc, char *argv[])
{
    Configuration *result;

    if (argc < 7)
        throw exception();
    else if (strcmp(argv[1], "-u") != 0)
        throw new exception();
    else if (strcmp(argv[3], "-n") != 0)
        throw new exception();
    else if (strcmp(argv[5], "-o") != 0)
        throw new exception();
    else
    {
        result = new Configuration(atof(argv[2]), atoi(argv[4]), argv[6]);
    }

    return result;
}
