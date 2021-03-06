#ifndef ROBOTGUIDE_PAHTFINDING_GRID_GRID_H
#define ROBOTGUIDE_PAHTFINDING_GRID_GRID_H

#include "Coordinate.h"
#include "robotguide/Pathfinding/Grid/VertexVector.h"


namespace robotguide::path 
{
	class Vertex;
	class Grid
	{
	private:
		VertexVector vertices;

	public:
		Grid() = default;
		virtual ~Grid();

		Grid(const Grid&) = delete;
		Grid& operator=(const Grid&) = delete;

		void AddVertex(Vertex* newVertex);
		void RemoveVertex(Vertex* vertex);

		void AddConnection(Vertex* startVertex, Vertex* targetVertex);
		void RemoveConnection(Vertex* startVertex, Vertex* targetVertex);

		Vertex* GetVertexByCoords(int x, int z);
		Vertex* GetVertexByCoords(const Coordinate& coordinate);
		
		bool DoesCoordExist(int x, int z);
		bool DoesCoordExist(const Coordinate& coordinate);

		const VertexVector& GetVertexes() const;
	};
}

#endif //ROBOTGUIDE_PAHTFINDING_GRID_GRID_H
