#include "robotguide/Communication/TransportLayer/Buffer.h"
#include <cstring>
#include <stdexcept>

using namespace robotguide::com::transportlayer;

Buffer::Buffer(const unsigned int length) : maxLength(length)
{
	buffer = new char[length];
	this->length = -1;
}

Buffer::~Buffer()
{
	delete buffer;
}

char* Buffer::GetBuffer() const
{
	return buffer;
}

unsigned int Buffer::GetMaxLength() const
{
	return maxLength;
}

int Buffer::GetLength() const
{
	return length;
}

void Buffer::SetLength(const unsigned int bytes)
{
	if (bytes > maxLength)
	{
		throw std::invalid_argument("Length can not be bigger than the maximum size of the buffer");
	}
	length = bytes;
}

void Buffer::Clear()
{
	memset(buffer, 0, maxLength);
	length = -1;
}
