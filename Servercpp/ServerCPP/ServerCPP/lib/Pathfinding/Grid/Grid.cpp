#include "robotguide/Pathfinding/Grid/Grid.h"
#include "robotguide/Pathfinding/Grid/Vertex.h"

using namespace robotguide::path;

Grid::~Grid() 
{
	for (int i = 0; i < vertices.vertices.size(); i++)
	{
		delete vertices.vertices[i];
	}
}

void Grid::AddVertex(Vertex* newVertex)
{
	vertices.Add(newVertex);
}

void Grid::RemoveVertex(Vertex* vertex)
{
	vertices.Remove(vertex);
}

void Grid::AddConnection(Vertex* startVertex, Vertex* targetVertex)
{
	startVertex->AddConnectedVertex(targetVertex);
	targetVertex->AddConnectedVertex(startVertex);
}

void Grid::RemoveConnection(Vertex* startVertex, Vertex* targetVertex)
{
	startVertex->RemoveConnectedVertex(targetVertex);
	targetVertex->RemoveConnectedVertex(startVertex);
}

const VertexVector& Grid::GetVertexes() const
{
	return vertices;
}
