#include "pch.h"
#include "robotguide/Pathfinding/Grid/TestGridBuilder.h"
#include "robotguide/Pathfinding/Path/PathFinder.h"

#include <iostream>
#include <random>
#include <time.h>

#include <chrono>
#include <ctime>

int main()
{
	robotguide::path::Grid grid;
	robotguide::path::TestGridBuilder* gridBuilder = new robotguide::path::TestGridBuilder();
	gridBuilder->PopulateGrid(&grid);

	robotguide::path::PathFinder pathFinder = robotguide::path::PathFinder(std::make_shared<robotguide::path::Grid>(grid));
	
	std::cout << grid.GetVertexes().vertices.size() << " vertices in grid" << std::endl;

	srand(time(NULL));
	int startVertex = rand() % (grid.GetVertexes().vertices.size() - 1);
	int targetVertex = rand() % (grid.GetVertexes().vertices.size() - 1);

	std::cout << "Startpoint has " << grid.GetVertexes().vertices[startVertex]->connectedVertexes.vertices.size() << " connected vertexes" << std::endl;
	std::cout << "Generating path from " << grid.GetVertexes().vertices[startVertex]->coordinate.x << "," << grid.GetVertexes().vertices[startVertex]->coordinate.z << " to " << grid.GetVertexes().vertices[targetVertex]->coordinate.x << "," << grid.GetVertexes().vertices[targetVertex]->coordinate.z << std::endl;

	auto startTime = std::chrono::system_clock::now();
	robotguide::path::Path generatePath = pathFinder.FindPath(grid.GetVertexes().vertices.at(startVertex), grid.GetVertexes().vertices.at(targetVertex));
	auto endTime = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = startTime - endTime;
	std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
	std::cout << "Runtime: " << -elapsed_seconds.count() << " ms" << std::endl;

	std::cout << "--------------------" << std::endl << "Path Generated:" << std::endl;
	std::cout << "  > Path length: " << generatePath.vertexPath.size() << std::endl;
	std::cout << "  > Startpoint: " << generatePath.vertexPath.at(0)->coordinate.x << "," << generatePath.vertexPath.at(0)->coordinate.z << std::endl;
	std::cout << "  > Targetpoint: " << generatePath.vertexPath.at(generatePath.vertexPath.size() - 1)->coordinate.x << "," << generatePath.vertexPath.at(generatePath.vertexPath.size() - 1)->coordinate.z << std::endl;
	std::cout << "    > Steps:" << std::endl;
	
	for (std::shared_ptr<robotguide::path::Vertex> step : generatePath.vertexPath)
	{
		std::cout << "      > " << step->coordinate.x << "," << step->coordinate.z << std::endl;
	}
	while (true);
}
