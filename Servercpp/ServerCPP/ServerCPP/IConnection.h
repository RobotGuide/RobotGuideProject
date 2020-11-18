#ifndef  CONNECTION_H
#define  CONNECTION_H
#include <string>

class IConnection
{
public:
	virtual ~IConnection() = default;
	virtual int GetSocketHandle() const = 0;
	virtual void Send(const char* message, const int length) = 0;
	virtual bool IsConnected() const = 0;
};

#endif
