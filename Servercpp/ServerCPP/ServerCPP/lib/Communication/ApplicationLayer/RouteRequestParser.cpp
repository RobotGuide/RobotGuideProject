#include "robotguide/Communication/ApplicationLayer/RouteRequestParser.h"
#include "robotguide/Communication/Exception/ApplicationLayer/Parser/ParserException.h"
#include <sstream>

static const char* GOTO_CMD = "GOTO";
static const int INVALID_ARG = -858993460; // signifies that parsing argument was unsuccessful

RouteRequest RouteRequestParser::ParseRequestToRoute(const std::string& message)
{
    std::stringstream stream(message);
    
    std::string cmd;
    stream >> cmd;

    if (cmd.compare(GOTO_CMD) != 0)
    {
        throw  robotguide::com::exception::applicationlayer::ParserException("incorrect command was given");
    }

    int args[4];

    for (int i = 0; i < 4; i++)
    {
        stream >> args[i];
        if (args[i] == INVALID_ARG)
        {
            throw robotguide::com::exception::applicationlayer::ParserException("incorrect argument was given");
        }
    }

    RouteRequest parsedRequest = { args[0], args[1], args[2], args[3] };

    return parsedRequest;
}