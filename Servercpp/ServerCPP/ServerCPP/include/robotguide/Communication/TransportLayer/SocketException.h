#ifndef SOCKETEXCEPTION_H
#define SOCKETEXCEPTION_H

#include <exception>
#include <string>

namespace robotguide::com::transportlayer
{

	/// <summary>
	/// The socket exception  occurs when a socket error happens in the socket functions.
	/// </summary>
	class SocketException : public std::exception
	{
	private:
		std::string error;

	public:
		/// <summary>
		/// Throw this exception when socket detects errors
		/// </summary>
		SocketException(const std::string& errorMessage);
		~SocketException() = default;

		/// <summary>
		/// Get the error message
		/// </summary>
		/// <returns>Returns the socket exceptions error message</returns>
		const char* what() const noexcept override;

	};
}

#endif
