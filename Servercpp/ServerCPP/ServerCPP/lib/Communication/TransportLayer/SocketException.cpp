#include "../../../include/robotguide/Communication/TransportLayer/SocketException.h"

using namespace robotguide::com::transportlayer;

SocketException::SocketException(const std::string& errorMessage) : error(errorMessage)
{
}


const char* SocketException::what() const noexcept
{
	return error.c_str();
}

