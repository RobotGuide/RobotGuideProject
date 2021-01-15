#include "pch.h"
#include "robotguide/Communication/ApplicationLayer/Lexer/Lexer.h"
#include "robotguide/Communication/ApplicationLayer/Parser/Parser.h"
#include "robotguide/Communication/Exception/ApplicationLayer/Lexer/LexerException.h"
#include "robotguide/Communication/ApplicationLayer/Instruction/InstructionPrinter.h"
#include <iostream>
#include "robotguide/Communication/Exception/ApplicationLayer/ApplicationLayerException.h"


using namespace robotguide::com::applicationlayer;

int main()
{
	auto lexer = Lexer();
	auto parser = Parser();
	auto instructionPrinter = InstructionPrinter();

	while(true)
	{
		lexer.ResetLexer();
		parser.ResetParser();
		std::string input = " ";
		std::getline(std::cin, input);
		try
		{
			TokenStream tokenStream;
			lexer.GetTokenStream(input, tokenStream);
			std::cout << tokenStream.ToString() << std::endl;

			InstructionStream instructionStream;
			parser.GetInstructionStream(tokenStream, instructionStream);
			std::cout << instructionStream.ToString() << std::endl;
		}
		catch(robotguide::com::exception::applicationlayer::LexerException& ex)
		{
			std::cout << "Error occured! Current state: " << (unsigned)lexer.CurrentState() << std::endl;
			std::cout << ex.what() << std::endl;
		}
		catch(robotguide::com::exception::applicationlayer::ApplicationLayerException& ex)
		{
			std::cout << ex.what() << std::endl;
		}
	}
}
