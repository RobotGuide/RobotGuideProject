#ifndef ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_ROBOTWINDOWSLISTENER_H
#define ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_ROBOTWINDOWSLISTENER_H

#include "ISocket.h"
#include "Receiver.h"
#include "IRobotInstructor.h"
#include "WindowsListener.h"

namespace robotguide::com::transportlayer
{

	class WindowsRobotListener final : protected WindowsListener, public ISelectable
	{
	private:
		Receiver& receiver;
		IRobotInstructor& robotInstructor;
	public:
		/// <summary>
		/// Initialize a windows based robot listener
		/// </summary>
		/// <param name="receiver">The receiver that you want the connections to have been added to</param>
		/// <param name="robotInstructor">The robot instructor you want to pass to connections</param>
		/// <param name="ipAddress">The ip address for the listener</param>
		/// <param name="port">The port you want to listen to</param>
		/// <param name="type">The configuration for this listener</param>
		WindowsRobotListener(Receiver& receiver, IRobotInstructor& robotInstructor, const std::string& ipAddress, const std::string& port, const addrinfo& type);
		~WindowsRobotListener() override = default;


		/// <summary>
		/// Handle available data for this socket
		/// </summary>
		void HandleAvailableData() override;
	};
}


#endif
