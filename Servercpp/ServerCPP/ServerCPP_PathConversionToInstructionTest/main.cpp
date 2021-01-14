#include "pch.h"
#include "robotguide/Pathfinding/Grid/TestGridBuilder.h"
#include "robotguide/Pathfinding/Path/PathFinder.h"
#include "robotguide/Pathfinding/Path/PathToProtocolInstruction.h"

#include <iostream>
#include <random>
#include <time.h>
#include <math.h>

#include <chrono>
#include <ctime>

#include "robotguide/Pathfinding/Path/PathToProtocolInstruction.h"

robotguide::path::Path CalculatePath(robotguide::path::PathFinder& pathFinder, robotguide::path::Grid& grid, robotguide::path::Vertex* startVertex, robotguide::path::Vertex* targetVertex)
{
	std::cout << "Startpoint has " << startVertex->connectedVertexes.vertices.size() << " connected vertexes" << std::endl;
	std::cout << "Generating path from " << startVertex->coordinate.x << "," << startVertex->coordinate.z << " to " << targetVertex->coordinate.x << "," << targetVertex->coordinate.z << std::endl;

	auto startTime = std::chrono::system_clock::now();
	robotguide::path::Path generatePath = pathFinder.GeneratePath(startVertex, targetVertex);
	auto endTime = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = startTime - endTime;
	std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
	std::cout << "Runtime: " << -elapsed_seconds.count() << " ms" << std::endl;
	std::cout << "--------------------" << std::endl << "Path Generated:" << std::endl;
	std::cout << "  > Path length: " << generatePath.vertexPath.size() << std::endl;

	if (generatePath.vertexPath.size() == 0)
	{
		return {};
	}

	std::cout << "  > Startpoint: " << generatePath.vertexPath.at(0)->coordinate.x << "," << generatePath.vertexPath.at(0)->coordinate.z << std::endl;
	std::cout << "  > Targetpoint: " << generatePath.vertexPath.at(generatePath.vertexPath.size() - 1)->coordinate.x << "," << generatePath.vertexPath.at(generatePath.vertexPath.size() - 1)->coordinate.z << std::endl;
	std::cout << "    > Steps:" << std::endl;

	for (robotguide::path::Vertex* step : generatePath.vertexPath)
	{
		std::cout << "      > " << step->coordinate.x << "," << step->coordinate.z << std::endl;
	}

	return generatePath;
}

std::tuple<robotguide::path::Vertex*, robotguide::path::Vertex*> GetRandomVertexes(robotguide::path::Grid& grid)
{
	int startVertexIndex = rand() % (grid.GetVertexes().vertices.size() - 1);
	int targetVertexIndex = rand() % (grid.GetVertexes().vertices.size() - 1);

	robotguide::path::Vertex* startVertex = grid.GetVertexes().vertices[startVertexIndex];
	robotguide::path::Vertex* targetVertex = grid.GetVertexes().vertices[targetVertexIndex];

	return { startVertex, targetVertex };
}

int main()
{
	//                      y  x
	std::cout << "Degree: unknown " << (atan2(0, 0) / std::_Pi * 180) << std::endl;
	std::cout << "Degree: 90 " << (atan2(1, 0) / std::_Pi * 180) << std::endl;
	std::cout << "Degree: 180 " << (atan2(0, -1) / std::_Pi * 180) << std::endl;
	std::cout << "Degree: 270 " << (atan2(-1, 0) / std::_Pi * 180) << std::endl;
	std::cout << "Degree: 0/360 " << (atan2(0, 1) / std::_Pi * 180) << std::endl;
	
	robotguide::path::Grid grid;
	robotguide::path::TestGridBuilder* gridBuilder = new robotguide::path::TestGridBuilder();
	gridBuilder->PopulateGrid(&grid);

	robotguide::path::PathFinder pathFinder = robotguide::path::PathFinder(&grid);

	std::cout << grid.GetVertexes().vertices.size() << " vertices in grid" << std::endl;

	srand(time(NULL));
	for (int i = 0; i < 5; i++)
	{
		auto [startVertex, targetVertex] = GetRandomVertexes(grid);
		robotguide::path::Path generatePath = CalculatePath(pathFinder, grid, startVertex, targetVertex);

		auto* const pathToInstruction = new robotguide::path::PathToProtocolInstruction();
		robotguide::com::applicationlayer::InstructionStream instructions;
		pathToInstruction->ConvertPathToInstructionStream(generatePath, instructions);
		for (const auto& instruction : instructions)
		{
			std::cout << instruction->ToString();
		}
	}


	

	while (true);
}
