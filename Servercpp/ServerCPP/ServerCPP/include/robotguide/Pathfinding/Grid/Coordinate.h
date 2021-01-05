#ifndef ROBOTGUIDE_PAHTFINDING_GRID_COORDINATE_H
#define ROBOTGUIDE_PAHTFINDING_GRID_COORDINATE_H



namespace robotguide::path
{
	struct Coordinate
	{
		int x;
		int y;
		int z;

	public:
		Coordinate(int x_, int z_, int y_ = 0);
		virtual ~Coordinate() = default;

		bool IsNeighbour(const Coordinate& coordinate) const;
		static bool IsNeighbour(const Coordinate& c1, const Coordinate& c2);
	};
}

#endif //ROBOTGUIDE_PAHTFINDING_GRID_COORDINATE_H
