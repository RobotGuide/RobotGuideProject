#include "robotguide/Communication/TransportLayer/Receiver.h"

using namespace robotguide::com::transportlayer;

Receiver::~Receiver()
{
	for (ISelectable* selectable : selectables)
	{
		delete selectable;
		selectable = nullptr;
	}
	selectables.clear();
}


void Receiver::AddSelectable(const ISelectable& selectable)
{
	selectables.push_back(selectable.Copy());
}

void Receiver::Clean()
{
	auto iterator = selectables.begin();
	while (iterator != selectables.end())
	{
		if (!(*iterator)->IsConnected())
		{
			ISelectable* temp = *iterator;
			iterator = selectables.erase(iterator);
			delete temp;
			temp = nullptr;
		}
		else
		{
			++iterator;
		}
	}
}
