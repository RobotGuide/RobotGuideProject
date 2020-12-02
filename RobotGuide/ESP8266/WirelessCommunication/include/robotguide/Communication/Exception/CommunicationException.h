#ifndef ROBOTGUIDE_COMMUNICATION_EXCEPTION_COMMUNICATIONEXCEPTION_H
#define ROBOTGUIDE_COMMUNICATION_EXCEPTION_COMMUNICATIONEXCEPTION_H

#include <exception>

namespace robotguide { namespace com { namespace al
{
	class CommunicationException : public std::exception
	{
	private:
		const char* text;
	public:
		CommunicationException(const char* text_);

		const char* what() const override;
	};
}}}

#endif //ROBOTGUIDE_COMMUNICATION_EXCEPTION_COMMUNICATIONEXCEPTION_H