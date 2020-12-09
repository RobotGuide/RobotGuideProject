#ifndef ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_LEXER_LEXER_H
#define ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_LEXER_LEXER_H

#include "robotguide/Communication/ApplicationLayer/Token/TokenStream.h"
#include "robotguide/Communication/ApplicationLayer/Lexer/LexerState.h"
#include "robotguide/Communication/ApplicationLayer/Lexer/LexerCharacterType.h"
#include <string>

namespace robotguide::com::applicationlayer
{
	class Lexer
	{
	private:
		LexerState currentState = LexerState::None;
		std::string buffer;
	public:
		Lexer() = default;

		void GetTokenStream(const char& text, TokenStream& stream) const;
		void GetTokenStream(const std::string& text, TokenStream& stream);

		LexerState CurrentState() const;
	private:
		void ResetLexer();
		void AddCharacterToBufferAndRetrieveToken(TokenStream& stream,
		                                          const char character);

		[[nodiscard]] LexerState LexCharacter(const char character) const;
		void UpdateCurrentState(const LexerState newState);

		[[nodiscard]] LexerCharacterType GetCharacterType(const char character) const;
		[[nodiscard]] Token* GetToken() const;

		[[nodiscard]] Token* GetTextToken() const;
		[[nodiscard]] Token* GetDecimalToken() const;
		[[nodiscard]] Token* GetIntToken() const;
		[[nodiscard]] Token* GetInstructionToken() const;

		[[nodiscard]] bool CurrentStateIsStringDeclaration() const;
		[[nodiscard]] bool CurrentStateIsHead() const;
		[[nodiscard]] bool CurrentStateIsInteger() const;
		[[nodiscard]] bool CurrentStateIsDecimal() const;
		[[nodiscard]] bool CurrentStateIsText() const;
		[[nodiscard]] bool CurrentStateIsNone() const;
	};
}

#endif //ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_LEXER_LEXER_H