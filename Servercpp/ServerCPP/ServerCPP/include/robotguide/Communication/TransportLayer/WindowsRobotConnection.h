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
		WindowsRobotConnection(IRobotInstructor& robotInstructor, const SOCKET& socketHandler, unsigned int receiveBufferSize);
		virtual void HandleAvailableData() override;
	};
}

#endif
