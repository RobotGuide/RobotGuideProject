#include "robotguide/Pathfinding/Path/PathToProtocolInstruction.h"
#include "robotguide/Pathfinding/Grid/Vertex.h"
#include "robotguide/Pathfinding/Path/Path.h"
#include <iostream>
#include <math.h>

robotguide::path::PathToProtocolInstruction::PathToProtocolInstruction() : currentAngle_(0)
{
}

robotguide::path::PathToProtocolInstruction::PathToProtocolInstruction(const int curentAngle) : currentAngle_(curentAngle)
{
}

robotguide::com::al::InstructionStream robotguide::path::PathToProtocolInstruction::ConvertPathToInstructionStream(const Path& path) const
{
	const std::vector<std::shared_ptr<Vertex>>& vertexes = path.GetVertexes();
	com::al::InstructionStream instructions;

	for (auto i = 0; i < vertexes.size(); i++)
	{
		const auto newInstructions = CreateInstruction(vertexes, i);
		for (auto* newInstruction : newInstructions)
		{
			instructions.AddInstruction(newInstruction);
		}
	}
	
	return instructions;
}

std::vector<robotguide::com::al::Instruction*> robotguide::path::PathToProtocolInstruction::CreateInstruction(
	const std::vector<std::shared_ptr<Vertex>>& vertexes, const int index) const
{
	const Vertex* currentVertex = vertexes[index].get();
	if (index != vertexes.size() - 1)
	{
		const Vertex* nextVertex = vertexes[index + 1].get();
		return GetInstruction(*currentVertex, *nextVertex);
	}
	else
	{
		return GetLastInstruction(*currentVertex);
	}
}

int robotguide::path::PathToProtocolInstruction::GetVerticalDistanceBetweenNextAndCurrentPath(const Vertex& v1, const Vertex& v2) const
{
	return v1.coordinate.x - v2.coordinate.x;
}

int robotguide::path::PathToProtocolInstruction::GetHorizontalDistanceBetweenNextAndCurrentPath(const Vertex& v1, const Vertex& v2) const
{
	return v1.coordinate.z - v2.coordinate.z;
}

int robotguide::path::PathToProtocolInstruction::CalculateNeededAngle(const double verticalDistance, const double horizontalDistance) const
{
	return static_cast<int>(atan2(verticalDistance, horizontalDistance)) * 90;
}

std::vector<robotguide::com::al::Instruction*> robotguide::path::PathToProtocolInstruction::GetInstruction(
	const Vertex& currentVertex, const Vertex& nextVertex) const
{
	const int VerticalDistance = GetVerticalDistanceBetweenNextAndCurrentPath(currentVertex, nextVertex);
	const int HorizontalDistance = GetHorizontalDistanceBetweenNextAndCurrentPath(currentVertex, nextVertex);
	const int distanceToMove = GetDistanceViaVerticalAndHorizontalDistance(VerticalDistance, HorizontalDistance);

	const int angleToMove = CalculateNeededAngle(VerticalDistance, HorizontalDistance);
	const int newAngle = currentAngle_ - angleToMove;
	std::cout << distanceToMove << std::endl;

	std::vector<com::al::Instruction*> newInstructions = DetermineInstructionToMoveToDesiredPlace(distanceToMove, angleToMove);
	return newInstructions;
}

std::vector<robotguide::com::al::Instruction*>
robotguide::path::PathToProtocolInstruction::DetermineInstructionToMoveToDesiredPlace(
	const int distanceToMove, const int angleToMove) const
{
	std::vector<com::al::Instruction*> newInstructions;
	if (angleToMove != 0)
	{
		auto* const turnInstruction = new com::al::Instruction(com::al::InstructionType::Turn, { angleToMove });
		newInstructions.push_back(turnInstruction);
	}

	auto* const forwardInstruction = new com::al::Instruction(com::al::InstructionType::Forn, { distanceToMove });
	newInstructions.push_back(forwardInstruction);
	return newInstructions;
}

std::vector<robotguide::com::al::Instruction*> robotguide::path::PathToProtocolInstruction::GetLastInstruction(const Vertex& vertex) const
{
	return {};
}

int robotguide::path::PathToProtocolInstruction::GetDistanceViaVerticalAndHorizontalDistance(
	const double verticalDistance, const double horizontalDistance) const
{
	const auto verticalDistanceSquared = verticalDistance * verticalDistance;
	const auto horizontalDistanceSquared = horizontalDistance * horizontalDistance;
	std::cout << "vertical: " << verticalDistanceSquared << " horizontal: " << horizontalDistanceSquared << std::endl;
	
	return static_cast<int>(sqrt(verticalDistanceSquared + horizontalDistanceSquared));
}