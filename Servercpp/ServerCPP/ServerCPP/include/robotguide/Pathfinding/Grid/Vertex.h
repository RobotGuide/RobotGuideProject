#ifndef ROBOTGUIDE_PAHTFINDING_GRID_VERTEX_H
#define ROBOTGUIDE_PAHTFINDING_GRID_VERTEX_H

#include "robotguide/Pathfinding/Grid/Coordinate.h"
#include "robotguide/Pathfinding/Grid/VertexVector.h"


namespace robotguide::path
{
	class Vertex
	{
	public:
		VertexVector connectedVertexes;
		const Coordinate coordinate;

	public:
		Vertex(const Coordinate& coordinate_);
		virtual ~Vertex();

		void AddConnectedVertex(Vertex* newVertex);
		void RemoveConnectedVertex(Vertex* vertex);
		void RemoveReferencesToSelf();			
	};
}

#endif //ROBOTGUIDE_PAHTFINDING_GRID_VERTEX_H
