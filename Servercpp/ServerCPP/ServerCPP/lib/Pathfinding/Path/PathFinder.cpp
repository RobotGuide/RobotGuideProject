#include "robotguide/Pathfinding/Path/Pathfinder.h"

#include <memory>
#include <stdexcept>
#include <iostream>

robotguide::path::PathFinder::PathFinder(std::shared_ptr<robotguide::path::Grid> grid_)
{
	if (grid_.get() == nullptr)
	{
		throw std::invalid_argument("grid_");
	}

	grid = grid_;
}

robotguide::path::Path robotguide::path::PathFinder::FindPath(std::shared_ptr<robotguide::path::Vertex> startPoint, std::shared_ptr<robotguide::path::Vertex> endPoint)
{
	if (startPoint.get() == nullptr)
	{
		throw std::invalid_argument("startPoint");
	}

	if (endPoint.get() == nullptr)
	{
		throw std::invalid_argument("endPoint");
	}

	if (startPoint == endPoint)
	{
		throw std::invalid_argument("startPoint and endPoint cant be the same vertex");
	}

	bool startPointValid = false;
	bool endPointValid = false;

	for (std::shared_ptr<robotguide::path::Vertex> vertex : grid->GetVertexes().vertexes)
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

	std::vector<robotguide::path::Path> frontier;
	frontier.push_back(Path(startPoint));

	std::vector<robotguide::path::Path> newFrontier;
	std::vector<std::shared_ptr<robotguide::path::Vertex>> finishedVertexes;

	std::cout << "------------------------------" << std::endl;
	for(int i = 1; i < 50; i++)
	{
		std::cout << "> Frontier cycle: " << i << std::endl;
		for (robotguide::path::Path testFrontier : frontier)
		{
			std::cout << "  > New frontier at " << testFrontier.vertexPath.at(testFrontier.vertexPath.size() - 1)->coordinate.x << "," << testFrontier.vertexPath.at(testFrontier.vertexPath.size() - 1)->coordinate.z;
			for (std::shared_ptr<robotguide::path::Vertex> testVertex : testFrontier.vertexPath.back()->connectedVertexes.vertexes)
			{
				std::cout << std::endl << "    > Testing " << testVertex->coordinate.x << "," << testVertex->coordinate.z;
				if (std::find(finishedVertexes.begin(), finishedVertexes.end(), testVertex) != finishedVertexes.end())
				{
					std::cout << "     | Already checked, skipping";
					continue;
				}
				std::cout << " x";

				Path newPath = Path(testFrontier);
				newPath.Add(testVertex);
				finishedVertexes.push_back(testVertex);

				std::cout << "x";
				if (newPath.vertexPath.at(newPath.vertexPath.size() - 1) == endPoint)
				{
					std::cout << "  | Target found!";
					return newPath;
				}

				std::cout << "x";
				newFrontier.push_back(newPath);
				std::cout << " | Not target, added to frontier";
			}
			std::cout << std::endl;
		}

		frontier.clear();
		frontier = newFrontier;
		newFrontier.clear();
		std::cout << std::endl;
	}

	return Path();
}

void temp(std::shared_ptr<robotguide::path::Path> path, std::shared_ptr<robotguide::path::Vertex> targetVertex)
{
	
}

