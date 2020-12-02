#ifndef ROBOTGUIDE_COMMUNICATION_EXCEPTION_APPLICATIONLAYER_INSTRUCTION_INVALIDCONVERSIONTOINSTRUCTIONTYPE_H
#define ROBOTGUIDE_COMMUNICATION_EXCEPTION_APPLICATIONLAYER_INSTRUCTION_INVALIDCONVERSIONTOINSTRUCTIONTYPE_H

#include "robotguide/Communication/Exception/ApplicationLayer/ApplicationLayerException.h"

namespace robotguide { namespace com { namespace al
{
	class InvalidConversionToInstructionType : public ApplicationLayerException
	{
	public:
		InvalidConversionToInstructionType(const char* text);
	};
}}}

#endif //ROBOTGUIDE_COMMUNICATION_EXCEPTION_APPLICATIONLAYER_INSTRUCTION_INVALIDCONVERSIONTOINSTRUCTIONTYPE_H