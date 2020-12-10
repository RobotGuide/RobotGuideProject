#include "robotguide/Pathfinding/Grid/TestGridBuilder.h"
#include "robotguide/Pathfinding/Grid/Vertex.h"
#include "robotguide/Pathfinding/Grid/Coordinate.h"
#include <stdexcept>
#include <memory>
#include <iostream>

//    Z ->
// X .......
// | .##..#.
// v .#.....
//   .......
//   ##...#.
//   .#..###
//   .....#.

robotguide::path::TestGridBuilder::TestGridBuilder()
{

	Coordinate wall1 = Coordinate(1, 1);
	Coordinate wall2 = Coordinate(1, 2);
	Coordinate wall3 = Coordinate(1, 5);
	Coordinate wall4 = Coordinate(2, 1);
	Coordinate wall5 = Coordinate(4, 0);
	Coordinate wall6 = Coordinate(4, 1);
	Coordinate wall7 = Coordinate(4, 5);
	Coordinate wall8 = Coordinate(5, 1);
	Coordinate wall9 = Coordinate(5, 4);
	Coordinate wall10 = Coordinate(5, 5);
	Coordinate wall11 = Coordinate(5, 6);
	Coordinate wall12 = Coordinate(6, 5);

	walls.push_back(wall1);
	walls.push_back(wall2);
	walls.push_back(wall3);
	walls.push_back(wall4);
	walls.push_back(wall5);
	walls.push_back(wall6);
	walls.push_back(wall7);
	walls.push_back(wall8);
	walls.push_back(wall9);
	walls.push_back(wall10);
	walls.push_back(wall11);
	walls.push_back(wall12);
}

robotguide::path::TestGridBuilder::~TestGridBuilder()
{
	walls.clear();
}

void robotguide::path::TestGridBuilder::PopulateGrid(Grid* grid)
{
	if (grid == nullptr)
	{
		throw std::invalid_argument("nullptr was provided as argument");
	}

	//step 1 place down vertexes
	for (int z = 0; z < maxZ; z++)
	{
		for (int x = 0; x < maxX; x++)
		{
			if (IsCoordinateWall(x, z))
			{
				continue;
			}

			Coordinate tileCoord = Coordinate(x, z);

			std::shared_ptr<Vertex> tileVert(new Vertex(tileCoord));

			grid->AddVertex(tileVert);
		}
	}

	//step 2 iterate over vertexes adding connections with neighbours
	for (auto vertex : grid->GetVertexes().vertexes)
	{
		for (auto neighbourVertex : grid->GetVertexes().vertexes)
		{
			if (vertex == neighbourVertex)
			{
				continue;
			}

			if (Coordinate::IsNeighbour(vertex->coordinate, neighbourVertex->coordinate))
			{
				vertex->AddConnectedVertex(neighbourVertex);
			}			
		}
	}
}

bool robotguide::path::TestGridBuilder::IsCoordinateWall(int x, int z)
{
	for (Coordinate wall : walls)
	{
		if (wall.x == x && wall.z == z)
		{
			return true;
		}
	}

	return false;
}

