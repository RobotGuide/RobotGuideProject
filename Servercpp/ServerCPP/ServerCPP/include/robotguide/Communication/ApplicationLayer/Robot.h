#ifndef  ROBOTGUIDE_COMMUNICATION_APPLICATRIONLAYER_ROBOT_H
#define  ROBOTGUIDE_COMMUNICATION_APPLICATRIONLAYER_ROBOT_H

#include "robotguide/Communication/TransportLayer/Connection.h"


namespace robotguide::com::applicationlayer
{
	class Robot
	{
	private:
		int id;
		transportlayer::Connection* connection;

	public:
		Robot(int id);
		~Robot() = default;

		int GetRobotId() const;
		void SetConnection(transportlayer::Connection& connection);
		transportlayer::Connection* GetConnection() const;
		void HandleMessage(const std::string& message);
	};
}

#endif
