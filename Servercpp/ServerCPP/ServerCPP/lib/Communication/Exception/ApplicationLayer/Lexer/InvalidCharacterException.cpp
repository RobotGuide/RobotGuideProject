#include "robotguide/Communication/Exception/ApplicationLayer/Lexer/InvalidCharacterException.h"

robotguide::com::exception::applicationlayer::InvalidCharacterException::InvalidCharacterException(const char* text) : LexerException(text)
{
}
