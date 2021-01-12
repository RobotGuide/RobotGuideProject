#ifndef  ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_ROBOT_H
#define  ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_ROBOT_H

#include "robotguide/Communication/TransportLayer/Connection.h"
#include "robotguide/Communication/TransportLayer/IRobot.h"

namespace robotguide::com::applicationlayer
{
	class Robot : public transportlayer::IRobot
	{
	private:
		int id;
		transportlayer::Connection* connection;

	public:
		Robot(int id);
		~Robot() override = default;
		Robot(const Robot& listener) = default;
		Robot& operator=(const Robot& listener) = default;


		int GetRobotId() const override;
		void SetConnection(transportlayer::Connection& connection) override;
		transportlayer::Connection* GetConnection() const override;
		void HandleMessage(const std::string& message) override;
		IRobot* Copy() override;
	};
}

#endif
