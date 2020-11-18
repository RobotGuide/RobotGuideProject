#ifndef ILISTENER_H
#define ILISTENER_H

/**
 * The class where you can check if there are sockets that want to connect
 */
class IListener
{
public:
	virtual ~IListener() {}

	// Listen listening for connections	 
	virtual  void  Listen(unsigned int maxConnections) = 0;

	//Check if there is a pending connection
	//Accept a pending connection
	virtual  int  Accept() = 0;

	//Stop listening for connections
	virtual  void Stop() = 0;
};

#endif

