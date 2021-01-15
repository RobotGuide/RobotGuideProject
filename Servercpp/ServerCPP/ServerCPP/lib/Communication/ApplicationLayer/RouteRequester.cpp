#include "robotguide/Communication/ApplicationLayer/RouteRequester.h"
#include <iostream>

using namespace robotguide::com::applicationlayer;
using namespace robotguide::com::transportlayer;

RouteRequester::RouteRequester(transportlayer::IRobotInstructor& instructor, path::PathFinder& pathfinder)
	: instructor(instructor)
	, pathfinder(pathfinder)
{
}

void RouteRequester::HandleMessage(const std::string& message)
{
	const int x = 1;
	const int y = 0;
	const int endX = 10;
	const int endY = 10;

	std::cout << "User: " << message;
	IRobot* robot = instructor.GetNearestRobot(0, 0);
	if (robot == nullptr)
	{
		std::cout << "No robots available" << std::endl;
		return;
	}

	std::get<0>(robot->GetCoordinates());
	path::Path path = pathfinder.FindPath(std::get<0>(robot->GetCoordinates()), std::get <1>(robot->GetCoordinates()), x, y);

	InstructionStream stream;
	converter.ConvertPathToInstructionStream(path, stream);
	robot->AddInstructions(stream, std::make_tuple(x, y));

	path = pathfinder.FindPath(x, y, endX, endY);
	converter.ConvertPathToInstructionStream(path, stream);
	robot->AddInstructions(stream, std::make_tuple(x, y));
}

