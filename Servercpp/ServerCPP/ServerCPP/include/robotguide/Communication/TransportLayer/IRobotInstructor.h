#ifndef  ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_IROBOTINSTRUCTOR_H
#define  ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_IROBOTINSTRUCTOR_H

#include  "IRobot.h"

namespace robotguide::com::transportlayer
{

	class IRobotInstructor
	{
	public:
		virtual ~IRobotInstructor() = default;
		virtual void AddRobot(IRobot& robot) = 0;
		virtual IRobot* GetRobot(int id) = 0;
		virtual int GetUniqueID() = 0;
	};
}
#endif
