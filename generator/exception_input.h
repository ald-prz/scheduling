#ifndef EXCEPTION_INPUT_H
#define EXCEPTION_INPUT_H

#include <string>

using namespace std;

class ExceptionInput : public exception
{
public:

    ExceptionInput(const string message);

    string getMessage() const;

private:

    string message;
};

#endif // EXCEPTION_INPUT_H



