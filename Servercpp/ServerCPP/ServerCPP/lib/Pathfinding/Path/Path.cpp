#include "robotguide/Pathfinding/Path/Path.h"

using namespace robotguide::path;

void robotguide::path::Path::Add(std::shared_ptr<robotguide::grid::Vertex> newVertex)
{
	vertexPath.push_back(newVertex);
}

void robotguide::path::Path::RemoveLast(std::shared_ptr<robotguide::grid::Vertex> vertex)
{
	vertexPath.erase(vertexPath.end());
}

const int robotguide::path::Path::GetLength()
{
	return sizeof(vertexPath) / sizeof(std::shared_ptr<robotguide::grid::Vertex>);
}
