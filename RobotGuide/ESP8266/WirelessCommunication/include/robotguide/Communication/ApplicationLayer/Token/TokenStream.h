#ifndef ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_TOKEN_TOKENSTREAM_H
#define ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_TOKEN_TOKENSTREAM_H

#include "robotguide/Communication/ApplicationLayer/Token/Token.h"
#include <vector>
#include <memory>

namespace robotguide { namespace com { namespace al 
{
	class TokenStream
	{
	private:
		std::vector<std::shared_ptr<Token>> tokens;
	public:
		TokenStream() = default;
		TokenStream(const std::vector<std::shared_ptr<Token>>& tokens);

		void AddToken(Token* token);
		std::string ToString() const;

		std::shared_ptr<Token>& operator[](const unsigned index)
		{
			return tokens[index];
		}

		const std::shared_ptr<Token>& operator[](const unsigned index) const
		{
			return tokens[index];
		}

		unsigned size() const;
	};
}}}

#endif //ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_TOKEN_TOKENSTREAM_H