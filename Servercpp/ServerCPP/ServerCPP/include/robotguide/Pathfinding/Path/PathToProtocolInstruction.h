#ifndef ROBOTGUIDE_PAHTFINDING_PATH_PATHTOPROTOCOLINSTRUCTIONS_H
#define ROBOTGUIDE_PAHTFINDING_PATH_PATHTOPROTOCOLINSTRUCTIONS_H

#include "robotguide/Communication/ApplicationLayer/Instruction/InstructionStream.h"
#include "robotguide/Pathfinding/Grid/Vertex.h"

namespace robotguide::path
{
	struct Path;

	class PathToProtocolInstruction final
	{
	private:
		int currentAngle_ = 0;
		int unitSize_ = 1;
	private:
		int GetVerticalDistanceBetweenNextAndCurrentPath(const Vertex& source, const Vertex& target) const;
		int GetHorizontalDistanceBetweenNextAndCurrentPath(const Vertex& source, const Vertex& target) const;
		int CalculateNeededAngle(const double verticalDistance, const double horizontalDistance) const;
		std::vector<com::applicationlayer::Instruction*> DetermineInstructionToMoveToDesiredPlace(
			int distanceToMove, int angleToMove);

		int GetDistanceViaVerticalAndHorizontalDistance(const double verticalDistance,
		                                                const double horizontalDistance);

		std::vector<com::applicationlayer::Instruction*> GetInstruction(const Vertex& currentVertex, const Vertex& nextVertex);
		
		std::vector<com::applicationlayer::Instruction*> CreateInstruction(const std::vector<Vertex*>& vertices, const int index);

		int ConvertNegativeAngleToPositiveAngle(const int angle);
		int ConvertPositiveAngleToNegativeAngle(const int angle);

		// Checks whether an inside turn is smaller than outside turn
		// Returns: smallest turn
		int GetClosestTurn(const int angle);
		
	public:
		PathToProtocolInstruction() = default;
		PathToProtocolInstruction(const int curentAngle, const int unitSize);
		~PathToProtocolInstruction() = default;

		void ConvertPathToInstructionStream(const Path& path, com::applicationlayer::InstructionStream& instructions);
		int GetCurrentAngle() const; // the angle is either: 0, 90, -90, or 180.
		int GetNodeSize() const;

		void SetNodeSize(int nodeSize);
		void SetCurrentAngle(int currentAngle);
	};
}

#endif //ROBOTGUIDE_PAHTFINDING_PATH_PATHTOPROTOCOLINSTRUCTIONS_H
