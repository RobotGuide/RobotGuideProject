#include "robotguide/Pathfinding/Grid/Grid.h"
#include "robotguide/Pathfinding/Grid/Vertex.h"

void robotguide::path::Grid::AddVertex(std::shared_ptr<robotguide::path::Vertex> newVertex)
{
	vertexes.Add(newVertex);
}

void robotguide::path::Grid::RemoveVertex(std::shared_ptr<robotguide::path::Vertex> vertex)
{
	vertexes.Remove(vertex);
}

void robotguide::path::Grid::AddConnection(std::shared_ptr<Vertex> startVertex, std::shared_ptr<Vertex> targetVertex)
{
	startVertex->AddConnectedVertex(targetVertex);
	targetVertex->AddConnectedVertex(startVertex);
}

void robotguide::path::Grid::RemoveConnection(std::shared_ptr<Vertex> startVertex, std::shared_ptr<Vertex> targetVertex)
{
	startVertex->RemoveConnectedVertex(targetVertex);
	targetVertex->RemoveConnectedVertex(startVertex);
}

const robotguide::path::VertexVector& robotguide::path::Grid::GetVertexes() const
{
	return vertexes;
}
