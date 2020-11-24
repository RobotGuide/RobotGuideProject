#include "robotguide/Communication/Exception/ApplicationLayer/Lexer/InvalidCharacterException.h"

robotguide::com::exception::al::InvalidCharacterException::InvalidCharacterException(const char* text) : LexerException(text)
{
}
