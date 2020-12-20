#ifndef ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_ROBOTINSTRUCTOR_H
#define ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_ROBOTINSTRUCTOR_H

#include "robotguide/Communication/TransportLayer/IRobotInstructor.h"


class RobotInstructor final : public robotguide::com::transportlayer::IRobotInstructor
{
public:
	RobotInstructor() = default;
	~RobotInstructor() override = default;


};
#endif

