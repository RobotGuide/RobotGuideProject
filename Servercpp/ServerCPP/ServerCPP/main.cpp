#include "robotguide/Communication/ApplicationLayer/TokenType.h"
#include <iostream>

int main()
{
	std::cout << "Hallo!" << static_cast<unsigned>(robotguide::com::applicationlayer::TokenType::Text) << std::endl;
}