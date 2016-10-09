#include "exception_input.h"



ExceptionInput::ExceptionInput(const string message)
{
    this->message = message;
}

string ExceptionInput::getMessage() const
{
    return message;
}
