#include "pch.h"

#include "robotguide/Communication/ApplicationLayer/Instruction/InstructionPrinter.h"
#include "robotguide/Communication/ApplicationLayer/Parser/Parser.h"
#include "robotguide/Communication/ApplicationLayer/Lexer/Lexer.h"
#include "robotguide/Communication/Exception/ApplicationLayer/Lexer/LexerException.h"
#include "robotguide/Communication/ApplicationLayer/Token/IntegerToken.h"
#include "robotguide/Communication/ApplicationLayer/Token/InstructionToken.h"
#include "robotguide/Pathfinding/Path/Path.h"
#include "robotguide/Pathfinding/Path/PathToProtocolInstruction.h"

using namespace robotguide::com::applicationlayer;
using namespace robotguide::path;

//NOTE: starting angle == 0 | right

class TestPathToInstructionConversion : public testing::Test
{
protected:
	TestPathToInstructionConversion() = default;
	virtual ~TestPathToInstructionConversion() = default;

public:
	Coordinate origin = Coordinate(0, 0);

	// The grid has Y inversed.
	Coordinate originUp = Coordinate(0, -1);
	Coordinate originDown = Coordinate(0, 1);
	Coordinate originLeft = Coordinate(-1, 0);
	Coordinate originRight = Coordinate(1, 0);


	Coordinate originUpLeft = Coordinate(-1, -1);
	Coordinate originDownLeft = Coordinate(-1, 1);
	Coordinate originDownRight = Coordinate(1, 1);
	Coordinate originUpRight = Coordinate(1, -1);

	Vertex vertex = Vertex(origin);
	Vertex vertexUp = Vertex(originUp);
	Vertex vertexDown = Vertex(originDown);
	Vertex vertexLeft = Vertex(originLeft);
	Vertex vertexRight = Vertex(originRight);

	Vertex vertexUpLeft = Vertex(originUpLeft);
	Vertex vertexDownLeft = Vertex(originDownLeft);
	Vertex vertexDownRight = Vertex(originDownRight);
	Vertex vertexUpRight = Vertex(originUpRight);
};

// Only checks integer instruction data objects
static void ASSERT_ARE_SAME(const Instruction& rhs, const Instruction& lhs)
{
	auto rhsData = rhs.GetData();
	auto lhsData = lhs.GetData();

	for (auto i = 0; i < rhsData.size(); i++)
	{
		ASSERT_EQ(rhsData[i].GetInteger(), lhsData[i].GetInteger());
	}
	ASSERT_EQ(rhs.GetType(), lhs.GetType());
}

TEST_F(TestPathToInstructionConversion, test_uppermovement)
{
	const auto path = Path({&vertex, &vertexUp});
	auto path_to_instruction = PathToProtocolInstruction();

	InstructionStream instructions;
	path_to_instruction.ConvertPathToInstructionStream(path, instructions);

	ASSERT_EQ(2, instructions.size());
	
	ASSERT_ARE_SAME(Instruction(InstructionType::Turn, { 90 }), instructions[0]);
	ASSERT_ARE_SAME(Instruction(InstructionType::Forn, { 1 }), instructions[1]);
}

TEST_F(TestPathToInstructionConversion, test_downmovement)
{
	const auto path = Path({ &vertex, &vertexDown });
	auto path_to_instruction = PathToProtocolInstruction();

	InstructionStream instructions;
	path_to_instruction.ConvertPathToInstructionStream(path, instructions);

	ASSERT_EQ(2, instructions.size());

	ASSERT_ARE_SAME(Instruction(InstructionType::Turn, { -90 }), instructions[0]);
	ASSERT_ARE_SAME(Instruction(InstructionType::Forn, { 1 }), instructions[1]);
}

TEST_F(TestPathToInstructionConversion, test_leftmovement)
{
	const auto path = Path({ &vertex, &vertexLeft });
	auto path_to_instruction = PathToProtocolInstruction();

	InstructionStream instructions;
	path_to_instruction.ConvertPathToInstructionStream(path, instructions);

	ASSERT_EQ(2, instructions.size());

	ASSERT_ARE_SAME(Instruction(InstructionType::Turn, { -180 }), instructions[0]);
	ASSERT_ARE_SAME(Instruction(InstructionType::Forn, { 1 }), instructions[1]);
}

TEST_F(TestPathToInstructionConversion, test_circleMovement)
{
	const auto path = Path({ &vertex, &vertexUp, &vertexUpLeft, &vertexLeft, &vertexDownLeft, &vertexDown, &vertexDownRight, &vertexRight, &vertexUpRight, &vertexUp });
	auto path_to_instruction = PathToProtocolInstruction();

	InstructionStream instructions;
	path_to_instruction.ConvertPathToInstructionStream(path, instructions);

	ASSERT_EQ(15, instructions.size());
	
	// go to up
	ASSERT_ARE_SAME(Instruction(InstructionType::Turn, { 90 }), instructions[0]);
	ASSERT_ARE_SAME(Instruction(InstructionType::Forn, { 1 }), instructions[1]);

	// go to top left
	ASSERT_ARE_SAME(Instruction(InstructionType::Turn, { 90 }), instructions[2]);
	ASSERT_ARE_SAME(Instruction(InstructionType::Forn, { 1 }), instructions[3]);

	// go to left
	ASSERT_ARE_SAME(Instruction(InstructionType::Turn, { 90 }), instructions[4]);
	ASSERT_ARE_SAME(Instruction(InstructionType::Forn, { 1 }), instructions[5]);

	// go to down left
	ASSERT_ARE_SAME(Instruction(InstructionType::Forn, { 1 }), instructions[6]);

	// go to down
	ASSERT_ARE_SAME(Instruction(InstructionType::Turn, { 90 }), instructions[7]);
	ASSERT_ARE_SAME(Instruction(InstructionType::Forn, { 1 }), instructions[8]);

	// go to down right
	ASSERT_ARE_SAME(Instruction(InstructionType::Forn, { 1 }), instructions[9]);

	// go to right
	ASSERT_ARE_SAME(Instruction(InstructionType::Turn, { 90 }), instructions[10]);
	ASSERT_ARE_SAME(Instruction(InstructionType::Forn, { 1 }), instructions[11]);

	// go to top right
	ASSERT_ARE_SAME(Instruction(InstructionType::Forn, { 1 }), instructions[12]);

	// go to top
	ASSERT_ARE_SAME(Instruction(InstructionType::Turn, { 90 }), instructions[13]);
	ASSERT_ARE_SAME(Instruction(InstructionType::Forn, { 1 }), instructions[14]);
}

TEST_F(TestPathToInstructionConversion, test_rightmovement)
{
	const auto path = Path({ &vertex, &vertexRight });
	auto path_to_instruction = PathToProtocolInstruction();

	InstructionStream instructions;
	path_to_instruction.ConvertPathToInstructionStream(path, instructions);

	ASSERT_EQ(1, instructions.size());

	ASSERT_ARE_SAME(Instruction(InstructionType::Forn, { 1 }), instructions[0]);
}