#include "robotguide/Communication/ApplicationLayer/RouteRequester.h"
#include <iostream>

using namespace robotguide::com::applicationlayer;
using namespace robotguide::com::transportlayer;

RouteRequester::RouteRequester(IRobotInstructor& instructor, path::PathFinder& pathfinder)
	: instructor(instructor)
	, pathfinder(pathfinder)
{
}

std::string RouteRequester::HandleMessage(const std::string& message)
{
	//TODO parse from instruction and return response message
	const int x = 0;
	const int y = 0;
	const int endX = 3;
	const int endY = 3;

	std::cout << "User: " << message;
	IRobot* robot = instructor.GetNearestRobot(0, 0);
	if (robot == nullptr)
	{
		return "No robots available";
	}

	path::Path path = pathfinder.FindPath(std::get<0>(robot->GetCoordinates()), std::get <1>(robot->GetCoordinates()), x, y);

	InstructionStream stream;
	converter.ConvertPathToInstructionStream(path, stream);
	robot->AddInstructions(stream, std::make_tuple(x, y));

	path = pathfinder.FindPath(x, y, endX, endY);
	converter.ConvertPathToInstructionStream(path, stream);
	robot->AddInstructions(stream, std::make_tuple(x, y));

	return "Navigation instruction handled";
}

