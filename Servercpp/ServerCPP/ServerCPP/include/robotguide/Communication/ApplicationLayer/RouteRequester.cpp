#include "RouteRequester.h"

using namespace robotguide::com::applicationlayer;

RouteRequester::RouteRequester(transportlayer::IRobotInstructor& instructor)
	: instructor(instructor)
{
}

void RouteRequester::HandleMessage(const std::string& message)
{
}
