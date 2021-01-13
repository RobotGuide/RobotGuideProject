#include "robotguide/Communication/TransportLayer/WindowsConnection.h"
#include "robotguide/Communication/TransportLayer/WindowsListener.h"
#include "robotguide/Communication/TransportLayer/SocketException.h"
#include "robotguide/Communication/TransportLayer/WindowsReceiver.h"
#include "robotguide/Communication/TransportLayer/WindowsRobotListener.h"
#include "robotguide/Communication/TransportLayer/SocketInitializationException.h"
#include "robotguide/Communication/ApplicationLayer/RobotInstructor.h"
#include <string>
#include <iostream>

//Required for windows socket
#pragma comment(lib, "Ws2_32.lib")
#undef  UNICODE

using namespace robotguide::com::transportlayer;
using namespace robotguide::com::applicationlayer;

int main()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	addrinfo hints{};
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	const std::string ipAddress = "0.0.0.0";
	const std::string port = "3030";

	WindowsReceiver receiver;
	RobotInstructor instructor;
	WindowsRobotListener listener(receiver, instructor, ipAddress, port, hints);
	try
	{
		listener.Listen(10);
		std::cout << "Started at address: " << ipAddress << " Port: " << port << std::endl;
		receiver.AddSelectable(listener);
	}
	catch (SocketInitializationException& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	while (true)
	{
		receiver.CheckForData();
		receiver.Clean();
	}
}