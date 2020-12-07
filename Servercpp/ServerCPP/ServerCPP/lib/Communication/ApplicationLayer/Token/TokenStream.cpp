#include "robotguide/Communication/ApplicationLayer/Token/TokenStream.h"

robotguide::com::applicationlayer::TokenStream::TokenStream(const std::vector<std::shared_ptr<Token>>& tokens_)
{
	tokens = tokens_;
}

void robotguide::com::applicationlayer::TokenStream::AddToken(Token* token)
{
	tokens.push_back(std::shared_ptr<Token>(token));
}

std::string robotguide::com::applicationlayer::TokenStream::ToString() const
{
	std::string completeString;
	for (const auto& token : tokens)
	{
		completeString += token->ToString() + ": " + token->DataToString() + ", ";
	}
	return completeString;
}

unsigned robotguide::com::applicationlayer::TokenStream::size() const
{
	return tokens.size();
}
