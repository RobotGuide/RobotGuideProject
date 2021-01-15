#include "robotguide/Pathfinding/Path/Pathfinder.h"

#include <memory>
#include <stdexcept>
#include <iostream>
#include <windows.h>

#include "robotguide/Communication/Exception/Pathfinding/InvalidRouteException.h"

using namespace robotguide::path;

robotguide::path::PathFinder::PathFinder(Grid* grid_)
{
	if (grid_ == nullptr)
	{
		throw std::invalid_argument("grid_");
	}

	grid = grid_;
}

Path robotguide::path::PathFinder::FindPath(Vertex* startPoint, Vertex* endPoint)
{
	return GeneratePath(startPoint, endPoint);
}

Path robotguide::path::PathFinder::FindPath(int startX, int startZ, int endX, int endZ)
{
	Vertex* startVertex = grid->GetVertexByCoords(startX, startZ);
	Vertex* endVertex = grid->GetVertexByCoords(endX, endZ);

	if (startVertex == nullptr || endVertex == nullptr)
	{
		throw com::exception::InvalidRouteException("Couldn't find path between given vertexes!");
	}

	return GeneratePath(startVertex, endVertex);
}

Path robotguide::path::PathFinder::GeneratePath(Vertex* startPoint, Vertex* endPoint)
{
	if (startPoint == nullptr)
	{
		throw com::exception::InvalidRouteException("The start point was either invalid or an invalid coordinate class was used");
	}

	if (endPoint == nullptr)
	{
		throw com::exception::InvalidRouteException("The end point was either invalid or an invalid coordinate class was used");

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

	std::vector<Path> frontier;
	frontier.push_back(Path(startPoint));

	std::vector<Path> newFrontier;
	std::vector<Vertex*> finishedVertexes;

	for(int i = 0; i < grid->GetVertexes().vertices.size(); i++)
	{
		for (Path testFrontier : frontier)
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
	throw com::exception::InvalidRouteException("Couldn't find path between given vertexes!");
}

