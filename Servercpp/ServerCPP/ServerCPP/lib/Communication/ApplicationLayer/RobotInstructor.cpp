#include "robotguide/Communication/ApplicationLayer/RobotInstructor.h"
#include "robotguide/Communication/ApplicationLayer/Robot.h"

using namespace robotguide::com::transportlayer;
using namespace robotguide::com::applicationlayer;

RobotInstructor::RobotInstructor() : nextRobotID(0)
{
}

RobotInstructor::~RobotInstructor()
{
	for (IRobot* robot : robots)
	{
		delete robot;
		robot = nullptr;
	}
}

void RobotInstructor::AddRobot(IRobot& robot)
{
	if (GetRobot(robot.GetRobotId()) != nullptr)
	{
		robots.push_back(robot.Copy());
	}
}

IRobot* RobotInstructor::GetRobot(const int id)
{
	for (IRobot* robot : robots)
	{
		if (robot->GetRobotId() == id)
		{
			return robot;
		}
	}
	return nullptr;
}

int RobotInstructor::GetUniqueID()
{
	return nextRobotID++;
}
