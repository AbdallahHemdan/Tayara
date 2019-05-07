#include "Order.h"

Order::Order(int id, ORD_TYPE r_Type, REGION r_region, int DST, double MON, int ArrT)
{
	ID = (id > 0 && id < 1000) ? id : 0;	//1<ID<999
	type = r_Type;
	Region = r_region;	
	//should we check for the validaity of the distance? and what we will do if it's invalid?!
	Distance = DST;
	totalMoney = MON;
	ArrTime = ArrT;

}

Order::~Order()
{
}

int Order::GetID()
{
	return ID;
}

ORD_TYPE Order::GetType() const
{
	return type;
}

REGION Order::GetRegion() const
{
	return Region;
}

void Order::SetDistance(int d)
{
	Distance = d>0?d:0;
}

int Order::GetDistance() const
{
	return Distance;
}
void Order::SetWaitingTime(int timestep)
{
	WaitingTime = timestep - ArrTime;
}
int Order::getWaitingTime() const
{
	return WaitingTime;
}

int Order::getPriority() const
{
	return (ArrTime*Distance/totalMoney);
}
int Order::getFinishTime() const
{
	return FinishTime; 
}
int Order::getServiceTime() const
{
	return ServTime;
}
int Order::getArrivalTime() const
{
	return ArrTime; 
}
int Order::CalcTime(int timeStep, int Speed)
{
	ServTime = Distance / Speed;
	WaitingTime = timeStep - ArrTime;
	FinishTime = ArrTime + WaitingTime + ServTime;
	return FinishTime + ServTime;
}
bool Order::IsWaiting(int TS)
{
	return (TS <= WaitingTime + ArrTime);
}
double Order::GetMoney()
{
	return totalMoney;
}
