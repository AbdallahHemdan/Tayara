#pragma once
#include "Event.h"

class CancellationEvent : public Event
{
public:
	// Take the eTime and OrderID to use them in deletion
	CancellationEvent(int eTime, int oID);
	CancellationEvent();
	~CancellationEvent();

	/// Assigned to Mahboub ( Input Part )
	virtual void Execute(Restaurant *pRest);	//override execute function

};

