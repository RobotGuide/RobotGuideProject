#ifndef ROBOTGUIDE_PAHTFINDING_GRID_COORDINATE_H
#define ROBOTGUIDE_PAHTFINDING_GRID_COORDINATE_H



namespace robotguide::path
{
	struct Coordinate
	{
	public:
		Coordinate(int x_, int z_, int y_ = 0);
		Coordinate(const Coordinate& coordinate_);
		virtual ~Coordinate() = default;
		
		int x;
		int y;
		int z;
	};
}

#endif //ROBOTGUIDE_PAHTFINDING_GRID_COORDINATE_H
