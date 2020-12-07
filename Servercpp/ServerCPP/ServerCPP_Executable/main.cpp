#include "pch.h"
#include "robotguide/Communication/ApplicationLayer/Lexer/Lexer.h"
#include "robotguide/Communication/ApplicationLayer/Parser/Parser.h"
#include "robotguide/Communication/Exception/ApplicationLayer/Lexer/LexerException.h"
#include <iostream>

int main()
{
	auto lexer = robotguide::com::applicationlayer::Lexer();
	auto parser = robotguide::com::applicationlayer::Parser();

	while(true)
	{
		std::string input = " ";
		std::getline(std::cin, input);
		try
		{
			auto tokenStream = lexer.GetTokenStream(input);
			std::cout << tokenStream.ToString() << std::endl;

			auto instructionStream = parser.GetInstructionStream(tokenStream);
			std::cout << instructionStream.ToString() << std::endl;
		}
		catch(robotguide::com::exception::al::LexerException& ex)
		{
			std::cout << "Error occured! Current state: " << (unsigned)lexer.CurrentState() << std::endl;
			std::cout << ex.what() << std::endl;
		}
	}
}
