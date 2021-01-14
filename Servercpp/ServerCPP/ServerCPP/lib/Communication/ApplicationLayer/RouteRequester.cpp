#include "robotguide/Communication/ApplicationLayer/RouteRequester.h"
#include <iostream>

using namespace robotguide::com::applicationlayer;

RouteRequester::RouteRequester(transportlayer::IRobotInstructor& instructor)
	: instructor(instructor)
{
}

void RouteRequester::HandleMessage(const std::string& message)
{
	std::cout << "User: " << message;
}

