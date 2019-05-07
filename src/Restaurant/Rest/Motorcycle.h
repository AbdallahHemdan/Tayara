#ifndef __MOTORCYCLE_H_
#define __MOTORCYCLE_H_


#include "..\Defs.h"

#pragma once
class Motorcycle	
{
	int ID;
	ORD_TYPE type;	//for each order type there is a corresponding motorcycle type 
	int speed;	//meters it can move in one clock tick (in one timestep)
	REGION	region;	//region of the motorcycle
	STATUS	status;	//idle or in-service
	
	////// More Variables //////
	int ReturnTime; // Finishtime + ServTime
	int RestPeroid; // the peroid that the motor should rest 
	int RestStep; // How many steps the motor rest 
    double DamageFactor; // factor that represents how much the motdor is damaged

public:

	Motorcycle();
	Motorcycle(int id, ORD_TYPE type, int Speed, REGION Region , int rest); // Initialize the Speed and the region of the motorCycle
	virtual ~Motorcycle();

	int getID();
	ORD_TYPE getType();

	void SetReturnTime(int Total_Time);

	bool CheckAssigned(int timeStep) const;
	void setSpeed(int Speed);
	int getSpeed() const;
	
	int TrafficProblemes();
	void updateReststeps();
	void setDamageFaactor();
	int getRestStep() const;
	void setRestStep(int rest);
};

#endif
