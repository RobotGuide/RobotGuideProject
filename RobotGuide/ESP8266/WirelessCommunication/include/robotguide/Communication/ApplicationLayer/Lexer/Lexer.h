#ifndef ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_LEXER_LEXER_H
#define ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_LEXER_LEXER_H

#include "robotguide/Communication/ApplicationLayer/Token/TokenStream.h"
#include "robotguide/Communication/ApplicationLayer/Lexer/LexerState.h"
#include "robotguide/Communication/ApplicationLayer/Lexer/LexerCharacterType.h"
#include <string>

namespace robotguide { namespace com { namespace al 
{
	class Lexer
	{
	private:
		LexerState currentState = LexerState::None;
		std::string buffer;
	public:
		Lexer() = default;

		TokenStream GetTokenStream(const char& text);
		TokenStream GetTokenStream(const std::string& text);

		LexerState CurrentState() const;
	private:
		void ResetLexer();
		void AddCharacterToBufferAndRetrieveToken(TokenStream& stream,
		                                          const char character);

		LexerState LexCharacter(const char character) const;
		void UpdateCurrentState(const LexerState newState);

		LexerCharacterType GetCharacterType(const char character) const;
		Token* GetToken() const;

		Token* GetTextToken() const;
		Token* GetDecimalToken() const;
		Token* GetIntToken() const;
		Token* GetInstructionToken() const;

		bool CurrentStateIsStringDeclaration() const;
		bool CurrentStateIsHead() const;
		bool CurrentStateIsInteger() const;
		bool CurrentStateIsDecimal() const;
		bool CurrentStateIsText() const;
		bool CurrentStateIsNone() const;
	};
}}}

#endif //ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_LEXER_LEXER_H