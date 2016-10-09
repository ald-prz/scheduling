#include "all.h"



int main(int argc, char *argv[])
{
    InputRecognizer *recognizer = new InputRecognizer();
    Configuration *configuration;

    try
    {
        configuration = recognizer->Recognize(argc, argv);
    }
    catch (ExceptionInput eInput)
    {
        cout << eInput.getMessage();
        return 0;
    }

    cout << *configuration;

    Generator *generator = new Generator(configuration);
    vector<Task *> tasks = generator->Generate();

    OutputWriter *outputWriter = new OutputWriter(configuration->getOutput_filename(), tasks);
    outputWriter->Write();

    cout << "Written to " << configuration->getOutput_filename() << endl;

    tasks.clear();

    cout << "Finished" << endl;

    delete configuration;
    delete generator;
    delete outputWriter;
    delete recognizer;

    return 0;
}
