#ifndef ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_WINDOWSROBOTCONNECTION_H
#define ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_WINDOWSROBOTCONNECTION_H

#include "WindowsConnection.h"
#include "IRobotInstructor.h"
#include "robotguide/Communication/ApplicationLayer/Lexer/Lexer.h"
#include "robotguide/Communication/ApplicationLayer/Parser/Parser.h"


namespace robotguide::com::transportlayer
{
	class WindowsRobotConnection final : public WindowsConnection
	{
	private:
		IRobotInstructor& robotInstructor;
		int robotID;
		applicationlayer::Lexer lexer;
		applicationlayer::Parser parser;

	public:
		/// <summary>
		/// Initialize the connection between a robot and the server
		/// </summary>
		/// <param name="robotInstructor">This is used for the robot to request new instructions</param>
		/// <param name="socketHandler">The socket handler for this connection</param>
		/// <param name="receiveBufferSize">The receive buffer size</param>
		WindowsRobotConnection(IRobotInstructor& robotInstructor, const SOCKET& socketHandler, unsigned int receiveBufferSize);
		~WindowsRobotConnection() override = default;

		/// <summary>
		/// Handle responses from the robot
		/// </summary>
		void HandleAvailableData() override;

		/// <summary>
		/// Copy a robot connection
		/// </summary>
		/// <returns>The copy in the heap</returns>
		ISelectable* Copy() const override;

	private:
		void HandleMessage(const std::string& message);
		bool HandleInstruction(const applicationlayer::Instruction& instruction);
	};
}

#endif
