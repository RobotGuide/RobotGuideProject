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
		/// Get a specific robot with its ID
		/// </summary>
		/// <param name="id">The id the robot will have</param>
		/// <returns>Returns the robot if found otherwise returns null</returns>
		virtual IRobot* GetRobot(int id) = 0;

		/// <summary>
		/// Get the robot closes to your target that is connected
		/// </summary>
		/// <param name="x">x coordinate</param>
		/// <param name="y">y coordinate</param>
		/// <returns>The closes robot if no robots are currently connected nullptr will be returned</returns>
		virtual IRobot* GetNearestRobot(int x, int y) = 0;

		/// <summary>
		/// Create a new robot
		/// </summary>
		/// <returns>The ID of the newly created robot</returns>
		virtual IRobot& CreateNewRobot() = 0;
	};
}
#endif
