#include "CancellationEvent.h"
#include"../Rest/Restaurant.h"

CancellationEvent::CancellationEvent()
{
}

// Take the eTime and OrderID to use them in deletion
CancellationEvent::CancellationEvent(int eTime, int oID):Event(eTime,oID)
{
}

CancellationEvent::~CancellationEvent()
{
}

/// Assigned to Mahboub ( Input Part ) //ده مش انبوت بارت XD
void CancellationEvent::Execute(Restaurant * pRest)
{
	pRest->CancelOrder(OrderID);
}
