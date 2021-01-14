#ifndef  ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_ROBOT_H
#define  ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_ROBOT_H

#include "robotguide/Communication/TransportLayer/Connection.h"
#include "robotguide/Communication/TransportLayer/IRobot.h"
#include "robotguide/Communication/ApplicationLayer/Instruction/InstructionStream.h"
#include "Lexer/Lexer.h"
#include "Parser/Parser.h"
#include <queue>


namespace robotguide::com::applicationlayer
{
	class Robot final : public transportlayer::IRobot
	{
	private:
		int id;
		transportlayer::Connection* connection;
		std::tuple<int, int> coordinates;
		std::tuple<int, int> targetCoordinates;
		std::queue<std::string> instructions;
		Lexer lexer;
		Parser parser;

		bool isOnRoute;

	public:
		/// <summary>
		/// Initialize a robot with its ID
		/// </summary>
		/// <param name="id">The ID this robot has</param>
		Robot(int id);
		~Robot() override = default;
		Robot(const Robot& listener) = default;
		Robot& operator=(const Robot& listener) = default;

		/// <summary>
		/// Get the ID from this robot. This is used for reconnecting to a specific robot.
		/// </summary>
		/// <returns>The robots ID</returns>
		int GetRobotId() const override;

		/// <summary>
		/// Check if the robot is connected
		/// </summary>
		/// <returns>The connectivity state</returns>
		bool Isconnected() const;

		/// <summary>
		/// Set a connection to the transport layer
		/// </summary>
		/// <param name="connection">The connection that this robot has</param>
		void SetConnection(transportlayer::Connection* connection) override;

		/// <summary>
		/// Get the connection we have to the actual robot
		/// </summary>
		/// <returns>The connection if </returns>
		transportlayer::Connection* GetConnection() const override;

		/// <summary>
		/// Handle a message from the transport layer
		/// </summary>
		/// <param name="message">The message you need to handle</param>
		void HandleMessage(const std::string& message) override;

		/// <summary>
		/// Get coords of the robot
		/// </summary>
		/// <returns>The coordinates</returns>
		std::tuple<int, int> GetCoordinates() const override;

		/// <summary>
		/// Add instructions to this Robot
		/// </summary>
		/// <param name="stream">The stream you want to add</param>
		/// <param name="endCoordinates">The end coordinates for the robot after handling all instructions</param>
		void AddInstructions(const InstructionStream& stream, const std::tuple<int, int>& endCoordinates) override;

		/// <summary>
		/// Get a copy of the robot
		/// </summary>
		/// <returns>A copy of IRobot</returns>
		IRobot* Copy() override;

	private:
		void HandleInstruction(const Instruction& instruction);
		void SendNextInstruction();
	};
}

#endif
