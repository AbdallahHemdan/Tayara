#include "PromotionEvent.h"
#include "..\Rest\Restaurant.h"
PromotionEvent::PromotionEvent()
{
}

PromotionEvent::PromotionEvent(int eTime, int oID, double oMon) :Event(eTime ,oID)
{
	OrdMoney = oMon;
}

PromotionEvent::~PromotionEvent()
{
}

/// Assigned to Mahboub ( Input Part )
void PromotionEvent::Execute(Restaurant * pRest)
{
	pRest->PromotOrder(EventTime, OrderID, OrdMoney);
}

