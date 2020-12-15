#include "robotguide/Communication/TransportLayer/Connection.h"
#include "robotguide/Communication/TransportLayer/Buffer.h"

using namespace robotguide::com::transportlayer;

Connection::Connection(unsigned int receiveBufferSize) : receiveBuffer(receiveBufferSize)
{
}

Buffer& Connection::GetReceiveBuffer()
{
	return receiveBuffer;
}
