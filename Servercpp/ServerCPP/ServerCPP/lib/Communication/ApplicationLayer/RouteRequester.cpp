#include "robotguide/Communication/ApplicationLayer/RouteRequester.h"
#include "robotguide/Communication/ApplicationLayer/RouteRequestParser.h"
#include "robotguide/Communication/Exception/ApplicationLayer/Parser/ParserException.h"
#include <iostream>

using namespace robotguide::com::applicationlayer;
using namespace robotguide::com::transportlayer;
using namespace robotguide::com::exception::applicationlayer;

RouteRequester::RouteRequester(IRobotInstructor& instructor, path::PathFinder& pathfinder)
	: instructor(instructor)
	, pathfinder(pathfinder)
{
}

std::string RouteRequester::HandleMessage(const std::string& message)
{
	RouteRequest request;
	try
	{
		request = RouteRequestParser::ParseRequestToRoute(message);
	}
	catch (ParserException&)
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

	AddRouteToRobot(*robot, robotX, robotY, request.xCurrent, request.yCurrent);
	AddRouteToRobot(*robot, request.xCurrent, request.yCurrent, request.xDestination, request.xDestination);
	return "Navigation instruction handled";
}

void RouteRequester::AddRouteToRobot(IRobot& robot, int x, int y, int endX, int endY)
{
	const path::Path path = pathfinder.FindPath(x, y, endX, endX);

	InstructionStream stream;
	converter.ConvertPathToInstructionStream(path, stream);
	robot.AddInstructions(stream, std::make_tuple(endX, endX));
}

