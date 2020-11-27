#ifndef ROBOTGUIDE_PAHTFINDING_GRID_VERTEX_H
#define ROBOTGUIDE_PAHTFINDING_GRID_VERTEX_H

#include "robotguide/Pathfinding/Grid/Coordinate.h"
#include "robotguide/Pathfinding/Grid/VertexType.h"
#include "robotguide/Pathfinding/Grid/VertexVector.h"


namespace robotguide::path
{
	class Vertex
	{
	public:
		VertexVector connectedVertexes;
		bool isOccupied = false;
		const VertexType vertexType = VertexType::Standard;
		const Coordinate coordinate;

	public:
		Vertex(const Coordinate& coordinate_);
		Vertex(const Coordinate& coordinate_, const VertexType vertexType_);
		virtual ~Vertex();

		void AddConnectedVertex(std::shared_ptr<Vertex> newVertex);
		void RemoveConnectedVertex(std::shared_ptr<Vertex> vertex);
		void RemoveReferencesToSelf();			
	};
}

#endif //ROBOTGUIDE_PAHTFINDING_GRID_VERTEX_H
