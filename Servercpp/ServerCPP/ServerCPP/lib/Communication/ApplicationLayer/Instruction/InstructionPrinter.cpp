#include "robotguide/Communication/ApplicationLayer/Instruction/InstructionPrinter.h"
#include <exception>

#include "robotguide/Communication/Exception/ApplicationLayer/Instruction/InvalidConversionToInstructionType.h"

robotguide::com::applicationlayer::InstructionType robotguide::com::applicationlayer::InstructionPrinter::GetInstructionType(
	const std::string& text) const
{
	if (text.size() != 4)
	{
		throw exception::al::InvalidConversionToInstructionType("Text cannot be converted to instruction type");
	}

	if (text == "MOVE")
	{
		return InstructionType::Move;
	}

	if (text == "MOVB")
	{
		return InstructionType::Movb;
	}

	if (text == "MOVT")
	{
		return InstructionType::Movt;
	}

	if (text == "MOVP")
	{
		return InstructionType::Movp;
	}

	if (text == "MOVD")
	{
		return InstructionType::Movd;
	}

	if (text == "FORN")
	{
		return InstructionType::Forn;
	}

	if (text == "BACN")
	{
		return InstructionType::Bacn;
	}

	if (text == "RIGN")
	{
		return InstructionType::Rign;
	}

	if (text == "LEFN")
	{
		return InstructionType::Lefn;
	}

	if (text == "TURN")
	{
		return InstructionType::Turn;
	}

	if (text == "TULN")
	{
		return InstructionType::Tuln;
	}

	if (text == "REQN")
	{
		return InstructionType::Reqn;
	}

	if (text == "NAVS")
	{
		return InstructionType::Navs;
	}

	if (text == "NAVF")
	{
		return InstructionType::Navf;
	}

	if (text == "TIMR")
	{
		return InstructionType::Timr;
	}

	if (text == "COMR")
	{
		return InstructionType::Comr;
	}

	if (text == "HEAR")
	{
		return InstructionType::Hear;
	}

	if (text == "HEAT")
	{
		return InstructionType::Heat;
	}

	if (text == "HEAS")
	{
		return InstructionType::Heas;
	}

	if (text == "HEAI")
	{
		return InstructionType::Heai;
	}

	if (text == "LOCA")
	{
		return InstructionType::Loca;
	}

	if (text == "LOCB")
	{
		return InstructionType::Locb;
	}

	if (text == "LOCC")
	{
		return InstructionType::Locc;
	}

	if (text == "LOCD")
	{
		return InstructionType::Locd;
	}

	if (text == "VERI")
	{
		return InstructionType::Veri;
	}

	if (text == "ASKI")
	{
		return InstructionType::Aski;
	}

	if (text == "SENI")
	{
		return InstructionType::Seni;
	}

	if (text == "SETI")
	{
		return InstructionType::Seti;
	}

	if (text == "VERS")
	{
		return InstructionType::Vers;
	}

	throw exception::al::InvalidConversionToInstructionType("Couldn't convert text to instruction type");
}

std::string robotguide::com::applicationlayer::InstructionPrinter::InstructionTypeToString(const InstructionType type) const
{
	return "not implemented!";
}
