#include "all.h"

using namespace std;

int main(int argc, char *argv[])
{
    auto_ptr<InputRecognizer> recognizer(new InputRecognizer());

    auto_ptr<Configuration> configuration(recognizer->Recognize(argc, argv));

    return 0;
}
