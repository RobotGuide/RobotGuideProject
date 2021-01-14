#ifndef ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_USERWINDOWSLISTENER_H
#define ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_USERWINDOWSLISTENER_H

#include "Receiver.h"
#include "IRouteRequester.h"
#include "WindowsListener.h"

namespace robotguide::com::transportlayer
{

	class WindowsUserListener final : public WindowsListener
	{
	private:
		Receiver& receiver;
		IRouteRequester& routeRequester;
	public:
		/// <summary>
		/// Initialize a windows based user listener
		/// </summary>
		/// <param name="receiver">The receiver that you want the connections to have been added to</param>
		/// <param name="routeRequester">The route requester you want to pass to connections</param>
		/// <param name="ipAddress">The ip address for the listener</param>
		/// <param name="port">The port you want to listen to</param>
		/// <param name="type">The configuration for this listener</param>
		WindowsUserListener(Receiver& receiver, IRouteRequester& routeRequester, const std::string& ipAddress, const std::string& port, const addrinfo& type);
		~WindowsUserListener() override = default;

		/// <summary>
		/// Handle available data for this socket
		/// </summary>
		void HandleAvailableData() override;


		/// <summary>
		/// Create a copy on the heap for this Robot Listener
		/// </summary>
		/// <returns>A copy of the robot listener</returns>
		ISelectable* Copy() const override;
	};
}


#endif
