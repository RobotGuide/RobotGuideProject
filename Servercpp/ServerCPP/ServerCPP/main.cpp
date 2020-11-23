#include "robotguide/Communication/TransportLayer/WindowsConnection.h"
#include "robotguide/Communication/TransportLayer/WindowsListener.h"
#include "robotguide/Communication/TransportLayer/SocketException.h"
#include <string>
#include <vector>
#include <iostream>


//Required for windows socket
#pragma comment(lib, "Ws2_32.lib")
#undef  UNICODE

using namespace robotguide::com::transportlayer;

void LoopThroughAllConnections(std::vector<IConnection*>& connections, const std::string& message);

int main()
{
	std::cout << "Boot Up" << std::endl;

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	addrinfo hints{};
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	WindowsListener listener("127.0.0.1", "3030", hints);
	listener.Listen(10);
	std::cout << "Started" << std::endl;

	std::string str;
	std::vector<IConnection*> connections;

	while (true)
	{
		try
		{
			const int handle = listener.Accept();
			connections.push_back(new WindowsConnection(handle));
			std::cout << handle << std::endl;
		}
		catch (SocketException& e)
		{
			std::cout << e.what() << std::endl;
		}
		LoopThroughAllConnections(connections, str);

		std::getline(std::cin, str);
		std::cout << str << std::endl;
	}
}

void LoopThroughAllConnections(std::vector<IConnection*>& connections, const std::string& message)
{
	try
	{
		auto iterator = connections.begin();
		while (iterator != connections.end())
		{
			if ((*iterator)->IsConnected())
			{
				(*iterator)->Send(message);
				std::cout << "Sent: " << message << std::endl;
				++iterator;
			}
			else
			{
				auto* const iteratorValue = *iterator;
				iterator = connections.erase(iterator);
				delete iteratorValue;
			}
		}
		std::cout << "There are: " << connections.size() << " connections" << std::endl;

	}
	catch (SocketException& e)
	{
		std::cout << e.what() << std::endl;
	}
}
