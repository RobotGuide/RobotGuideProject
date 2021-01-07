#include "robotguide/Pathfinding/Grid/VertexVector.h"
#include "robotguide/Pathfinding/Grid/Vertex.h"

using namespace robotguide::path;

bool robotguide::path::VertexVector::IsVertexInConnectedVertexes(Vertex* vertex)
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

int robotguide::path::VertexVector::GetVertexIndex(Vertex* vertex)
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

std::vector<Vertex*>::iterator robotguide::path::VertexVector::GetVertexIterator(Vertex* vertex)
{
	return vertices.begin() + GetVertexIndex(vertex);
}

void robotguide::path::VertexVector::Add(Vertex* newVertex)
{
	if (IsVertexInConnectedVertexes(newVertex))
	{
		return;
	}

	vertices.push_back(newVertex);
}

void robotguide::path::VertexVector::Remove(Vertex* vertex)
{
	if (!IsVertexInConnectedVertexes(vertex))
	{
		return;
	}

	vertices.erase(GetVertexIterator(vertex));
}