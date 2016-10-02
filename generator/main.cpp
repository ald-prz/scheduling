#include <QCoreApplication>

#include "all.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    auto_ptr<InputRecognizer> recognizer(new InputRecognizer());

    auto_ptr<Configuration> configuration(recognizer->Recognize(argc, argv));

    return a.exec();
}
