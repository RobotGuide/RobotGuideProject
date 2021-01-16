#include "robotguide/Communication/ApplicationLayer/RouteRequester.h"
#include "robotguide/Communication/ApplicationLayer/RouteRequestParser.h"
#include "robotguide/Communication/Exception/ApplicationLayer/Parser/ParserException.h"
#include "robotguide/Communication/Exception/Pathfinding/InvalidRouteException.h"
#include <iostream>


using namespace robotguide::com::applicationlayer;
using namespace robotguide::com::transportlayer;

RouteRequester::RouteRequester(IRobotInstructor& instructor, path::PathFinder& pathfinder)
	: instructor(instructor)
	, pathfinder(pathfinder)
	, converter(0, 1000)
{
}

std::string RouteRequester::HandleMessage(const std::string& message)
{
	RouteRequest request;
	try
	{
		request = RouteRequestParser::ParseRequestToRoute(message);
	}
	catch (exception::applicationlayer::ParserException&)
	{
		return "Invalid message received";
	}

	std::cout << "User: " << message;
	IRobot* robot = instructor.GetNearestRobot(0, 0);
	if (robot == nullptr)
	{
		return "No robots available";
	}

	const int robotX = std::get<0>(robot->GetCoordinates());
	const int robotY = std::get<1>(robot->GetCoordinates());

	converter.SetCurrentAngle(robot->GetRotationAngle());
	InstructionStream stream;
	try
	{
		const path::Path path = pathfinder.FindPath(robotX, robotY, request.xCurrent, request.yCurrent);
		converter.ConvertPathToInstructionStream(path, stream);

		const path::Path path2 = pathfinder.FindPath(request.xCurrent, request.yCurrent, request.xDestination, request.yDestination);
		converter.ConvertPathToInstructionStream(path2, stream);
	}
	catch (exception::InvalidRouteException&)
	{
		return "Invalid route request. The route could not be processed";
	}
	robot->AddInstructions(stream, std::make_tuple(request.xDestination, request.xDestination), converter.GetCurrentAngle());
	return "Navigation instruction handled";
}