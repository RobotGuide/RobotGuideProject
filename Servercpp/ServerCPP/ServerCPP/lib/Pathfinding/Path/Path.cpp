#include "robotguide/Pathfinding/Path/Path.h"
#include <stdexcept>

using namespace robotguide::path;

Path::Path(Vertex* startPoint)
{
	Add(startPoint);
}

void Path::Add(Vertex* newVertex)
{
	if (newVertex == nullptr)
	{
		throw std::invalid_argument("newVertex");
	}

	vertexPath.push_back(newVertex);
}

void Path::RemoveLast(Vertex* vertex)
{
	vertexPath.erase(vertexPath.end());
}

int Path::GetLength() const
{
	return vertexPath.size();
}

const std::vector<Vertex*>& Path::GetVertexes() const
{
	return vertexPath;
}
