#include "all.h"


int main(int argc, char *argv[])
{
    InputRecognizer recognizer;
    Configuration *configuration = nullptr;

    try
    {
        configuration = recognizer.Recognize(argc, argv);
    }
    catch (ExceptionInput eInput)
    {
        cout << eInput.getMessage();
        return 0;
    }

    cout << *configuration;

    Generator generator(configuration);
    vector<Task *> tasks = generator.Generate();

    OutputWriter outputWriter(configuration->getOutputFilename(), tasks);
    outputWriter.Write();

    cout << "Written to " << configuration->getOutputFilename() << endl;

    tasks.clear();

    cout << "Finished" << endl;

    delete configuration;

    return 0;
}
