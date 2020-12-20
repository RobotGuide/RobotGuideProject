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

void LoopThroughAllConnections(std::vector<IConnection*>& connections, const std::string& message);


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

	WindowsListener listener(ipAddress, port, hints);
	try
	{
		listener.Listen(10);
		std::cout << "Started at address: " << ipAddress << " Port: " << port << std::endl;
	}
	catch (SocketInitializationException& e)
	{
		std::cout << e.what() << std::endl;
		return 0;
	}
	std::string str;
	std::vector<IConnection*> connections;
	std::vector<int> handlers;
	WindowsReceiver receiver;

	while (true)
	{
		std::getline(std::cin, str);
		std::cout << str << std::endl;

		try
		{
			const int handle = listener.Accept();
			connections.push_back(new WindowsConnection(handle, 80));
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
				(*iterator)->Send(message + '\n');
				std::cout << "Sent: " << message << std::endl;
				++iterator;
			}
			else
			{
				IConnection* temp = *iterator;
				iterator = connections.erase(iterator);
				delete temp;
				temp = nullptr;
			}
		}
		std::cout << "There are: " << connections.size() << " connections" << std::endl;

	}
	catch (SocketException& e)
	{
		std::cout << e.what() << std::endl;
	}
}
