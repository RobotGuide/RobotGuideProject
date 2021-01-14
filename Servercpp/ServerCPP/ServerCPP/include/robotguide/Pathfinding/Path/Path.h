#ifndef ROBOTGUIDE_PAHTFINDING_PATH_PATH_H
#define ROBOTGUIDE_PAHTFINDING_PATH_PATH_H

#include "robotguide/Pathfinding/Grid/Vertex.h"
#include <memory>
#include <vector>

namespace robotguide::path 
{
	struct Path
	{
		std::vector<Vertex*> vertexPath;		

	public:
		Path() = default;
		Path(Vertex* startPoint);
		virtual ~Path() = default;

		void Add(Vertex* newVertex);
		void RemoveLast(Vertex* vertex);

		int GetLength() const;

		const std::vector<Vertex*>& GetVertexes() const;
	};
}
	
#endif //ROBOTGUIDE_PAHTFINDING_PATH_PATH_H
