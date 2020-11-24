#ifndef ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_INSTRUCTIONTYPE_H
#define ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_INSTRUCTIONTYPE_H

/*
 * Defines the different input datatypes, used by the lexer.
 */

namespace robotguide::com::al
{
	enum class InstructionType
	{
		// Navigational instructions
		Move,
		Movb,
		Movt,
		Movp,
		Movd,
		Forn,
		Bacn,
		Rign,
		Lefn,
		Turn,
		Tuln,
		Reqn,

		// Error/success instructions
		Navs,
		Navf,
		Timr,
		Comr,
		Hear,

		// Heartbeat instructions
		Heat,
		Heas,
		Heai,

		// Location instructions
		Loca,
		Locb,
		Locc,
		Locd,

		// Verification instructions
		Veri,
		Aski,
		Seni,
		Seti,
		Vers,
	};
}


#endif //ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_INSTRUCTIONTYPE_H