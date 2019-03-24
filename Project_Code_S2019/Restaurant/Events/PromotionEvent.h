#pragma once
#include "Events/Event.h"
class PromotionEvent : public Event
{
	
	//Info about the order to add it in Promotion process
	int OrdDistance;	//order distance
	ORD_TYPE OrdType;	//order type: Normal, Frozen, VIP
	REGION OrdRegion;	//Region of this order	                
	double OrdMoney;	//Total order money

public:
	PromotionEvent();
	PromotionEvent(int eTime, int oID, ORD_TYPE oType, REGION reg);
	~PromotionEvent();

	/// Assigned to Mahboub ( Input Part )
	virtual void Execute(Restaurant *pRest);	//override execute function
};

