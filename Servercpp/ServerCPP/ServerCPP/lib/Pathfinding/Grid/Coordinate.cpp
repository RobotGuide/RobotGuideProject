#include "robotguide/Pathfinding/Grid/Coordinate.h"

using namespace robotguide::path;

Coordinate::Coordinate(int x_, int z_, int y_)
{
	x = x_;	
	z = z_;
	y = y_;
}

Coordinate::Coordinate(const Coordinate& coordinate_)
{
	x = coordinate_.x;
	z = coordinate_.z;
	y = coordinate_.y;
}