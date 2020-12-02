#ifndef ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_INSTRUCTION_INSTRUCTIONPRINTER_H
#define ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_INSTRUCTION_INSTRUCTIONPRINTER_H

#include "robotguide/Communication/ApplicationLayer/Instruction/InstructionType.h"
#include <string>

namespace robotguide { namespace com { namespace al 
{
	struct InstructionPrinter
	{
	private:
		enum class FCharacter
		{
			M,
			F,
			B,
			R,
			L,
			T,
			C,
			H,
			V,
			A,
			S,
			NONE,
		};

		enum class FSCharacter
		{
			MO,
			FO,
			BA,
			RI,
			LE,
			TU,
			RE,
			NA,
			TI,
			CO,
			HE,
			LO,
			VE,
			AS,
			SE,
			NONE,
		};

		enum class FSTCharacter
		{
			MOV,
			FOR,
			BAC,
			RIG,
			LEF,
			TUR,
			TUL,
			REQ,
			NAV,
			TIM,
			COM,
			HEA,
			LOC,
			VER,
			ASK,
			SEN,
			SET,
			NONE,
		};

		enum class FSTFCharacter
		{
			ASKI,

			BACN,

			COMR,

			FORN,

			HEAR,
			HEAT,
			HEAS,
			HEAI,

			LEFN,
			LOCA,
			LOCB,
			LOCC,
			LOCD,

			MOVE,
			MOVB,
			MOVT,
			MOVP,
			MOVD,

			NAVS,
			NAVF,

			RIGN,
			REQN,

			SENI,
			SETI,

			TURN,
			TULN,
			TIMR,

			VERI,
			VERS,
			
			NONE,
		};
	public:
		InstructionPrinter() = default;

		InstructionType GetInstructionType(const std::string& text) const;
		std::string InstructionTypeToString(const InstructionType type) const;
	};
}}}

#endif //ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_INSTRUCTION_INSTRUCTIONPRINTER_H