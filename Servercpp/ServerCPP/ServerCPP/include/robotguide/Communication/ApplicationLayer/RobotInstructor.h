#ifndef ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_ROBOTINSTRUCTOR_H
#define ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_ROBOTINSTRUCTOR_H

#include "robotguide/Communication/TransportLayer/IRobotInstructor.h"
#include "robotguide/Communication/TransportLayer/IRobot.h"
#include <vector>


namespace robotguide::com::applicationlayer
{
	class RobotInstructor final : public transportlayer::IRobotInstructor
	{
	private:
		std::vector<transportlayer::IRobot*> robots;
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
		/// Add a robot to the robot instructor
		/// </summary>
		/// <param name="robot">The new robot</param>
		void AddRobot(transportlayer::IRobot& robot) override;

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
	};
}
#endif

