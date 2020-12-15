#include "robotguide/Pathfinding/Path/Path.h"
#include <stdexcept>

using namespace robotguide::path;

Path::Path(std::shared_ptr<Vertex> startPoint)
{
	Add(startPoint);
}

void Path::Add(std::shared_ptr<Vertex> newVertex)
{
	if (newVertex.get() == nullptr)
	{
		throw std::invalid_argument("newVertex");
	}

	vertexPath.push_back(newVertex);
}

void Path::RemoveLast(std::shared_ptr<Vertex> vertex)
{
	vertexPath.erase(vertexPath.end());
}

int Path::GetLength() const
{
	return sizeof(vertexPath) / sizeof(std::shared_ptr<Vertex>);
}

const std::vector<std::shared_ptr<Vertex>>& Path::GetVertexes() const
{
	return vertexPath;
}
