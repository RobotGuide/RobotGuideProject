#ifndef  ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_IROBOT_H
#define  ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_IROBOT_H

#include "robotguide/Communication/TransportLayer/Connection.h"

namespace robotguide {
	namespace com {
		namespace applicationlayer {
			class InstructionStream;
		}
	}
}

namespace robotguide::com::transportlayer
{
	class IRobot
	{
	public:
		virtual ~IRobot() = default;

		/// <summary>
		/// Get the ID from this robot. This is used for reconnecting to a specific robot.
		/// </summary>
		/// <returns>The robots ID</returns>
		virtual int GetRobotId() const = 0;

		/// <summary>
		/// Check if the robot is connected
		/// </summary>
		/// <returns>The connectivity state</returns>
		bool Isconnected() const;

		/// <summary>
		/// Set a connection to the transport layer
		/// </summary>
		/// <param name="connection">The connection that this robot has</param>
		virtual void SetConnection(Connection* connection) = 0;

		/// <summary>
		/// Get the connection we have to the actual robot
		/// </summary>
		/// <returns>The connection if </returns>
		virtual Connection* GetConnection() const = 0;

		/// <summary>
		/// Handle a message from the transport layer
		/// </summary>
		/// <param name="message">The message you need to handle</param>
		virtual void HandleMessage(const std::string& message) = 0;

		/// <summary>
		/// Get current coordinates of the robot
		/// </summary>
		/// <returns>A copy of IRobot</returns>
		virtual std::tuple<int, int> GetCoordinates() const = 0;

		/// <summary>
		/// Add instructions to this Robot
		/// </summary>
		/// <param name="stream">The stream you want to add</param>
		/// <param name="endCoordinates">The end coordinates for the robot after handling all instructions</param>
		virtual void AddInstructions(const applicationlayer::InstructionStream& stream, const std::tuple<int, int>& endCoordinates) = 0;

		/// <summary>
		/// Get a copy of a robot child class
		/// </summary>
		/// <returns>A copy of IRobot</returns>
		virtual IRobot* Copy() = 0;
	};
}

#endif
