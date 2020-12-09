#ifndef ROBOTGUIDE_PAHTFINDING_PATH_PATH_H
#define ROBOTGUIDE_PAHTFINDING_PATH_PATH_H

#include "robotguide/Pathfinding/Grid/Vertex.h"
#include <memory>
#include <vector>

namespace robotguide::path 
{
	struct Path
	{
	public:
		std::vector<std::shared_ptr<robotguide::path::Vertex>> vertexPath;

	public:
		Path() = default;
		virtual ~Path() = default;

		void Add(std::shared_ptr<robotguide::path::Vertex> newVertex);
		void RemoveLast(std::shared_ptr<robotguide::path::Vertex> vertex);

		const int GetLength();
	};
}
	
#endif //ROBOTGUIDE_PAHTFINDING_PATH_PATH_H
