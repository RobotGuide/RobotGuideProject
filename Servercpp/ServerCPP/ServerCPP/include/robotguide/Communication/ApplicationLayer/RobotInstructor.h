#ifndef ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_ROBOTINSTRUCTOR_H
#define ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_ROBOTINSTRUCTOR_H

#include "robotguide/Communication/TransportLayer/IRobotInstructor.h"
#include <vector>

namespace robotguide::com::applicationlayer
{
	class RobotInstructor final : public transportlayer::IRobotInstructor
	{
	private:
		std::vector<transportlayer::Robot*> robots;
		uint64_t nextRobotID;

	public:
		RobotInstructor();
		~RobotInstructor() override;
		RobotInstructor(const RobotInstructor& instructor) = delete;
		RobotInstructor& operator=(const RobotInstructor& instructor) = delete;

		void AddRobot(transportlayer::Robot& robot) override;

		transportlayer::Robot* GetRobot(int id) override;

		int GetUniqueID() override;

	};
}
#endif

