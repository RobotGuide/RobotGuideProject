#include "robotguide/Communication/ApplicationLayer/Robot.h"
#include "robotguide/Communication/TransportLayer/Connection.h"
#include "robotguide/Communication/ApplicationLayer/Instruction/InstructionPrinter.h"
#include "robotguide/Communication/ApplicationLayer/Token/TokenStream.h"
#include "robotguide/Communication/Exception/ApplicationLayer/Lexer/LexerException.h"
#include "robotguide/Communication/Exception/ApplicationLayer/Parser/ParserException.h"
#include <iostream>

using namespace robotguide::com::transportlayer;
using namespace robotguide::com::applicationlayer;
using namespace robotguide::com::exception::applicationlayer;

Robot::Robot(const int id)
	: id(id)
	, connection(nullptr)
	, coordinates(0, 0)
	, angle(0)
	, targetCoordinates(0, 0)
	, targetAngle(0)
	, isOnRoute(false)
{
	std::cout << "A new Robot connected " << id << std::endl;
}

int Robot::GetRobotId() const
{
	return id;
}

bool Robot::IsConnected() const
{
	return connection != nullptr;
}

void Robot::SetConnection(Connection* connection)
{
	this->connection = connection;
	std::cout << (!IsConnected() ? "A robot disconnected " : "A robot reconnected ") << id << std::endl;
}

Connection* Robot::GetConnection() const
{
	return connection;
}

int Robot::GetRotationAngle() const
{
	return angle;
}

void Robot::HandleMessage(const std::string& message)
{
	try
	{
		TokenStream tokenStream;
		lexer.GetTokenStream(message, tokenStream);
		InstructionStream instructionStream;
		parser.GetInstructionStream(tokenStream, instructionStream);

		for (Instruction* instruction : instructionStream)
		{
			HandleInstruction(*instruction);
		}
	}
	catch (LexerException&)
	{
		std::cout << "Lexer exception encountered" << std::endl;
	}
	catch (ParserException&)
	{
		std::cout << "Parser exception encountered" << std::endl;
	}
	std::cout << "Robot " << id << ": " << message;
}


std::tuple<int, int> Robot::GetCoordinates() const
{
	return coordinates;
}

void Robot::AddInstructions(const InstructionStream& stream, const std::tuple<int, int>& endCoordinates, const int endAngle)
{
	for (size_t i = 0; i < stream.size(); i++)
	{
		instructions.push(stream[i].ToString());
	}
	targetCoordinates = endCoordinates;
	targetAngle = endAngle;

	//Start the route of this robot is not yet on one.
	//To start we have to make sure that we actually received instructions
	if (!isOnRoute && !instructions.empty() && IsConnected())
	{
		SendNextInstruction();
		isOnRoute = true;
	}
}

IRobot* Robot::Copy()
{
	return new Robot(*this);
}

void Robot::HandleInstruction(const Instruction& instruction)
{
	if (instruction.GetType() == InstructionType::Navs)
	{
		if (connection != nullptr)
		{
			if (!instructions.empty())
			{
				SendNextInstruction();
			}
			else
			{
				coordinates = targetCoordinates;
				angle = targetAngle;
				isOnRoute = false;
			}
		}
	}
}

void Robot::SendNextInstruction()
{
	if (!instructions.empty())
	{
		connection->Send(instructions.front());
		instructions.pop();
	}
}
