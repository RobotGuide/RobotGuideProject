#include "robotguide/Pathfinding/Path/PathToProtocolInstruction.h"
#include "robotguide/Pathfinding/Grid/Vertex.h"
#include "robotguide/Pathfinding/Path/Path.h"
#include <iostream>
#include <math.h>
#include <random>

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

int robotguide::path::PathToProtocolInstruction::GetCurrentAngle() const
{
	return currentAngle_;
}

int robotguide::path::PathToProtocolInstruction::GetNodeSize() const
{
	return unitSize_;
}

void robotguide::path::PathToProtocolInstruction::SetNodeSize(int nodeSize)
{
	unitSize_ = nodeSize;
}

void robotguide::path::PathToProtocolInstruction::SetCurrentAngle(int currentAngle)
{
	currentAngle_ = currentAngle;
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
		return {};
	}
}

int robotguide::path::PathToProtocolInstruction::ConvertNegativeAngleToPositiveAngle(const int angle)
{
	if (angle >= 0)
	{
		return angle;
	}

	return (angle + 360) % 360;
}

int robotguide::path::PathToProtocolInstruction::ConvertPositiveAngleToNegativeAngle(const int angle)
{
	if (angle <= 0)
	{
		return angle;
	}

	return (angle - 360) % 360;
}

int robotguide::path::PathToProtocolInstruction::GetClosestTurn(const int angle)
{
	const int positiveAngleVariant = ConvertNegativeAngleToPositiveAngle(angle);
	const int negativeAngleVariant = ConvertPositiveAngleToNegativeAngle(angle);

	if (std::abs(positiveAngleVariant) < std::abs(negativeAngleVariant))
	{
		return positiveAngleVariant;
	}
	else
	{
		return negativeAngleVariant;
	}
}

int robotguide::path::PathToProtocolInstruction::GetVerticalDistanceBetweenNextAndCurrentPath(const Vertex& source, const Vertex& target) const
{
	return target.coordinate.z - source.coordinate.z;
}

int robotguide::path::PathToProtocolInstruction::GetHorizontalDistanceBetweenNextAndCurrentPath(const Vertex& source, const Vertex& target) const
{
	return target.coordinate.x - source.coordinate.x;
}

int robotguide::path::PathToProtocolInstruction::CalculateNeededAngle(const double verticalDistance, const double horizontalDistance) const
{
	/*
	 * This returns:
	 * right: 0
	 * up: 90
	 * left: 180/-180
	 * down: -90
	 *
	 * Using vertical and horizontal movement
	 */
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
	const int angleToMoveCorrected = GetClosestTurn(angleToMove);
	
	std::vector<com::applicationlayer::Instruction*> newInstructions;
	if (angleToMove % 360 != 0)
	{
		auto* const turnInstruction = new com::applicationlayer::Instruction(com::applicationlayer::InstructionType::Turn, { angleToMoveCorrected });
		newInstructions.push_back(turnInstruction);
	}

	auto* const forwardInstruction = new com::applicationlayer::Instruction(com::applicationlayer::InstructionType::Forn, { distanceToMove * unitSize_ });
	newInstructions.push_back(forwardInstruction);
	return newInstructions;
}

int robotguide::path::PathToProtocolInstruction::GetDistanceViaVerticalAndHorizontalDistance(
	const double verticalDistance, const double horizontalDistance)
{
	const auto verticalDistanceSquared = verticalDistance * verticalDistance;
	const auto horizontalDistanceSquared = horizontalDistance * horizontalDistance;
	
	return static_cast<int>(sqrt(verticalDistanceSquared + horizontalDistanceSquared));
}