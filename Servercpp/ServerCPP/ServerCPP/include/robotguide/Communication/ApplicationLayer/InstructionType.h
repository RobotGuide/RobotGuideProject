#ifndef ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_INSTRUCTIONTYPE_H
#define ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_INSTRUCTIONTYPE_H

/*
 * Defines the different input datatypes, used by the lexer.
 */

namespace robotguide::com::applicationlayer
{
	enum class InstructionType
	{
		// Navigational instructions
		move,
		movb,
		movt,
		movp,
		movd,
		forn,
		bacn,
		rign,
		lefn,
		turn,
		tuln,
		reqn,

		// Error/success instructions
		navs,
		navf,
		timr,
		comr,
		hear,

		// Heartbeat instructions
		heat,
		heas,
		heai,

		// Location instructions
		loca,
		locb,
		locc,
		locd,

		// Verification instructions
		veri,
		aski,
		seni,
		seti,
		vers,
	};
}


#endif //ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_INSTRUCTIONTYPE_H