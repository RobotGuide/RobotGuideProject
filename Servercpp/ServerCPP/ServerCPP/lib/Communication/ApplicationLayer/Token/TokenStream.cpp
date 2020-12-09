#include "robotguide/Communication/ApplicationLayer/Token/TokenStream.h"

using namespace robotguide::com::applicationlayer;

TokenStream::TokenStream(const std::vector<Token*>& tokens_)
{
	tokens = tokens_;
}

TokenStream::~TokenStream()
{
	for (auto* token : tokens)
	{
		delete token;
		token = nullptr;
	}
}

void TokenStream::AddToken(Token* token)
{
	tokens.push_back(token);
}

std::string TokenStream::ToString() const
{
	std::string completeString;
	for (const auto& token : tokens)
	{
		completeString += token->ToString() + ": " + token->DataToString() + ", ";
	}
	return completeString;
}

unsigned TokenStream::size() const
{
	return tokens.size();
}
