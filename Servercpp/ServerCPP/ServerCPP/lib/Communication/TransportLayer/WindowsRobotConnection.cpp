#include "robotguide/Communication/TransportLayer/WindowsRobotConnection.h"
#include "robotguide/Communication/ApplicationLayer/Instruction/InstructionPrinter.h"
#include "robotguide/Communication/Exception/ApplicationLayer/Lexer/LexerException.h"
#include "robotguide/Communication/Exception/ApplicationLayer/Parser/ParserException.h"
#include <ostream>

using namespace robotguide::com::transportlayer;
using namespace robotguide::com::applicationlayer;
using namespace robotguide::com::exception::applicationlayer;

static constexpr int INVALID_ID = -1;

WindowsRobotConnection::WindowsRobotConnection(IRobotInstructor& robotInstructor,
	const SOCKET& socketHandler,
	const unsigned int receiveBufferSize)
	: WindowsConnection(socketHandler, receiveBufferSize)
	, robotInstructor(robotInstructor)
	, robotID(INVALID_ID)
{
	WindowsConnection::Send(InstructionPrinter().InstructionTypeToString(InstructionType::Aski) + " 0 " + '\n');
}

WindowsRobotConnection::~WindowsRobotConnection()
{
	if (robotID != INVALID_ID)
	{
		IRobot* robot = robotInstructor.GetRobot(robotID);
		if (robot != nullptr)
		{
			robot->SetConnection(nullptr);
		}
	}
}

WindowsRobotConnection::WindowsRobotConnection(const WindowsRobotConnection& connection)
	: WindowsConnection(connection.socketHandle, connection.receiveBuffer.GetMaxLength())
	, robotInstructor(connection.robotInstructor)
	, robotID(INVALID_ID)
{
}

void WindowsRobotConnection::HandleAvailableData()
{
	WindowsConnection::HandleAvailableData();
	const std::string message(GetReceiveBuffer().GetBuffer());

	if (socketHandle == INVALID_SOCKET)
	{
		return;
	}

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
		IRobot* robot = robotInstructor.GetRobot(robotID);
		if (robot != nullptr)
		{
			robot->HandleMessage(message);
		}
		else
		{
			Disconnect();
		}
	}
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

	//If all of the received messages could not be handled disconnect
	if (!isHandled)
	{
		Disconnect();
	}
}

bool WindowsRobotConnection::HandleInstruction(const Instruction& instruction)
{
	if (instruction.GetType() == InstructionType::Seni)
	{
		if (instruction.GetData().size() == 2)
		{
			robotID = instruction.GetData()[1].GetInteger();

			IRobot* robot = robotInstructor.GetRobot(robotID);
			if (robot == nullptr)
			{
				return false;
			}
			robot->SetConnection(this);
			return true;
		}
		if (instruction.GetData().size() == 1)
		{
			IRobot& robot = robotInstructor.CreateNewRobot();
			robot.SetConnection(this);
			robotID = robot.GetRobotId();
			const std::string command = InstructionPrinter().InstructionTypeToString(InstructionType::Seti) + " 0 " + std::to_string(robotID) + '\n';
			Send(command);
			return  true;
		}
	}
	return false;
}
