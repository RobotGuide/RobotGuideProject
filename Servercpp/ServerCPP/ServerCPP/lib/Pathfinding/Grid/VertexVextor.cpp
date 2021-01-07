#include "robotguide/Pathfinding/Grid/VertexVector.h"
#include "robotguide/Pathfinding/Grid/Vertex.h"

using namespace robotguide::path;

bool VertexVector::IsVertexInConnectedVertexes(Vertex* vertex)
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

int VertexVector::GetVertexIndex(Vertex* vertex)
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

std::vector<Vertex*>::iterator VertexVector::GetVertexIterator(Vertex* vertex)
{
	return vertices.begin() + GetVertexIndex(vertex);
}

void VertexVector::Add(Vertex* newVertex) 
{
	if (IsVertexInConnectedVertexes(newVertex))
	{
		return;
	}

	vertices.push_back(newVertex);
}

void VertexVector::Remove(Vertex* vertex)
{
	if (!IsVertexInConnectedVertexes(vertex))
	{
		return;
	}

	vertices.erase(GetVertexIterator(vertex));
}