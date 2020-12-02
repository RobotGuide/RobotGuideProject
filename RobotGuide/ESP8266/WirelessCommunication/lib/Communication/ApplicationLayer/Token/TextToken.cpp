#include "robotguide/Communication/ApplicationLayer/Token/TextToken.h"

robotguide::com::al::TextToken::TextToken(const char* data) : Token(TokenType::Text, InstructionData(data))
{
}

robotguide::com::al::TextToken::TextToken(const std::string& data) : Token(TokenType::Text, InstructionData(data))
{
}
