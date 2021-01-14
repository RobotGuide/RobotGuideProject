#ifndef ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_WINDOWSRECEIVER_H
#define ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_WINDOWSRECEIVER_H

#include "Receiver.h"
#include <vector>
#include <WinSock2.h>

namespace robotguide::com::transportlayer
{

	class WindowsReceiver final : public Receiver
	{
	private:
		FD_SET ReadSet = {};
	public:
		WindowsReceiver() = default;
		~WindowsReceiver() override = default;

		/// <summary>
		/// Check all sockets for data
		/// </summary>
		void CheckForData() override;

	private:
		/// <summary>
		/// Count the number of sockets who have data available to them
		/// </summary>
		/// <returns>The amount of sockets with data</returns>
		int SetFDSet();
	};
}
#endif
