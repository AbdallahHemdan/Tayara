#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"


ArrivalEvent::ArrivalEvent(int eTime, int oID, int oDis, double oMon, ORD_TYPE oType, REGION reg) :Event(eTime, oID)
{
	OrdDistance = oDis;
	OrdType = oType;
	OrdRegion = reg;
	OrdMoney = oMon;
}

ArrivalEvent::ArrivalEvent()
{
}

/// Assigned to Mahboub ( Input Part )
void ArrivalEvent::Execute(Restaurant* pRest)
{
	//This function should create and order and  fills its data 
	//Then adds it to normal, frozen, or VIP order lists that you will create in phase1

	
	
	// Fallah, copied it without even read it
	///For the sake of demo, this function will just create an order and add it to DemoQueue
	///Remove the next code lines in phase 1&2

	Order* pOrd = new Order(OrderID , OrdType, OrdRegion, OrdDistance, OrdMoney, EventTime);

	if(OrdType == TYPE_VIP)
	{
		int priority = EventTime*OrdDistance/OrdMoney;
		pRest->AddtoVIP(pOrd, priority);
	}
	else if(OrdType == TYPE_FROZ) pRest->AddtoFrozen(pOrd);
	else if (OrdType == TYPE_NRM) pRest->AddtoNormal(pOrd);
}
