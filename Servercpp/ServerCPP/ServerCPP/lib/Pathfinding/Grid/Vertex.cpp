#include "robotguide/Pathfinding/Grid/Vertex.h"

using namespace robotguide::path;

robotguide::path::Vertex::Vertex(const Coordinate& coordinate_) : coordinate(coordinate_)
{
}

robotguide::path::Vertex::~Vertex()
{
	RemoveReferencesToSelf();
}

void robotguide::path::Vertex::AddConnectedVertex(Vertex* newVertex)
{
	connectedVertexes.Add(newVertex);
}

void robotguide::path::Vertex::RemoveConnectedVertex(Vertex* vertex)
{
	connectedVertexes.Remove(vertex);
}

void robotguide::path::Vertex::RemoveReferencesToSelf()
{
	for (auto vertex : connectedVertexes.vertices)
	{
		vertex->RemoveConnectedVertex(this);
	}
}


