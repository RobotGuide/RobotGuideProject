#include "robotguide/Pathfinding/Grid/Grid.h"
#include "robotguide/Pathfinding/Grid/Vertex.h"

using namespace robotguide::path;

void Grid::AddVertex(std::shared_ptr<Vertex> newVertex)
{
	vertices.Add(newVertex);
}

void Grid::RemoveVertex(std::shared_ptr<Vertex> vertex)
{
	vertices.Remove(vertex);
}

void Grid::AddConnection(std::shared_ptr<Vertex> startVertex, std::shared_ptr<Vertex> targetVertex)
{
	startVertex->AddConnectedVertex(targetVertex);
	targetVertex->AddConnectedVertex(startVertex);
}

void Grid::RemoveConnection(std::shared_ptr<Vertex> startVertex, std::shared_ptr<Vertex> targetVertex)
{
	startVertex->RemoveConnectedVertex(targetVertex);
	targetVertex->RemoveConnectedVertex(startVertex);
}

const VertexVector& Grid::GetVertexes() const
{
	return vertices;
}
