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
		int currentAngle_;
		int unitSize_;
	private:
		int GetVerticalDistanceBetweenNextAndCurrentPath(const Vertex& source, const Vertex& target);
		int GetHorizontalDistanceBetweenNextAndCurrentPath(const Vertex& source, const Vertex& target);
		int CalculateNeededAngle(const double verticalDistance, const double horizontalDistance);
		std::vector<com::applicationlayer::Instruction*> DetermineInstructionToMoveToDesiredPlace(
			int distanceToMove, int angleToMove);

		int GetDistanceViaVerticalAndHorizontalDistance(const double verticalDistance,
		                                                const double horizontalDistance);

		std::vector<com::applicationlayer::Instruction*> GetInstruction(const Vertex& currentVertex, const Vertex& nextVertex);
		std::vector<com::applicationlayer::Instruction*> GetLastInstruction(const Vertex& vertex);
		std::vector<com::applicationlayer::Instruction*> CreateInstruction(const std::vector<Vertex*>& vertices, const int index);
	public:
		PathToProtocolInstruction();
		PathToProtocolInstruction(const int curentAngle, const int unitSize);
		~PathToProtocolInstruction() = default;

		void ConvertPathToInstructionStream(const Path& path, com::applicationlayer::InstructionStream& instructions);
	};
}

#endif //ROBOTGUIDE_PAHTFINDING_PATH_PATHTOPROTOCOLINSTRUCTIONS_H
