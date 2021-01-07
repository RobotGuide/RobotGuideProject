#include "robotguide/Pathfinding/Path/Pathfinder.h"

#include <memory>
#include <stdexcept>
#include <iostream>
#include <windows.h>

using namespace robotguide::path;

robotguide::path::PathFinder::PathFinder(Grid* grid_)
{
	if (grid_ == nullptr)
	{
		throw std::invalid_argument("grid_");
	}

	grid = grid_;
}

robotguide::path::Path robotguide::path::PathFinder::FindPath(Vertex* startPoint, Vertex* endPoint)
{
	if (startPoint == nullptr)
	{
		throw std::invalid_argument("startPoint");
	}

	if (endPoint == nullptr)
	{
		throw std::invalid_argument("endPoint");
	}	

	bool startPointValid = false;
	bool endPointValid = false;

	for (Vertex* vertex : grid->GetVertexes().vertices)
	{
		if (vertex == startPoint)
		{
			startPointValid = true;
		}

		if (vertex == endPoint)
		{
			endPointValid = true;
		}
	}

	if (!startPointValid)
	{
		throw std::invalid_argument("startPoint");
	}

	if (!endPointValid)
	{
		throw std::invalid_argument("endPoint");
	}

	if (startPoint == endPoint)
	{
		return {};
	}

	std::vector<robotguide::path::Path> frontier;
	frontier.push_back(Path(startPoint));

	std::vector<robotguide::path::Path> newFrontier;
	std::vector<Vertex*> finishedVertexes;

	for(int i = 0; i < grid->GetVertexes().vertices.size(); i++)
	{
		for (robotguide::path::Path testFrontier : frontier)
		{
			for (Vertex* testVertex : testFrontier.vertexPath.back()->connectedVertexes.vertices)
			{				
				if (std::find(finishedVertexes.begin(), finishedVertexes.end(), testVertex) != finishedVertexes.end())
				{					
					continue;
				}				

				Path newPath = Path(testFrontier);
				newPath.Add(testVertex);
				finishedVertexes.push_back(testVertex);
				
				if (newPath.vertexPath.at(newPath.vertexPath.size() - 1) == endPoint)
				{					
					return newPath;
				}				
				newFrontier.push_back(newPath);				
			}
		}
		frontier.clear();
		frontier = newFrontier;
		newFrontier.clear();
	}
	throw new std::runtime_error("Could not find path between start- and endpoint");
}

