#ifndef SOCKET_EXCEPTION_H
#define SOCKET_EXCEPTION_H

#include <exception>

/// <summary>
/// The socket exception this occurs when socket happens
/// </summary>
class SocketException final : public std::exception
{
private:
	const char* error;

public:
	/// <summary>
	/// Throw this exception when socket detects errors
	/// </summary>
	/// <param name="str">The error message</param>
	SocketException(const char* str);

	/// <summary>
	/// Get the error message
	/// </summary>
	/// <returns>Returns the socket exceptions error message</returns>
	const char* what() const throw () override;

};

#endif
