#include "robotguide/Communication/ApplicationLayer/RouteRequestParser.h"
#include "robotguide/Communication/Exception/ApplicationLayer/Parser/ParserException.h"
#include <sstream>

routeRequest RouteRequestParser::ParseRequestToRoute(const std::string& message)
{

    std::stringstream stream(message);
    
    std::string cmd;
    stream >> cmd;

    if (cmd.compare("GOTO") != 0)
    {
        throw  robotguide::com::exception::applicationlayer::ParserException("incorrect command was given");
    }

    int args[4];

    for (int i = 0; i < 4; i++)
    {
        stream >> args[i];
        if (args[i] == -858993460) // signifies that parsing argument was unsuccessful
        {
            throw robotguide::com::exception::applicationlayer::ParserException("incorrect argument was given");
        }
    }

    routeRequest parsedRequest = { args[0], args[1], args[2], args[3] };

    return parsedRequest;
}