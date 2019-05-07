#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Events\Event.h"
#include "..\Generic_DS\PQueue.h"
#include "Motorcycle.h"
#include "..\Generic_DS\LinkedList.h"
#include "Order.h"

// it is the maestro of the project
class Restaurant  
{	
private:
	GUI *pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file
	
	//
	// TODO: Add More Data Members As Needed
	//
	PQueue<Order *, int >VIP_PQueue[4];
	Queue<Order *>Frozen_Queue[4];
	LinkedList<Order *> Normal_List[4];
	PQueue<Motorcycle *, double> VIPMotors[4], FrozenMotors[4], NormalMotors[4];
	LinkedList<Motorcycle *> VIP_AssignedMotors[4], Frozen_AssignedMotors[4], Normal_AssignedMotors[4];
	
	LinkedList<Order*> OutputOrdersList; //fill output file by it

	int AutoPromotionTime;
	int VIP_Speed ,Normal_Speed , Frozen_Speed;
	int MotorsID;

	//Counters of Acive Orders (updated in Add(orderType) functions)
	int ActiveOrder[3][4];
	
	//Counters of Avaliable Motorcycles (updated when we dequeue any motor or enqueue it)
	int AvaliableMotors[3][4];

	//Counters of served orders so far 
	int ServedOrders[3][4];

	int LastPosition[4];
	M_AND_O_Types PrintedTypes[4][50];

	bool Different_Speed;

public:
	
	Restaurant();
	~Restaurant();
	void AddEvent(Event* pE);	//adds a new event to the queue of events
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();
	

	/// ==> 
	///  DEMO-related functions. Should be removed in phases 1&2
	void Simulation(int mode); //Phase 1 simluation functions
	void AddtoVIP(Order* VIPOrder, int priority);   //adds an order to the VIP queue
	void AddtoFrozen(Order* FrozenOrder);
	void AddtoNormal(Order* NormalOrder);

	
	void ReadData();
	void ResetDrawingList();
	void CancelOrder(int Normal_ID);
	void PromotOrder(int etim, int Normal_ID, double Mon);
	
	void AutoPromotion();
	void CheckAssigned(int timeStep);
	bool AllisDone() const;
	void UpdateWatingTime(int timestep);
	void OutputFile();
	void SortOrdersByFinishTime();
	void UpdateAvailableMotorsRestStep();
};

#endif