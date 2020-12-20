#ifndef ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_WINDOWSROBOTCONNECTION_H
#define ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_WINDOWSROBOTCONNECTION_H

#include "WindowsConnection.h"
#include "IRobotInstructor.h"

namespace robotguide::com::transportlayer
{
	class WindowsRobotConnection final : public WindowsConnection
	{
	private:
		IRobotInstructor& robotInstructor;
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
		virtual void HandleAvailableData() override;
	};
}

#endif
