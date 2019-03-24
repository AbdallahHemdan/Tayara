#include "PromotionEvent.h"

PromotionEvent::PromotionEvent()
{

}

PromotionEvent::PromotionEvent(int eTime, int oID, ORD_TYPE oType, REGION reg) : Event(eTime, oID)
{
	OrdType = oType;
	OrdRegion = reg;
}

PromotionEvent::~PromotionEvent()
{
}

/// Assigned to Mahboub ( Input Part )
void PromotionEvent::Execute(Restaurant * pRest)
{
}
