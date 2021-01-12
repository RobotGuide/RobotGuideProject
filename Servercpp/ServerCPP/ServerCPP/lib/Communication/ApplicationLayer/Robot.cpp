#include "robotguide/Communication/ApplicationLayer/Robot.h"
#include "robotguide/Communication/TransportLayer/Connection.h"

using namespace  robotguide::com::transportlayer;
using namespace  robotguide::com::applicationlayer;

Robot::Robot(int id) : id(id), connection(nullptr)
{
}

int Robot::GetRobotId() const
{
	return id;
}

void Robot::SetConnection(Connection& connection)
{
	this->connection = &connection;
}

Connection* Robot::GetConnection() const
{
	return connection;
}

void Robot::HandleMessage(const std::string& message)
{
}

IRobot* Robot::Copy()
{
	return new Robot(*this);
}
