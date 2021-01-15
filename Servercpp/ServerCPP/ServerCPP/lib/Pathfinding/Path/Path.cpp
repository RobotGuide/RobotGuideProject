#include "robotguide/Pathfinding/Path/Path.h"
#include <stdexcept>

using namespace robotguide::path;

robotguide::path::Path::Path(Vertex* startPoint)
{
	Add(startPoint);
}

Path::Path(std::vector<Vertex*> vertexPath_)
{
	vertexPath = vertexPath_;
}

void robotguide::path::Path::Add(Vertex* newVertex)
{
	if (newVertex == nullptr)
	{
		throw std::invalid_argument("newVertex");
	}

	vertexPath.push_back(newVertex);
}

void robotguide::path::Path::RemoveLast(Vertex* vertex)
{
	vertexPath.erase(vertexPath.end());
}

int robotguide::path::Path::GetLength() const
{
	return vertexPath.size();
}

const std::vector<Vertex*>& robotguide::path::Path::GetVertexes() const
{
	return vertexPath;
}
