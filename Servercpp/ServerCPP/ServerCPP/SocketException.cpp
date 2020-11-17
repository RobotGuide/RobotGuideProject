#include "SocketException.h"

SocketException::SocketException(const char* str): error(str)
{
	error = str;
}

const char* SocketException::what() const throw()
{
	return error != nullptr ? error : "";
}

