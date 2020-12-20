#ifndef ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_ISELECTABLE_H
#define ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_ISELECTABLE_H

#include "ISocket.h"

namespace robotguide::com::transportlayer
{
	class ISelectable : public ISocket
	{
	public:
		/// <summary>
		/// Destructs a selectable object
		/// </summary>
		virtual ~ISelectable() = default;

		/// <summary>
		/// Handle the data. This should only be called when the socket has data available.
		/// </summary>
		virtual void HandleAvailableData() = 0;

		virtual void Copy();
	};
}


#endif
