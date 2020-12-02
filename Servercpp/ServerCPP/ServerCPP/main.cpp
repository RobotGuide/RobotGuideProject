#include "robotguide/Communication/TransportLayer/WindowsConnection.h"
#include "robotguide/Communication/TransportLayer/WindowsListener.h"
#include "robotguide/Communication/TransportLayer/SocketException.h"
#include "robotguide/Communication/TransportLayer/WindowsReceiver.h"
#include "robotguide/Communication/TransportLayer/SocketIntializationException.h"
#include <string>
#include <vector>
#include <iostream>

//Required for windows socket
#pragma comment(lib, "Ws2_32.lib")
#undef  UNICODE

using namespace robotguide::com::transportlayer;

void LoopThroughAllConnections(std::vector<std::shared_ptr<IConnection>>& connections, const std::string& message);

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
	try
	{
		listener.Listen(10);
		std::cout << "Started" << std::endl;
	}
	catch (SocketInitializationException& e)
	{
		std::cout << e.what() << std::endl;
		return 0;
	}
	std::string str;
	std::vector<std::shared_ptr<IConnection>> connections;
	std::vector<int> handlers;
	WindowsReceiver receiver;

	while (true)
	{
		try
		{
			const int handle = listener.Accept();
			connections.push_back(std::make_shared<WindowsConnection>(handle, 80));
			handlers.push_back(handle);
			std::cout << handle << std::endl;
		}
		catch (SocketException& e)
		{
			std::cout << e.what() << std::endl;
		}

		try
		{
			receiver.ReceiveData(connections);
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

void LoopThroughAllConnections(std::vector<std::shared_ptr<IConnection>>& connections, const std::string& message)
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
				iterator = connections.erase(iterator);
			}
		}
		std::cout << "There are: " << connections.size() << " connections" << std::endl;

	}
	catch (SocketException& e)
	{
		std::cout << e.what() << std::endl;
	}
}
