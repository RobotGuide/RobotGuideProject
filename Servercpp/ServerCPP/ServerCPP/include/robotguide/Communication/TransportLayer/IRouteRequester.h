#ifndef ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_IROUTEREQUESTER_H
#define ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_IROUTEREQUESTER_H

#include <string>

namespace robotguide::com::transportlayer
{
	class IRouteRequester
	{
	public:

		virtual ~IRouteRequester() = default;
		virtual void HandleMessage(const std::string& message) = 0;
	};
}

#endif
