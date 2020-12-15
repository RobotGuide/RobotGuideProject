#include "robotguide/Communication/ApplicationLayer/Instruction/InstructionPrinter.h"
#include "robotguide/Communication/Exception/ApplicationLayer/Instruction/InvalidConversionToInstructionType.h"
#include "robotguide/Communication/ApplicationLayer/Instruction/InstructionStream.h"

using namespace robotguide::com::applicationlayer;

InstructionType InstructionPrinter::GetInstructionType(
	const std::string& text) const
{
	if (text.size() != 4)
	{
		throw exception::applicationlayer::InvalidConversionToInstructionType("Text cannot be converted to instruction type");
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

	throw exception::applicationlayer::InvalidConversionToInstructionType("Couldn't convert text to instruction type");
}

std::string InstructionPrinter::InstructionTypeToString(const InstructionType type) const
{
	switch(type)
	{
	case InstructionType::Heat:
		return "HEAT";
	case InstructionType::Aski:
		return "ASKI";
	case InstructionType::Bacn:
		return "BACN";
	case InstructionType::Comr:
		return "COMR";
	case InstructionType::Forn:
		return "FORN";
	case InstructionType::Heai:
		return "HEAI";
	case InstructionType::Hear:
		return "HEAR";
	case InstructionType::Heas:
		return "HEAS";
	case InstructionType::Lefn:
		return "LEFN";
	case InstructionType::Navs:
		return "NAVS";
	case InstructionType::Navf:
		return "NAVF";
	case InstructionType::Movb:
		return "MOVB";
	case InstructionType::Movd:
		return "MOVD";
	case InstructionType::Move:
		return "MOVE";
	case InstructionType::Movp:
		return "MOVP";
	case InstructionType::Movt:
		return "MOVT";
	case InstructionType::Rign:
		return "RIGN";
	case InstructionType::Tuln:
		return "TULN";
	case InstructionType::Turn:
		return "TURN";
	case InstructionType::Timr:
		return "TIMR";
	case InstructionType::Loca:
		return "LOCA";
	case InstructionType::Locb:
		return "LOCB";
	case InstructionType::Locc:
		return "LOCC";
	case InstructionType::Locd:
		return "LOCD";
	case InstructionType::Reqn:
		return "REQN";
	case InstructionType::Seni:
		return "SENI";
	case InstructionType::Seti:
		return "SETI";
	case InstructionType::Veri:
		return "VERI";
	case InstructionType::Vers:
		return "VERS";
	}
	
	return "NONE";
}

std::string InstructionPrinter::ConvertInstructionStreamToASCII(const InstructionStream& stream) const
{
	std::string ASCII_Variant;
	for (const auto* instruction : stream)
	{
		ASCII_Variant += ConvertInstructionToASCII(*instruction) + '\n';
	}
	return ASCII_Variant;
}

std::string InstructionPrinter::ConvertInstructionToASCII(const Instruction& instruction) const
{
	std::string ASCII_Variant;
	ASCII_Variant += InstructionTypeToString(instruction.GetType());
	for (const auto& data : instruction.GetData())
	{
		ASCII_Variant += ' ';
		ASCII_Variant += std::to_string(data.GetInteger());
	}

	return ASCII_Variant;
}
