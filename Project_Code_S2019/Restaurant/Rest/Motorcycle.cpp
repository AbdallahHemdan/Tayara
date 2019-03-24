#include "Motorcycle.h"


Motorcycle::Motorcycle()
{
}


Motorcycle::Motorcycle(int Speed, REGION Region)
{
	speed = Speed;
	region = Region;
	status = IDLE;
}


Motorcycle::~Motorcycle()
{
}
