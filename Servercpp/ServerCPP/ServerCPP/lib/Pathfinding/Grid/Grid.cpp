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
