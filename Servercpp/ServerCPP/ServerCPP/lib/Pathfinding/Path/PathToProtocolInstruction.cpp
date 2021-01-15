#include "robotguide/Pathfinding/Path/PathToProtocolInstruction.h"
#include "robotguide/Pathfinding/Grid/Vertex.h"
#include "robotguide/Pathfinding/Path/Path.h"
#include <iostream>
#include <math.h>
#include <random>

robotguide::path::PathToProtocolInstruction::PathToProtocolInstruction() : currentAngle_(0), unitSize_(1)
{
}

robotguide::path::PathToProtocolInstruction::PathToProtocolInstruction(const int curentAngle, const int unitSize) : currentAngle_(curentAngle), unitSize_(unitSize)
{
}

void robotguide::path::PathToProtocolInstruction::ConvertPathToInstructionStream(const Path& path, com::applicationlayer::InstructionStream& instructions)
{
	const std::vector<Vertex*>& vertices = path.GetVertexes();

	for (auto i = 0; i < vertices.size(); i++)
	{
		const auto newInstructions = CreateInstruction(vertices, i);
		for (auto* newInstruction : newInstructions)
		{
			instructions.AddInstruction(newInstruction);
		}
	}
}

std::vector<robotguide::com::applicationlayer::Instruction*> robotguide::path::PathToProtocolInstruction::CreateInstruction(
	const std::vector<Vertex*>& vertices, const int index)
{
	const Vertex* currentVertex = vertices[index];
	if (index != vertices.size() - 1)
	{
		const Vertex* nextVertex = vertices[index + 1];
		return GetInstruction(*currentVertex, *nextVertex);
	}
	else
	{
		return GetLastInstruction(*currentVertex);
	}
}

int robotguide::path::PathToProtocolInstruction::GetVerticalDistanceBetweenNextAndCurrentPath(const Vertex& source, const Vertex& target)
{
	return target.coordinate.z - source.coordinate.z;
}

int robotguide::path::PathToProtocolInstruction::GetHorizontalDistanceBetweenNextAndCurrentPath(const Vertex& source, const Vertex& target)
{
	return target.coordinate.x - source.coordinate.x;
}

int robotguide::path::PathToProtocolInstruction::CalculateNeededAngle(const double verticalDistance, const double horizontalDistance)
{
	return static_cast<int>(atan2(-verticalDistance, horizontalDistance) / std::_Pi * 180);
}

std::vector<robotguide::com::applicationlayer::Instruction*> robotguide::path::PathToProtocolInstruction::GetInstruction(
	const Vertex& currentVertex, const Vertex& nextVertex)
{
	const int VerticalDistance = GetVerticalDistanceBetweenNextAndCurrentPath(currentVertex, nextVertex);
	const int HorizontalDistance = GetHorizontalDistanceBetweenNextAndCurrentPath(currentVertex, nextVertex);

	const int distanceToMove = GetDistanceViaVerticalAndHorizontalDistance(VerticalDistance, HorizontalDistance);
	const int angleToMove = CalculateNeededAngle(VerticalDistance, HorizontalDistance);

	const int newAngle = angleToMove - currentAngle_;

	std::vector<com::applicationlayer::Instruction*> newInstructions = DetermineInstructionToMoveToDesiredPlace(distanceToMove, newAngle);
	currentAngle_ = angleToMove;
	return newInstructions;
}

std::vector<robotguide::com::applicationlayer::Instruction*>
robotguide::path::PathToProtocolInstruction::DetermineInstructionToMoveToDesiredPlace(
	const int distanceToMove, const int angleToMove)
{
	std::vector<com::applicationlayer::Instruction*> newInstructions;
	if (angleToMove % 360 != 0)
	{
		auto* const turnInstruction = new com::applicationlayer::Instruction(com::applicationlayer::InstructionType::Turn, { angleToMove });
		newInstructions.push_back(turnInstruction);
	}

	auto* const forwardInstruction = new com::applicationlayer::Instruction(com::applicationlayer::InstructionType::Forn, { distanceToMove * unitSize_ });
	newInstructions.push_back(forwardInstruction);
	return newInstructions;
}

std::vector<robotguide::com::applicationlayer::Instruction*> robotguide::path::PathToProtocolInstruction::GetLastInstruction(const Vertex& vertex)
{
	return {};
}

int robotguide::path::PathToProtocolInstruction::GetDistanceViaVerticalAndHorizontalDistance(
	const double verticalDistance, const double horizontalDistance)
{
	const auto verticalDistanceSquared = verticalDistance * verticalDistance;
	const auto horizontalDistanceSquared = horizontalDistance * horizontalDistance;
	
	return static_cast<int>(sqrt(verticalDistanceSquared + horizontalDistanceSquared));
}