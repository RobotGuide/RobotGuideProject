#ifndef ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_ROBOTINSTRUCTOR_H
#define ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_ROBOTINSTRUCTOR_H

#include "robotguide/Communication/TransportLayer/IRobotInstructor.h"
#include "Robot.h"
#include <vector>



namespace robotguide::com::applicationlayer
{
	class RobotInstructor final : public transportlayer::IRobotInstructor
	{
	private:
		std::vector<Robot*> robots;
		uint64_t nextRobotID;

	public:
		/// <summary>
		/// Initialize the robot instructor
		/// </summary>
		RobotInstructor();

		/// <summary>
		/// Remove all the robot copies we own
		/// </summary>
		~RobotInstructor() override;

		RobotInstructor(const RobotInstructor& instructor) = delete;
		RobotInstructor& operator=(const RobotInstructor& instructor) = delete;

		/// <summary>
		/// Get a specific robot with its ID
		/// </summary>
		/// <param name="id">The id the robot will have</param>
		/// <returns>Returns the robot if found otherwise returns null</returns>
		transportlayer::IRobot* GetRobot(int id) override;

		/// <summary>
		/// Create a new robot
		/// </summary>
		/// <returns>The ID of the newly created robot</returns>
		transportlayer::IRobot& CreateNewRobot() override;


		/// <summary>
		/// Get the robot closes to your target that is connected
		/// </summary>
		/// <param name="x">x coordinate</param>
		/// <param name="y">y coordinate</param>
		/// <returns>The closes robot if no robots are currently connected nullptr will be returned</returns>
		transportlayer::IRobot* GetNearestRobot(int x, int y) override;
	};
}
#endif

