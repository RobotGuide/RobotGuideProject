#include "robotguide/Pathfinding/Path/Path.h"
#include <stdexcept>

using namespace robotguide::path;

robotguide::path::Path::Path(std::shared_ptr<robotguide::path::Vertex> startPoint)
{
	Add(startPoint);
}

void robotguide::path::Path::Add(std::shared_ptr<robotguide::path::Vertex> newVertex)
{
	if (newVertex.get() == nullptr)
	{
		throw std::invalid_argument("newVertex");
	}

	vertexPath.push_back(newVertex);
}

void robotguide::path::Path::RemoveLast(std::shared_ptr<robotguide::path::Vertex> vertex)
{
	vertexPath.erase(vertexPath.end());
}

int robotguide::path::Path::GetLength() const
{
	return sizeof(vertexPath) / sizeof(std::shared_ptr<robotguide::path::Vertex>);
}
