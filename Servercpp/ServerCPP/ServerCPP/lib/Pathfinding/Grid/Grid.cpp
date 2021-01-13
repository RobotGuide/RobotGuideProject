#include "robotguide/Pathfinding/Grid/Grid.h"
#include "robotguide/Pathfinding/Grid/Vertex.h"

using namespace robotguide::path;

robotguide::path::Grid::~Grid()
{
	for (int i = 0; i < vertices.vertices.size(); i++)
	{
		delete vertices.vertices[i];
	}
}

Vertex* robotguide::path::Grid::GetVertexByCoords(int x, int z) 
{
	for (Vertex* vertex : vertices.vertices)
	{
		if (vertex->coordinate.x == x && vertex->coordinate.z == z)
		{
			return vertex;
		}		
	}
	return nullptr;
}

void robotguide::path::Grid::AddVertex(Vertex* newVertex)
{
	vertices.Add(newVertex);
}

void robotguide::path::Grid::RemoveVertex(Vertex* vertex)
{
	vertices.Remove(vertex);
}

void robotguide::path::Grid::AddConnection(Vertex* startVertex, Vertex* targetVertex)
{
	startVertex->AddConnectedVertex(targetVertex);
	targetVertex->AddConnectedVertex(startVertex);
}

void robotguide::path::Grid::RemoveConnection(Vertex* startVertex, Vertex* targetVertex)
{
	startVertex->RemoveConnectedVertex(targetVertex);
	targetVertex->RemoveConnectedVertex(startVertex);
}

const VertexVector& robotguide::path::Grid::GetVertexes() const
{
	return vertices;
}
