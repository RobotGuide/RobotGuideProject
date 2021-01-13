#ifndef  ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_IROBOTINSTRUCTOR_H
#define  ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_IROBOTINSTRUCTOR_H

#include  "IRobot.h"

namespace robotguide::com::transportlayer
{

	class IRobotInstructor
	{
	public:
		virtual ~IRobotInstructor() = default;

		/// <summary>
		/// Add a robot to the robot instructor
		/// </summary>
		/// <param name="robot">The new robot</param>
		virtual void AddRobot(IRobot& robot) = 0;

		/// <summary>
		/// Get a specific robot with its ID
		/// </summary>
		/// <param name="id">The id the robot will have</param>
		/// <returns>Returns the robot if found otherwise returns null</returns>
		virtual IRobot* GetRobot(int id) = 0;

		/// <summary>
		/// Create a new robot
		/// </summary>
		/// <returns>The ID of the newly created robot</returns>
		virtual IRobot& CreateNewRobot() = 0;
	};
}
#endif
