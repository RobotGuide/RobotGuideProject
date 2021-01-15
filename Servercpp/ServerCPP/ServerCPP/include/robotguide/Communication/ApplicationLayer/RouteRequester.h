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

	private:
		/// <summary>
		/// Add a route to a robot
		/// </summary>
		/// <param name="robot">The robot you want the route to have</param>
		/// <param name="x">The start x coordinate</param>
		/// <param name="y">The start y coordinate</param>
		/// <param name="endX">The end x coordinate</param>
		/// <param name="endY">The end y coordinate</param>
		void AddRouteToRobot(transportlayer::IRobot& robot, int x, int y, int endX, int endY);
	};
}
#endif

