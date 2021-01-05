#ifndef ROBOTGUIDE_PAHTFINDING_PATH_PATH_H
#define ROBOTGUIDE_PAHTFINDING_PATH_PATH_H

#include "robotguide/Pathfinding/Grid/Vertex.h"
#include <memory>
#include <vector>

namespace robotguide::path 
{
	struct Path
	{
		std::vector<std::shared_ptr<Vertex>> vertexPath;		

	public:
		Path() = default;
		Path(std::shared_ptr<Vertex> startPoint);
		virtual ~Path() = default;

		void Add(std::shared_ptr<Vertex> newVertex);
		void RemoveLast(std::shared_ptr<Vertex> vertex);

		int GetLength() const;

		const std::vector<std::shared_ptr<Vertex>>& GetVertexes() const;
	};
}
	
#endif //ROBOTGUIDE_PAHTFINDING_PATH_PATH_H
