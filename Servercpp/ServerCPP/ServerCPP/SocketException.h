#ifndef SOCKET_EXCEPTION_H
#define SOCKET_EXCEPTION_H

#include <exception>

class SocketException final : public std::exception
{
private:
	const char* error;

public:
	explicit SocketException(const char* str);
	const char* what() const throw () override;

};

#endif
