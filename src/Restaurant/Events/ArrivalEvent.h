#ifndef __ARRIVAL_EVENT_H_
#define __ARRIVAL_EVENT_H_

#include "Event.h"
#include "..\Rest\Order.h"

//class for the arrival event
class ArrivalEvent: public Event
{
	//Info about the order ralted to arrival event
	int OrdDistance;	//order distance
	ORD_TYPE OrdType;	//order type: Normal, Frozen, VIP
	REGION OrdRegion;	//Region of this order	                
	double OrdMoney;	//Total order money
public:
	ArrivalEvent(int eTime, int oID,int oDis, double oMon ,ORD_TYPE oType, REGION reg);
	ArrivalEvent();
	
	
	virtual void Execute(Restaurant *pRest);	//override execute function

};

#endif
