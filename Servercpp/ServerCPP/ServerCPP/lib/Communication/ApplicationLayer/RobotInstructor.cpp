#include "robotguide/Communication/ApplicationLayer/RobotInstructor.h"

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

void RobotInstructor::AddRobot(Robot& robot)
{
	if (GetRobot(robot.GetRobotId()) == nullptr)
	{
		robots.push_back(new Robot(robot));
	}
}

Robot* RobotInstructor::GetRobot(const int id)
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

int RobotInstructor::GetUniqueID()
{
	return nextRobotID++;
}
