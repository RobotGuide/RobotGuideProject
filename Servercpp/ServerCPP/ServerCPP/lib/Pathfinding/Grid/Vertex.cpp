#include "robotguide/Pathfinding/Grid/Vertex.h"

using namespace robotguide::path;

Vertex::Vertex(const Coordinate& coordinate_) : coordinate(coordinate_)
{
}

Vertex::~Vertex()
{
	RemoveReferencesToSelf();
}

void Vertex::AddConnectedVertex(std::shared_ptr<Vertex> newVertex)
{
	connectedVertexes.Add(newVertex);
}

void Vertex::RemoveConnectedVertex(std::shared_ptr<Vertex> vertex)
{
	connectedVertexes.Remove(vertex);
}

void Vertex::RemoveReferencesToSelf()
{
	for (auto vertex : connectedVertexes.vertices)
	{
		vertex->RemoveConnectedVertex(std::shared_ptr<Vertex>(this));
	}
}


