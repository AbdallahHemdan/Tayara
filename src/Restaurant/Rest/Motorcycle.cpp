#include "Motorcycle.h"
#include <random>

Motorcycle::Motorcycle()
{
}


Motorcycle::Motorcycle(int id, ORD_TYPE tp, int Speed, REGION Region, int rest) : ID(id), type(tp)
{
	speed = Speed;
	region = Region;
	status = IDLE;
	RestPeroid = rest;
	RestStep = 0;
}
Motorcycle::~Motorcycle()
{
}

int Motorcycle::getID()
{
	return ID;
}

ORD_TYPE Motorcycle::getType()
{
	return type;
}

void Motorcycle::SetReturnTime(int Total_Time)
{
	ReturnTime = Total_Time + TrafficProblemes()+DamageFactor*Total_Time ;
}

bool Motorcycle::CheckAssigned(int timeStep) const
{
	return ReturnTime <= timeStep;
}

int Motorcycle::getSpeed() const
{
	return speed;
}
void Motorcycle::setSpeed(int Speed)
{
	speed = Speed;
}
int Motorcycle::TrafficProblemes()
{
	return rand() % 3 + 0;
}
void Motorcycle::updateReststeps()
{
	RestStep++;
}
void Motorcycle::setDamageFaactor()
{
	DamageFactor = double(1.0-RestStep) / RestPeroid;
}
int Motorcycle::getRestStep() const
{
	return RestStep;
}
void Motorcycle::setRestStep (int rest)
{
	RestStep = rest;
}