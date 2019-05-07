#ifndef __ORDER_H_
#define __ORDER_H_

#include "..\Defs.h"

class Order
{

protected:
	int ID;			//Each order has a unique ID (from 1 --> 999 )
	ORD_TYPE type;	//order type: Normal, Frozen, VIP
	REGION Region;  //Region of this order
	int Distance;	//The distance (in meters) between the order location and the resturant                 
	double totalMoney;	//Total order money
	int ArrTime, ServTime, FinishTime;	//arrival, service start, and finish times
	int WaitingTime;

public:
	Order(int id, ORD_TYPE r_Type, REGION r_region, int DST, double MON, int ArrT);
	virtual ~Order();

	int GetID();

    ORD_TYPE GetType() const;
	REGION GetRegion() const;

	void SetDistance(int d);
	int GetDistance() const;

	//
	// TODO: Add More Member Functions As Needed
	//
	void SetWaitingTime(int timestep);
	int getWaitingTime() const;
	int getPriority() const; 
	int getFinishTime()const; 
	int getServiceTime() const; 
	int getArrivalTime()const; 
	int CalcTime(int timeStep, int Speed);
	bool IsWaiting(int TS);
	double GetMoney();
};

#endif
