#include "robotguide\Communication\TransportLayer\Robot.h"

using namespace  robotguide::com::transportlayer;

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
