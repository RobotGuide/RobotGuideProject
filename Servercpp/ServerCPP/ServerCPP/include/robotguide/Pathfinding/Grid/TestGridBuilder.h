#ifndef ROBOTGUIDE_PATHFINDING_GRID_TEST_BUILDER_H
#define ROBOTGUIDE_PATHFINDING_GRID_TEST_BUILDER_H

#include "robotguide/Pathfinding/Grid/Grid.h"
#include "robotguide/Pathfinding/Grid/Coordinate.h"
#include <vector>
#include <memory>

namespace robotguide::path
{
	class TestGridBuilder
	{
	private:
		const int maxZ = 7;
		const int maxX = 7;
		std::vector<Coordinate> walls;

		bool IsCoordinateWall(int x, int z);
		bool AreNeighBours(std::shared_ptr<Vertex> v1, std::shared_ptr<Vertex> v2);

	public:
		TestGridBuilder();
		~TestGridBuilder();

		void PopulateGrid(Grid* grid);
	};
}

#endif //ROBOTGUIDE_PATHFINDING_GRID_TEST_BUILDER_H