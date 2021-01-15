#ifndef ROBOTGUIDE_COMMUNICATION_EXCEPTION_PATHFINDING_INVALIDROUTEEXCEPTION_H
#define ROBOTGUIDE_COMMUNICATION_EXCEPTION_PATHFINDING_INVALIDROUTEEXCEPTION_H

#include <exception>

namespace robotguide::com::exception
{
	class InvalidRouteException : public std::exception
	{
	private:
		const char* text;
	public:
		InvalidRouteException(const char* text_);

		char const* what() const override;
	};
}

#endif //ROBOTGUIDE_COMMUNICATION_EXCEPTION_PATHFINDING_INVALIDROUTEEXCEPTION_H