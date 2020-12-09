#include "pch.h"
#include "robotguide/Communication/ApplicationLayer/Parser/Parser.h"
#include "robotguide/Communication/ApplicationLayer/Lexer/Lexer.h"

using namespace robotguide::com::applicationlayer;

class TestParser : public testing::Test
{
protected:
	TestParser() = default;

	virtual ~TestParser() = default;

public:
	Instruction CorrectMoveInstruction = Instruction(InstructionType::Move, { 1,2,3 });
	Instruction CorrectMoveInstruction2 = Instruction(InstructionType::Loca, { 84823 });
};

// Only checks integer instruction data objects
void ASSERT_ARE_SAME(const Instruction& rhs, const Instruction& lhs)
{
	auto rhsData = rhs.GetData();
	auto lhsData = lhs.GetData();

	for (auto i = 0; i < rhsData.size(); i++)
	{
		ASSERT_EQ(rhsData[i].GetInteger(), lhsData[i].GetInteger());
	}
	ASSERT_EQ(rhs.GetType(), lhs.GetType());
}

TEST_F(TestParser, InputValidTokenStream_ShouldReturnCorrectInstruction)
{
	TokenStream tokenStream;
	Lexer().GetTokenStream("MOVE 1 2 3", tokenStream);
	InstructionStream instructionStream;
	Parser().GetInstructionStream(tokenStream, instructionStream);

	EXPECT_EQ(1u, instructionStream.size());
	const auto actualInstruction = *instructionStream[0];
	ASSERT_ARE_SAME(CorrectMoveInstruction, actualInstruction);
}

TEST_F(TestParser, InputValidTokenStreamContainingMultipleInstructions_ShouldReturnCorrectInstructions)
{
	TokenStream tokenStream;
	Lexer().GetTokenStream("MOVE 1 2 3 LOCA 84823", tokenStream);
	InstructionStream instructionStream;
	Parser().GetInstructionStream(tokenStream, instructionStream);

	EXPECT_EQ(2u, instructionStream.size());
	const auto actualInstruction1 = *instructionStream[0];
	const auto actualInstruction2 = *instructionStream[1];

	ASSERT_ARE_SAME(CorrectMoveInstruction, actualInstruction1);
	ASSERT_ARE_SAME(CorrectMoveInstruction2, actualInstruction2);
}

TEST_F(TestParser, InputInvalidStream_ShouldThrowInvalidTokenSequenceException)
{

}