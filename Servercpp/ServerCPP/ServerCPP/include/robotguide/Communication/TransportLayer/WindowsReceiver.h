#ifndef ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_WINDOWSRECEIVER_H
#define ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_WINDOWSRECEIVER_H

#include "IReceiver.h"
#include <vector>
#include <WinSock2.h>

namespace robotguide::com::transportlayer
{

	class WindowsReceiver final : public IReceiver
	{
	private:
		FD_SET ReadSet = {};

	public:
		WindowsReceiver() = default;
		~WindowsReceiver() override = default;

		/// <summary>
		/// Receive data for all available sockets
		/// </summary>
		/// <param name="connections">The connections you want to check for available data</param>
		void ReceiveData(const std::vector<Connection*>& connections) override;
	private:
		int GetAvailableSocketsCount(const std::vector<Connection*>& connections);
		static void ReceiveDataFromConnection(Connection& connection);
	};
}
#endif
