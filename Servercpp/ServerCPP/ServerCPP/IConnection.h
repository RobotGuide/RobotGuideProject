#ifndef  CONNECTION_H
#define  CONNECTION_H

class IConnection
{
public:
	
	/// <summary>
	/// Destruct a connection
	/// </summary>
	virtual ~IConnection() = default;
	
	/// <summary>
	/// Returns the socket handler for this connection
	/// </summary>
	/// <returns>The socket handle for this connection</returns>
	virtual int GetSocketHandle() const = 0;
	
	/// <summary>
	/// Send data to the connected application
	/// </summary>
	/// <param name="message">The message you want to send</param>
	/// <param name="length">The length of the message</param>
	virtual void Send(const char* message, const int length) = 0;

	/// <summary>
	/// Returns if the connection is still connected
	/// </summary>
	/// <returns>If the connection is active</returns>
	virtual bool IsConnected() const = 0;
};

#endif
