#include "robotguide/Communication/TransportLayer/WindowsReceiver.h"
#include <iostream>
#include <vector>
#include <Windows.h>
#include <WinSock2.h>


using namespace  robotguide::com::transportlayer;

void WindowsReceiver::CheckForData()
{
	SetFDSet();
	const size_t length = selectables.size();
	for (size_t i = 0; i < length; i++)
	{
		if (FD_ISSET(selectables[i]->GetSocketHandle(), &ReadSet))
		{
			selectables[i]->HandleAvailableData();
		}
	}
}

int WindowsReceiver::SetFDSet()
{
	FD_ZERO(&ReadSet);
	struct timeval tv
	{
		0, 50
	};

	for (ISelectable* selectable : selectables)
	{
		FD_SET(selectable->GetSocketHandle(), &ReadSet);
	}

	return select(0, &ReadSet, nullptr, nullptr, &tv);
}
