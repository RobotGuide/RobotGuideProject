#include "robotguide/Communication/TransportLayer/WindowsRobotConnection.h"
#include "robotguide/Communication/ApplicationLayer/Instruction/InstructionPrinter.h"
#include "robotguide/Communication/Exception/ApplicationLayer/Lexer/LexerException.h"
#include "robotguide/Communication/Exception/ApplicationLayer/Parser/ParserException.h"
#include <iostream>
#include <ostream>


using namespace robotguide::com::transportlayer;
using namespace robotguide::com::applicationlayer;
using namespace robotguide::com::exception::applicationlayer;

static constexpr int INVALID_ID = -1;

WindowsRobotConnection::WindowsRobotConnection(IRobotInstructor& robotInstructor, const SOCKET& socketHandler, const unsigned int receiveBufferSize)
	: WindowsConnection(socketHandler, receiveBufferSize), robotInstructor(robotInstructor), robotID(INVALID_ID)
{
	WindowsConnection::Send(InstructionPrinter().InstructionTypeToString(InstructionType::Seni));
}

void WindowsRobotConnection::HandleAvailableData()
{
	WindowsConnection::HandleAvailableData();
	const std::string message(GetReceiveBuffer().GetBuffer());

	if (robotID == INVALID_ID)
	{
		try
		{
			HandleMessage(GetReceiveBuffer().GetBuffer());
		}
		catch (LexerException&)
		{
			Disconnect();
		}
		catch (ParserException&)
		{
			Disconnect();
		}
	}
	else
	{
		// Pass message to robot
	}
	std::cout << message << std::endl;
}

ISelectable* WindowsRobotConnection::Copy() const
{
	return new WindowsRobotConnection(*this);
}

void WindowsRobotConnection::HandleMessage(const std::string& message)
{
	TokenStream tokenStream;
	lexer.GetTokenStream(message, tokenStream);
	InstructionStream instructionStream;
	parser.GetInstructionStream(tokenStream, instructionStream);

	bool isHandled = false;
	for (size_t i = 0; i < instructionStream.size() && !isHandled; i++)
	{
		isHandled = HandleInstruction(*instructionStream[i]);
	}

	//If all of the received messages could no be handled disconnect
	if (!isHandled)
	{
		Disconnect();
	}
}

bool WindowsRobotConnection::HandleInstruction(const Instruction& instruction)
{
	if (instruction.GetType() == InstructionType::Seni)
	{
		if (instruction.GetData().size() == 1)
		{
			//Check if ID is valid
			return true;
		}
		if (instruction.GetData().empty())
		{
			//Get new ID and then Send
			return  true;
		}
	}
	return false;
}
