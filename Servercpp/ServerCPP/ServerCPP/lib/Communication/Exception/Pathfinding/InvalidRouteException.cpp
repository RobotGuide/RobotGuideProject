#include "robotguide/Communication/Exception/Pathfinding/InvalidRouteException.h"

robotguide::com::exception::InvalidRouteException::InvalidRouteException(const char* text_) : text(text_)
{
}

char const* robotguide::com::exception::InvalidRouteException::what() const
{
	return text;
}
