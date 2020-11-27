#ifndef ROBOTGUIDE_PAHTFINDING_GRID_VERTEXVECTOR_H
#define ROBOTGUIDE_PAHTFINDING_GRID_VERTEXVECTOR_H

#include <vector>
#include <memory>


namespace robotguide::path
{
	class Vertex;
	class VertexVector 
	{
	public:
		std::vector<std::shared_ptr<Vertex>> vertexes;
		
	public:
		VertexVector() = default;
		virtual ~VertexVector() = default;
		bool IsVertexInConnectedVertexes(std::shared_ptr<Vertex> vertex);
		int GetVertexIndex(std::shared_ptr<Vertex> vertex);
		std::vector<std::shared_ptr<Vertex>>::iterator GetVertexIterator(std::shared_ptr<Vertex> vertex);

		void Add(std::shared_ptr<Vertex> newVertex);
		void Remove(std::shared_ptr<Vertex> vertex);
	};
}

#endif //ROBOTGUIDE_PAHTFINDING_GRID_VERTEXVECTOR_H

