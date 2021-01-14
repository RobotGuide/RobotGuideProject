#include "robotguide/Communication/ApplicationLayer/RobotInstructor.h"
#include "robotguide/Communication/ApplicationLayer/Robot.h"
#include <cmath>

using namespace robotguide::com::transportlayer;
using namespace robotguide::com::applicationlayer;

RobotInstructor::RobotInstructor() : nextRobotID(0)
{
}

RobotInstructor::~RobotInstructor()
{
	for (Robot* robot : robots)
	{
		delete robot;
		robot = nullptr;
	}
}

IRobot* RobotInstructor::GetRobot(const int id)
{
	for (Robot* robot : robots)
	{
		if (robot->GetRobotId() == id)
		{
			return robot;
		}
	}
	return nullptr;
}

IRobot& RobotInstructor::CreateNewRobot()
{
	Robot* robot = new Robot(++nextRobotID);
	robots.push_back(robot);
	return *robot;
}

IRobot* RobotInstructor::GetNearestRobot(const int x, const int y)
{
	IRobot* nearestRobot = nullptr;
	int distance = INT_MAX;
	for (Robot* robot : robots)
	{
		const std::tuple<int, int> coords = robot->GetCoordinates();
		const int distanceFromRobot = abs(std::get<0>(coords) - x) + abs(std::get<1>(coords) - y);
		if (distance > distanceFromRobot)
		{
			distance = distanceFromRobot;
			nearestRobot = robot;
		}
	}
	return nearestRobot;
}
