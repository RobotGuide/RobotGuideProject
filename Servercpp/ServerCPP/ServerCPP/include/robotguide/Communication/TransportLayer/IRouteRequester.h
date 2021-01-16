#ifndef ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_IROUTEREQUESTER_H
#define ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_IROUTEREQUESTER_H

#include <string>

namespace robotguide::com::transportlayer
{
	class IRouteRequester
	{
	public:

		virtual ~IRouteRequester() = default;

		/// <summary>
		/// Handle a message from the transport layer
		/// </summary>
		/// <param name="message">The message you need to handle</param>
		virtual std::string HandleMessage(const std::string& message) = 0;
	};
}

#endif
