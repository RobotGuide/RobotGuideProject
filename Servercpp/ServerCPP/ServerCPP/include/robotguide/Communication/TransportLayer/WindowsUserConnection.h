#ifndef ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_WINDOWSUSERCONNECTION_H
#define ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_WINDOWSUSERCONNECTION_H

#include "WindowsConnection.h"
#include "IRouteRequester.h"

namespace robotguide::com::transportlayer
{
	class WindowsUserConnection final : public WindowsConnection
	{
	private:
		IRouteRequester& routeRequester;
	public:
		/// <summary>
		/// Initialize the connection between a user and the server 
		/// </summary>
		/// <param name="routeRequester">The route requester that the user connection can interface with</param>
		/// <param name="socketHandler">The socket handler for this connection</param>
		/// <param name="receiveBufferSize">The size of the receive buffer in characters</param>
		WindowsUserConnection(IRouteRequester& routeRequester, const SOCKET& socketHandler, unsigned int receiveBufferSize);
		~WindowsUserConnection() override = default;

		/// <summary>
		/// Handle user requests
		/// </summary>
		void HandleAvailableData() override;

		/// <summary>
		/// Copy a robot connection
		/// </summary>
		/// <returns>The copy in the heap</returns>
		ISelectable* Copy() const override;
	};
}

#endif
