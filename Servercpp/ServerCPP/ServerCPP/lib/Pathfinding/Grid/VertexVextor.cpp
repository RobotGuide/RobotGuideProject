#include "robotguide/Pathfinding/Grid/VertexVector.h"
#include "robotguide/Pathfinding/Grid/Vertex.h"

using namespace robotguide::path;

bool VertexVector::IsVertexInConnectedVertexes(std::shared_ptr<Vertex> vertex)
{
	for (auto tempVertex : vertices)
	{
		if (tempVertex == vertex)
		{
			return true;
		}
	}
	return false;
}

int VertexVector::GetVertexIndex(std::shared_ptr<Vertex> vertex)
{
	int resultIndex = 0;

	for (auto tempVertex : vertices)
	{
		if (tempVertex == vertex)
		{
			return resultIndex;
		}
		resultIndex++;
	}
	return -1;
}

std::vector<std::shared_ptr<Vertex>>::iterator VertexVector::GetVertexIterator(std::shared_ptr<Vertex> vertex)
{
	return vertices.begin() + GetVertexIndex(vertex);
}

void VertexVector::Add(std::shared_ptr<Vertex> newVertex) 
{
	if (IsVertexInConnectedVertexes(newVertex))
	{
		return;
	}

	vertices.push_back(newVertex);
}

void VertexVector::Remove(std::shared_ptr<Vertex> vertex)
{
	if (!IsVertexInConnectedVertexes(vertex))
	{
		return;
	}

	vertices.erase(GetVertexIterator(vertex));
}