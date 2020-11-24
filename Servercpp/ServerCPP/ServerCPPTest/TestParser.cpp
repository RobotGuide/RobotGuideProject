#include "pch.h"
#include "robotguide/Communication/ApplicationLayer/Parser/Parser.h"
#include "robotguide/Communication/ApplicationLayer/Lexer/Lexer.h"

using namespace robotguide::com::al;

class TestParser : public testing::Test
{
protected:
	TestParser() = default;

	virtual ~TestParser() = default;

public:
	Instruction CorrectMoveInstruction = Instruction(InstructionType::Move, { 1,2,3 });
};

TEST_F(TestParser, InputValidTokenStream_ShouldReturnCorrectInstruction)
{
	const auto tokenStream = Lexer().GetTokenStream("MOVE 1 2 3");
	const auto instructionStream = Parser().GetInstructionStream(tokenStream);

	EXPECT_EQ(1u, instructionStream.size());
	ASSERT_EQ(CorrectMoveInstruction, instructionStream[0]);
}

TEST_F(TestParser, InputValidTokenStreamContainingMultipleInstructions_ShouldReturnCorrectInstructions)
{
}

TEST_F(TestParser, InputInvalidStream_ShouldThrowInvalidTokenSequenceException)
{

}