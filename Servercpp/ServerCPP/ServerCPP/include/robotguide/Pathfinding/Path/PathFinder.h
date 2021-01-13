#ifndef ROBOTGUIDE_PAHTFINDING_PATH_PATHFINDER_H
#define ROBOTGUIDE_PAHTFINDING_PATH_PATHFINDER_H

#include "robotguide/Pathfinding/Grid/Grid.h"
#include "robotguide/Pathfinding/Path/Path.h"
#include <memory>

namespace robotguide::path
{
	class PathFinder
	{
	private:
		Grid* grid;

	public:
		PathFinder(Grid* grid);
		virtual ~PathFinder() = default;
			
		virtual Path GeneratePath(Vertex* startPoint, Vertex* endPoint);
		virtual Path FindPath(Vertex* startPoint, Vertex* endpoint);
		virtual Path FindPath(int startX, int startY, int endX, int endY);
	};
}

#endif //ROBOTGUIDE_PAHTFINDING_PATH_PATHFINDER_H
