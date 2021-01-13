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

		/// <summary>
		/// Destruct a receiver
		/// </summary>
		virtual ~Receiver();

	public:
		/// <summary>
		/// Receive data for all socket who have pending data request.
		/// </summary>
		virtual void CheckForData() = 0;

		/// <summary>
		/// Add a new connection to the receiver
		/// </summary>
		/// <param name="selectable">The selectable you want to be able to handle receiving for</param>
		void AddSelectable(const ISelectable& selectable);

		/// <summary>
		/// Clean all inactive connections
		/// </summary>
		void Clean();
	};
}

#endif 
