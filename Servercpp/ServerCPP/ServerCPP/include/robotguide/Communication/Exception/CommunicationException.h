#ifndef ROBOTGUIDE_COMMUNICATION_EXCEPTION_COMMUNICATIONEXCEPTION_H
#define ROBOTGUIDE_COMMUNICATION_EXCEPTION_COMMUNICATIONEXCEPTION_H

#include <exception>

namespace robotguide::com::exception
{
	class CommunicationException : public std::exception
	{
	private:
		const char* text;
	public:
		CommunicationException(const char* text_);

		char const* what() const override;
	};
}

#endif //ROBOTGUIDE_COMMUNICATION_EXCEPTION_COMMUNICATIONEXCEPTION_H