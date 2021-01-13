#include "robotguide/Communication/ApplicationLayer/Robot.h"
#include "robotguide/Communication/TransportLayer/Connection.h"
#include <iostream>

using namespace robotguide::com::transportlayer;
using namespace robotguide::com::applicationlayer;

Robot::Robot(int id) : id(id), connection(nullptr)
{
	std::cout << "A new Robot connected " << id << std::endl;
}

int Robot::GetRobotId() const
{
	return id;
}

void Robot::SetConnection(Connection& connection)
{
	this->connection = &connection;
	std::cout << "A robot reconnected " << id << std::endl;
}

Connection* Robot::GetConnection() const
{
	return connection;
}

void Robot::HandleMessage(const std::string& message)
{
	std::cout << "Robot " << id << ": " << message;
}

IRobot* Robot::Copy()
{
	return new Robot(*this);
}
