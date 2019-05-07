//#include "Drawing.h"
#include "Rest\Restaurant.h"
#include "GUI\GUI.h"

int main()
{
	
	Restaurant* pRest = new Restaurant;
	pRest->RunSimulation();
	
	delete pRest;
	
	return 0;
}
