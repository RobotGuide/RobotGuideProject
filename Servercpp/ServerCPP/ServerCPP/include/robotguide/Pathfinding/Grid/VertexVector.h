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
		std::vector<Vertex*> vertices;
		
	public:
		VertexVector() = default;
		virtual ~VertexVector() = default;
		bool IsVertexInConnectedVertexes(Vertex* vertex);
		int GetVertexIndex(Vertex* vertex);
		std::vector<Vertex*>::iterator GetVertexIterator(Vertex* vertex);

		void Add(Vertex* newVertex);
		void Remove(Vertex* vertex);
	};
}
#endif //ROBOTGUIDE_PAHTFINDING_GRID_VERTEXVECTOR_H

