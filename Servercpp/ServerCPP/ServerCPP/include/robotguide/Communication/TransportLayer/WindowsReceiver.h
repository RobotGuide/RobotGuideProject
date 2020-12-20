#ifndef ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_WINDOWSRECEIVER_H
#define ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_WINDOWSRECEIVER_H

#include "Receiver.h"
#include "ISelectable.h"
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

		/// <summary>
		/// Add a new socket to the receiver to check for data
		/// </summary>
		/// <param name="socket">The socket you want to add</param>
		void AddSelectable(ISelectable* socket) override;

		/// <summary>
		/// Remove all inactive connections
		/// </summary>
		void Clean() override;

	private:
		/// <summary>
		/// Count the number of sockets who have data available to them
		/// </summary>
		/// <returns>The amount of sockets with data</returns>
		int SetFDSet();
	};
}
#endif
