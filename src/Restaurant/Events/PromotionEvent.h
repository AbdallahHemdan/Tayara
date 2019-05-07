#pragma once
#include "Event.h"
class PromotionEvent : public Event
{
	
	//Info about the order to add it in Promotion process
	//int OrdDistance;	//order distance	                
	double OrdMoney;	//Total order money

public:
	PromotionEvent(int eTime, int oID,double OrdMoney);
	PromotionEvent();
	~PromotionEvent();

	/// Assigned to Mahboub ( Input Part )
	virtual void Execute(Restaurant *pRest);	//override execute function
	


};

