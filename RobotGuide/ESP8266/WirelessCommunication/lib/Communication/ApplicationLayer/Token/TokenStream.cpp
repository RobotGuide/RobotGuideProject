#include "robotguide/Communication/ApplicationLayer/Token/TokenStream.h"

robotguide::com::al::TokenStream::TokenStream(const std::vector<std::shared_ptr<Token>>& tokens_)
{
	tokens = tokens_;
}

void robotguide::com::al::TokenStream::AddToken(Token* token)
{
	tokens.push_back(std::shared_ptr<Token>(token));
}

std::string robotguide::com::al::TokenStream::ToString() const
{
	std::string completeString;
	for (const auto& token : tokens)
	{
		completeString += token->ToString() + ": " + token->DataToString() + ", ";
	}
	return completeString;
}

unsigned robotguide::com::al::TokenStream::size() const
{
	return tokens.size();
}
