#ifndef ROBOTGUIDE_PAHTFINDING_GRID_GRID_H
#define ROBOTGUIDE_PAHTFINDING_GRID_GRID_H

#include "robotguide/Pathfinding/Grid/VertexVector.h"


namespace robotguide::path 
{
	class Vertex;
	class Grid
	{
	private:
		VertexVector vertexes;

	public:
		Grid() = default;
		virtual ~Grid() = default;

		void AddVertex(std::shared_ptr <Vertex> newVertex);
		void RemoveVertex(std::shared_ptr<Vertex> vertex);

		void AddConnection(std::shared_ptr<Vertex> startVertex, std::shared_ptr<Vertex> targetVertex);
		void RemoveConnection(std::shared_ptr<Vertex> startVertex, std::shared_ptr<Vertex> targetVertex);

		const VertexVector& GetVertexes() const;
	};
}

#endif //ROBOTGUIDE_PAHTFINDING_GRID_GRID_H
