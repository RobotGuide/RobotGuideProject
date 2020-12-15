#include "pch.h"
#include "robotguide/Pathfinding/Grid/TestGridBuilder.h"
#include "robotguide/Pathfinding/Path/PathFinder.h"
#include "robotguide/Pathfinding/Path/PathToProtocolInstruction.h"

#include <iostream>
#include <random>
#include <time.h>

#include "robotguide/Pathfinding/Path/PathToProtocolInstruction.h"

int main()
{
	robotguide::path::Grid grid;
	robotguide::path::TestGridBuilder* gridBuilder = new robotguide::path::TestGridBuilder();
	gridBuilder->PopulateGrid(&grid);

	robotguide::path::PathFinder pathFinder = robotguide::path::PathFinder(std::make_shared<robotguide::path::Grid>(grid));

	std::cout << grid.GetVertexes().vertexes.size() << " vertexes in grid" << std::endl;

	srand(time(NULL));
	int startVertex = rand() % (grid.GetVertexes().vertexes.size() - 1);
	int targetVertex = rand() % (grid.GetVertexes().vertexes.size() - 1);

	std::cout << "Startpoint has " << grid.GetVertexes().vertexes[startVertex]->connectedVertexes.vertexes.size() << " connected vertexes" << std::endl;
	std::cout << "Generating path from " << grid.GetVertexes().vertexes[startVertex]->coordinate.x << "," << grid.GetVertexes().vertexes[startVertex]->coordinate.z << " to " << grid.GetVertexes().vertexes[targetVertex]->coordinate.x << "," << grid.GetVertexes().vertexes[targetVertex]->coordinate.z << std::endl;
	robotguide::path::Path generatePath = pathFinder.FindPath(grid.GetVertexes().vertexes.at(startVertex), grid.GetVertexes().vertexes.at(targetVertex));

	std::cout << std::endl << std::endl << std::endl << "--------------------" << std::endl << "Path Generated:" << std::endl;
	std::cout << "  > Path length: " << generatePath.vertexPath.size() << std::endl;
	std::cout << "  > Startpoint: " << generatePath.vertexPath.at(0)->coordinate.x << "," << generatePath.vertexPath.at(0)->coordinate.z << std::endl;
	std::cout << "  > Targetpoint: " << generatePath.vertexPath.at(generatePath.vertexPath.size() - 1)->coordinate.x << "," << generatePath.vertexPath.at(generatePath.vertexPath.size() - 1)->coordinate.z << std::endl;
	std::cout << "    > Steps:" << std::endl;

	for (std::shared_ptr<robotguide::path::Vertex> step : generatePath.vertexPath)
	{
		std::cout << "    > " << step->coordinate.x << "," << step->coordinate.z << std::endl;
	}

	auto* const pathToInstruction = new robotguide::path::PathToProtocolInstruction();
	const auto instructions = pathToInstruction->ConvertPathToInstructionStream(generatePath);
	for (const auto& instruction : instructions)
	{
		if (instruction->type == robotguide::com::al::InstructionType::Forn)
		{
			std::cout << "FORN ";
		}
		else if (instruction->type == robotguide::com::al::InstructionType::Turn)
		{
			std::cout << "TURN ";
		}
		std::cout << instruction->data[0].GetInteger() << std::endl;
	}

	while (true);
}
