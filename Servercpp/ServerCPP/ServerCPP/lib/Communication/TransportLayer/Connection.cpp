#include "robotguide/Communication/TransportLayer/Connection.h"
#include "robotguide/Communication/TransportLayer/Buffer.h"

using namespace robotguide::com::transportlayer;

Connection::Connection(const unsigned int socketHandle, const unsigned int receiveBufferSize)
	: receiveBuffer(receiveBufferSize)
	, socketHandle(socketHandle)
{
}

unsigned Connection::GetSocketHandle() const
{
	return socketHandle;
}

Buffer& Connection::GetReceiveBuffer()
{
	return receiveBuffer;
}
