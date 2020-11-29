#ifndef ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_WINDOWSRECEIVER_H
#define ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_WINDOWSRECEIVER_H


#include "IReceiver.h"
#include <vector>
#include <WinSock2.h>

namespace robotguide::com::transportlayer
{

	class WindowsReceiver final : public IReceiver
	{
	private:
		FD_SET ReadSet = {};

	public:
		WindowsReceiver();
		~WindowsReceiver() override;
		void ReceiveData(const std::vector<std::shared_ptr<IConnection>>& connections) override;
	};
}


#endif
