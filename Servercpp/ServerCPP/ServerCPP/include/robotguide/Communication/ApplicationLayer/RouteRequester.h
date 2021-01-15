#ifndef ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_ROUTEREQUESTER_H
#define ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_ROUTEREQUESTER_H

#include "robotguide/Communication/TransportLayer/IRouteRequester.h"
#include "robotguide/Communication/TransportLayer/IRobotInstructor.h"
#include "robotguide/Pathfinding/Path/PathFinder.h"
#include "robotguide/Pathfinding/Path/PathToProtocolInstruction.h"



namespace robotguide::com::applicationlayer
{
	class RouteRequester final : public transportlayer::IRouteRequester
	{
	private:
		transportlayer::IRobotInstructor& instructor;
		path::PathFinder& pathfinder;
		path::PathToProtocolInstruction converter;
	public:
		RouteRequester(transportlayer::IRobotInstructor& instructor, path::PathFinder& pathfinder);
		~RouteRequester() override = default;

		/// <summary>
		/// Handle a message from the transport layer
		/// </summary>
		/// <param name="message">The message you need to handle</param>
		std::string HandleMessage(const std::string& message) override;
	};
}
#endif

