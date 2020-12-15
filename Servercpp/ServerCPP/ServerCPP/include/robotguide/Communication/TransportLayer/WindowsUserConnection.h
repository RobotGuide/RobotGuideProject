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
		WindowsUserConnection(IRouteRequester& routeRequester, const SOCKET& socketHandler, unsigned int receiveBufferSize);
		virtual void HandleAvailableData() override;
	};
}

#endif
