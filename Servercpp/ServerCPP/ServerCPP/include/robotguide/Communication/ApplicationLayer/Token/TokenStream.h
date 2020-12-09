#ifndef ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_TOKEN_TOKENSTREAM_H
#define ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_TOKEN_TOKENSTREAM_H

#include "robotguide/Communication/ApplicationLayer/Token/Token.h"
#include <vector>
#include <memory>

namespace robotguide::com::applicationlayer
{
	/*
	 * TokenStreams take ownership of the content they receive.
	 */
	class TokenStream
	{
	private:
		std::vector<Token*> tokens;
	public:
		TokenStream() = default;
		TokenStream(const TokenStream& tokenStream) = delete;
		TokenStream(const std::vector<Token*>& tokens);

		~TokenStream();

		void AddToken(Token* token);
		std::string ToString() const;

		Token* operator[](const unsigned index)
		{
			return tokens[index];
		}

		const Token* operator[](const unsigned index) const
		{
			return tokens[index];
		}

		unsigned size() const;

		TokenStream& operator=(const TokenStream& tokenStream) = delete;
	};
}

#endif //ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_TOKEN_TOKENSTREAM_H