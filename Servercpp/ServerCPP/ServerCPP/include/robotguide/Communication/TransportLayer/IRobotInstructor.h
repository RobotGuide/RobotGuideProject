#ifndef  ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_IROBOTINSTRUCTOR_H
#define  ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_IROBOTINSTRUCTOR_H

#include  "Robot.h"

namespace robotguide::com::transportlayer
{

	class IRobotInstructor
	{
	public:
		virtual ~IRobotInstructor() = default;
		virtual void AddRobot(Robot& robot) = 0;
		virtual Robot* GetRobot(int id) = 0;
		virtual int GetUniqueID() = 0;
	};
}
#endif
