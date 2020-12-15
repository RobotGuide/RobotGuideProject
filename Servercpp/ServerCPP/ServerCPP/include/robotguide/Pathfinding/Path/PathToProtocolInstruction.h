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
		const int currentAngle_;
	private:
		int GetVerticalDistanceBetweenNextAndCurrentPath(const Vertex& v1, const Vertex& v2) const;
		int GetHorizontalDistanceBetweenNextAndCurrentPath(const Vertex& v1, const Vertex& v2) const;
		int CalculateNeededAngle(const double verticalDistance, const double horizontalDistance) const;
		std::vector<com::al::Instruction*> DetermineInstructionToMoveToDesiredPlace(
			int distanceToMove, int angleToMove) const;

		int GetDistanceViaVerticalAndHorizontalDistance(const double verticalDistance,
		                                                const double horizontalDistance) const;

		std::vector<com::al::Instruction*> GetInstruction(const Vertex& currentVertex, const Vertex& nextVertex) const;
		std::vector<com::al::Instruction*> GetLastInstruction(const Vertex& vertex) const;
		std::vector<com::al::Instruction*> CreateInstruction(const std::vector<std::shared_ptr<Vertex>>& vertexes, const int index) const;
	public:
		PathToProtocolInstruction();
		PathToProtocolInstruction(const int curentAngle);
		~PathToProtocolInstruction() = default;

		com::al::InstructionStream ConvertPathToInstructionStream(const Path& path) const;
	};
}

#endif //ROBOTGUIDE_PAHTFINDING_PATH_PATHTOPROTOCOLINSTRUCTIONS_H
