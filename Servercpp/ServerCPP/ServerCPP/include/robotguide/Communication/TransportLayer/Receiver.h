#ifndef  ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_IRECEIVER_H
#define  ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_IRECEIVER_H

#include "ISelectable.h"
#include <vector>

namespace robotguide::com::transportlayer
{
	class Receiver
	{
	protected:
		std::vector<ISelectable*> selectables;
	public:
		/// <summary>
		/// Destruct a receiver
		/// </summary>
		virtual ~Receiver() = default;

		/// <summary>
		/// Receive data for all socket who have pending data request.
		/// </summary>
		virtual void CheckForData() = 0;

		/// <summary>
		/// Add a new connection to the receiver
		/// </summary>
		/// <param name="socket">The socket you want to manage</param>
		virtual void AddSelectable(ISelectable* socket) = 0;

		/// <summary>
		/// Clean all inactive connections
		/// </summary>
		virtual void Clean() = 0;
	};
}

#endif 
