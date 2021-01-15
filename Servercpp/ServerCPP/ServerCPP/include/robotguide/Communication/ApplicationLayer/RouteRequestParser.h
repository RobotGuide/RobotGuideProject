#ifndef ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_ROUTEREQUESTPARSER_H
#define ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_ROUTEREQUESTPARSER_H

#include "robotguide/Communication/ApplicationLayer/RouteRequest.h"
#include <string>

class RouteRequestParser
{
public:
	RouteRequestParser() = delete;
	RouteRequestParser(const RouteRequestParser& other) = delete;
	RouteRequestParser& operator=(const RouteRequestParser&) = delete;
	~RouteRequestParser() = delete;

	/// <summary>
	/// Parses a route request string to a routeRequest object. <br/>
	/// The route request string has to use the following syntax: <br/>
	/// GOTO [current x pos] [current y pos] [destination x pos] [destination y pos] <br/>
	/// Throws a ParserException if the input was invalid <br/>
	/// </summary>
	/// <param name="message">The route request string</param>
	/// <returns>Returns the routeRequest struct</returns>
	static RouteRequest ParseRequestToRoute(const std::string& message);
};

#endif // !ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_ROUTEREQUESTPARSER_H
