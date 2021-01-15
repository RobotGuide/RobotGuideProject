#ifndef ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_ROUTEREQUESTER_H
#define ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_ROUTEREQUESTER_H

#include "robotguide/Communication/TransportLayer/IRouteRequester.h"
#include "robotguide/Communication/TransportLayer/IRobotInstructor.h"

namespace robotguide::com::applicationlayer
{
	class RouteRequester final : public transportlayer::IRouteRequester
	{
	private:
		transportlayer::IRobotInstructor& instructor;
	public:
		RouteRequester(transportlayer::IRobotInstructor& instructor);
		~RouteRequester() override = default;

		/// <summary>
		/// Handle a message from the transport layer
		/// </summary>
		/// <param name="message">The message you need to handle</param>
		void HandleMessage(const std::string& message) override;

	};
}
#endif
