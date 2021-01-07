#include "robotguide/Pathfinding/Grid/Coordinate.h"

#include <memory>
#include <iostream>

using namespace robotguide::path;

robotguide::path::Coordinate::Coordinate(int x_, int z_, int y_) : x(x_), z(z_), y(y_)
{
}

bool robotguide::path::Coordinate::IsNeighbour(const Coordinate& coordinate) const
{
	return (abs(x - coordinate.x) + abs(z - coordinate.z)) == 1;
}

bool robotguide::path::Coordinate::IsNeighbour(const Coordinate& c1, const Coordinate& c2)
{	
	return ((abs(c1.x - c2.x) + abs(c1.z - c2.z)) == 1);
}
