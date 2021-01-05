#ifndef  ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_ROBOT_H
#define  ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_ROBOT_H

#include "Connection.h"

namespace robotguide::com::transportlayer
{

	class Robot
	{
	private:
		int id;
		Connection* connection;

	public:
		Robot(int id);
		~Robot() = default;

		int GetRobotId() const;
		void SetConnection(Connection& connection);
		Connection* GetConnection() const;
	};
}

#endif
