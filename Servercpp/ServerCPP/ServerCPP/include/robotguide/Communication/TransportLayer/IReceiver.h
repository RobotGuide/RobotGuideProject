#ifndef  ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_IRECEIVER_H
#define  ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_IRECEIVER_H

#include "robotguide/Communication/TransportLayer/IConnection.h"
#include <vector>

namespace robotguide::com::transportlayer
{
	class IReceiver
	{
	public:
		/// <summary>
		/// Destruct a connection
		/// </summary>
		virtual ~IReceiver() = default;

		/// <summary>
		/// Receive data for all socket who have pending data request.
		/// </summary>
		/// <param name="connections">The connections you want to check for data</param>
		virtual void ReceiveData(const std::vector<IConnection*>& connections) = 0;
	};
}

#endif 
