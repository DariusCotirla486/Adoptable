#include "Exceptions.h"


Exception::Exception(const string& message)
{
	this->message = message;
}

const char* Exception::what()
{
	return this->message.c_str();
}
