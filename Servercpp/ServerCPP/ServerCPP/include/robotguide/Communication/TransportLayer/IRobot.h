#ifndef  ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_IROBOT_H
#define  ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_IROBOT_H

#include "robotguide/Communication/TransportLayer/Connection.h"

namespace robotguide::com::transportlayer
{
	class IRobot
	{
	public:
		virtual ~IRobot() = default;
		virtual int GetRobotId() const = 0;
		virtual void SetConnection(Connection& connection) = 0;
		virtual Connection* GetConnection() const = 0;
		virtual void HandleMessage(const std::string& message) = 0;

		virtual IRobot* Copy() = 0;
	};
}

#endif
