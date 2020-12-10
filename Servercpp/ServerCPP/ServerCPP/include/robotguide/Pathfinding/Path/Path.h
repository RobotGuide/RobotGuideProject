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
		bool completed = false;

	public:
		Path() = default;
		Path(std::shared_ptr<robotguide::path::Vertex> startPoint);
		virtual ~Path() = default;

		void Add(std::shared_ptr<robotguide::path::Vertex> newVertex);
		void RemoveLast(std::shared_ptr<robotguide::path::Vertex> vertex);

		int GetLength() const;
	};
}
	
#endif //ROBOTGUIDE_PAHTFINDING_PATH_PATH_H
