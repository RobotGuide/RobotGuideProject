#ifndef ROBOTGUIDE_PAHTFINDING_PATH_PATHFINDER_H
#define ROBOTGUIDE_PAHTFINDING_PATH_PATHFINDER_H

#include "robotguide/Pathfinding/Grid/Grid.h"
#include "robotguide/Pathfinding/Path/Path.h"
#include <memory>

namespace robotguide::path
{
	class PathFinder
	{
	public:
		PathFinder(std::shared_ptr<robotguide::path::Grid> grid);
		virtual ~PathFinder() = default;

		virtual Path FindPath(std::shared_ptr<robotguide::path::Vertex> startPoint, 
								std::shared_ptr<robotguide::path::Vertex> endPoint);
	};
}

#endif //ROBOTGUIDE_PAHTFINDING_PATH_PATHFINDER_H
