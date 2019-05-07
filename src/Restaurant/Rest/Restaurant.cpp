#include <cstdlib>
#include <time.h>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <mmsystem.h>
#include <iomanip>
#include <string>
#include <random>
using namespace std;

#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"
#include "..\Events\CancellationEvent.h"
#include "..\Events\PromotionEvent.h"



Restaurant::Restaurant() 
{
	pGUI = NULL;

	for (int j = 0; j < 3; j++)
		for (int i = 0; i < 4; i++)
			ActiveOrder[j][i] = 0;

	for (int j = 0; j < 3; j++)
		for (int i = 0; i < 4; i++)
			AvaliableMotors[j][i] = 0;

	for(int j = 0; j < 3; j++)
		for (int i = 0; i < 4; i++) 
			ServedOrders[j][i] = 0;
	
	for (int i = 0; i < 4; i++)
		LastPosition[i] = 0;

	Different_Speed = false;
	MotorsID = 0;
}

void Restaurant::RunSimulation()
{
	
	pGUI = new GUI;
	PlaySound(TEXT("Sounds/Welcome.wav"), NULL, SND_SYNC);
	PlaySound(TEXT("Sounds/four.wav"), NULL, SND_SYNC);
	PROG_MODE mode = pGUI->getGUIMode();
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		Simulation(1);
		break;
	case MODE_STEP:
		Simulation(2);
		break;
	case MODE_SLNT:
		Simulation(3);
		break;
	case MODE_PHASE1:
		Simulation(4);
		break;
	};
}
//////////////////////////////////  Event handling functions   /////////////////////////////
void Restaurant::AddEvent(Event* pE)	//adds a new event to the queue of events
{
	EventsQueue.enqueue(pE);
}

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event *pE;
	while( EventsQueue.peekFront(pE) )	//as long as there are more events
	{
		if(pE->getEventTime() > CurrentTimeStep )	//no more events at current time
			return;

		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}

}


Restaurant::~Restaurant()
{
		delete pGUI;
}
////////////////////////need functions///////////////////////////////////////

string  GetFileName(const string & prompt) {
	const int BUFSIZE = 1024;
	char buffer[BUFSIZE] = { 0 };
	OPENFILENAME ofns = { 0 };
	ofns.lStructSize = sizeof(ofns);
	ofns.lpstrFile = buffer;
	ofns.nMaxFile = BUFSIZE;
	ofns.lpstrTitle = prompt.c_str();
	GetOpenFileName(&ofns);
	return buffer;
}

void Restaurant::ReadData()
{
	ifstream Data;
	fstream DataSpeed;
	string EnterType, name;

	//pGUI->PrintMessage("Enter the file name");
	
	pGUI->PrintMessage("Choose the file: 1) Enter name     2) Browse file");
	PlaySound(TEXT("Sounds/File.wav"), NULL, SND_SYNC);
	do
	{
		EnterType = pGUI->GetString();
		if (EnterType == "1")
		{
			pGUI->PrintMessage("Enter file name: ");
			PlaySound(TEXT("Sounds/name.wav"), NULL, SND_SYNC);
			name = pGUI->GetString();
		}
		else if (EnterType == "2")
			name = GetFileName("Number which file: ");

		pGUI->PrintMessage("Invalid Choice ", "Choose the file: 1) Enter name     2) Browse file");

	} while ((EnterType != "1" && EnterType != "2") || name == "");

	int len = name.length();
	if (len < 5 || (name[len - 1] != 't' || name[len - 2] != 'x' || name[len - 3] != 't' || name[len - 4] != '.'))
		Data.open(name + ".txt");
	else
		Data.open(name);

	DataSpeed.open("DataSpeed.txt");

	while (Data.fail())
	{
		cout << "Ops Error Opening File, try agian :)" << endl;
		name = pGUI->GetString();
	}

	pGUI->PrintMessage("Different Speeds or not? (y / any other key)");
	PlaySound(TEXT("Sounds/speed.wav"), NULL, SND_SYNC);
	string choice = pGUI->GetString();
	Different_Speed = (choice == "y" || choice == "Y");

	if (Data.is_open())
	{	
		Data >> Normal_Speed >> Frozen_Speed >> VIP_Speed;
		
		int x, y, z;
		double speed;
		for (int i = 0; i < 4; i++)
		{
			Data >> x >> y >> z;
				int count(0);
				while (count<x)
				{
					DataSpeed << rand() % 6 + 1<<" ";
					count++;
				}
				count = 0;
				while (count<y)
				{
					DataSpeed << rand() % 6 + 1<<" ";
					count++;
				}
				count = 0;
				while (count<z)
				{
					DataSpeed << rand() % 6 + 1<<" ";
					count++;
				}
			

			if(i == 0)
			{
				while (x--)
				{
					if (Different_Speed) DataSpeed >> speed;
					else speed = Normal_Speed;
					Motorcycle *Motor = new Motorcycle (MotorsID++, TYPE_NRM, speed, A_REG ,2);
					NormalMotors[0].add(Motor, 1.0/speed), AvaliableMotors[2][0]++;
				}
				while (y--)
				{
					if (Different_Speed) DataSpeed >> speed;
					else speed = Frozen_Speed;
					Motorcycle *Motor = new Motorcycle(MotorsID++, TYPE_FROZ, speed, A_REG ,3);
					FrozenMotors[0].add(Motor, 1.0/speed), AvaliableMotors[1][0]++;
				}
				while (z--)
				{
					if (Different_Speed) DataSpeed >> speed;
					else speed = VIP_Speed;
					Motorcycle *Motor = new Motorcycle(MotorsID++, TYPE_VIP, speed, A_REG ,3);
					VIPMotors[0].add(Motor, 1.0/speed), AvaliableMotors[0][0]++;
				}
			}
			else if (i == 1)
			{
				while (x--)
				{
					if (Different_Speed) DataSpeed >> speed;
					else speed = Normal_Speed;
					Motorcycle *Motor = new Motorcycle(MotorsID++, TYPE_NRM, speed, B_REG ,2);
					NormalMotors[1].add(Motor, 1.0/speed), AvaliableMotors[2][1]++;
				}
				while (y--)
				{
					if (Different_Speed) DataSpeed >> speed;
					else speed = Frozen_Speed;
					Motorcycle *Motor = new Motorcycle(MotorsID++, TYPE_FROZ, speed, B_REG ,3);
					FrozenMotors[1].add(Motor, 1.0/speed), AvaliableMotors[1][1]++;
				}
				while (z--)
				{
					if (Different_Speed) DataSpeed >> speed;
					else speed = VIP_Speed;
					Motorcycle *Motor = new Motorcycle(MotorsID++, TYPE_VIP, speed, B_REG ,3);
					VIPMotors[1].add(Motor, 1.0/speed), AvaliableMotors[0][1]++;
				}
			}
			else if (i == 2)
			{
				while (x--)
				{
					if (Different_Speed) DataSpeed >> speed;
					else speed = Normal_Speed;
					Motorcycle *Motor = new Motorcycle(MotorsID++, TYPE_NRM, speed, C_REG ,2 );
					NormalMotors[2].add(Motor, 1.0/speed), AvaliableMotors[2][2]++;
				}
				while (y--)
				{
					if (Different_Speed) DataSpeed >> speed;
					else speed = Frozen_Speed;
					Motorcycle *Motor = new Motorcycle(MotorsID++, TYPE_FROZ, speed, C_REG ,3);
					FrozenMotors[2].add(Motor, 1.0/speed), AvaliableMotors[1][2]++;
				}
				while (z--)
				{
					if (Different_Speed) DataSpeed >> speed;
					else speed = VIP_Speed;
					Motorcycle *Motor = new Motorcycle(MotorsID++, TYPE_VIP, speed, C_REG ,3);
					VIPMotors[2].add(Motor, 1.0/speed), AvaliableMotors[0][2]++; 
				}
			}
			else
			{
				while (x--)
				{
					if (Different_Speed) DataSpeed >> speed;
					else speed = Normal_Speed;
					Motorcycle *Motor = new Motorcycle(MotorsID++, TYPE_NRM, speed, D_REG ,2);
					NormalMotors[3].add(Motor, 1.0/speed), AvaliableMotors[2][3]++;
				}
				while (y--)
				{
					if (Different_Speed) DataSpeed >> speed;
					else speed = Frozen_Speed;
					Motorcycle *Motor = new Motorcycle(MotorsID++, TYPE_FROZ, speed, D_REG ,3);
					FrozenMotors[3].add(Motor, 1.0/speed), AvaliableMotors[1][3]++;
				}
				while (z--)
				{
					if (Different_Speed) DataSpeed >> speed;
					else speed = VIP_Speed;
					Motorcycle *Motor = new Motorcycle(MotorsID++, TYPE_VIP, speed, D_REG ,3);
					VIPMotors[3].add(Motor, 1.0/speed), AvaliableMotors[0][3]++;
				}
			}
		}
		
		Data >> AutoPromotionTime;

		int n; 
		char Type;
		Data >> n;
		for (int i = 0; i < n; i++)
		{
			Data >> Type;	
			if (Type == 'R')
			{
				
				int TS, ID, DST; double MON;
				char TYP, REG;
				ORD_TYPE ORD;
				REGION Reg;
				Data >> TS >> TYP >> ID >> DST >> MON >> REG;
				if (TYP == 'N')
					ORD = TYPE_NRM;
				else if (TYP == 'F')
					ORD = TYPE_FROZ;
				else
					ORD = TYPE_VIP;

				if (REG == 'A')
					Reg = A_REG;
				else if (REG == 'B')
					Reg = B_REG;
				else if (REG == 'C')
					Reg = C_REG;
				else if (REG == 'D')
					Reg = D_REG;

				Event* Event = new ArrivalEvent(TS, ID ,DST ,MON , ORD ,Reg);
					EventsQueue.enqueue(Event);
			}
			else if (Type == 'P')
			{
				int TS, ID; double MON;
				Data >> TS >> ID >> MON;
				Event* P_Event = new PromotionEvent(TS, ID, MON);
				EventsQueue.enqueue(P_Event);
			}
			else if (Type == 'X')
			{
				int TS, ID;
				Data >> TS >> ID;
				Event* X_Event = new CancellationEvent(TS, ID);
				EventsQueue.enqueue(X_Event);
			}
		}
	}
	Data.close();
	DataSpeed.close();
	
}

void Restaurant::Simulation(int Mode)
{
	ReadData();

	Order* pOrd;
	Motorcycle* pMot;
	Event* pEv;
	int ReturnTime;


	if (Mode == 1)
	{
		pGUI->PrintMessage("Welcome to the Interactive mode ^_^", "Let's begin, Click to start!");
		PlaySound(TEXT("Sounds/Interactive.wav"), NULL, SND_SYNC);
		PlaySound(TEXT("Sounds/Click.wav"), NULL, SND_SYNC);
		pGUI->waitForClick();
	}
	else if (Mode == 2)
	{
		pGUI->PrintMessage("Welcome to the Step-by-step mode ^_^", "Let's start, Click to begin!");
		PlaySound(TEXT("Sounds/Step.wav"), NULL, SND_SYNC);
		PlaySound(TEXT("Sounds/Click.wav"), NULL, SND_SYNC);
		pGUI->waitForClick();
	}
	else if (Mode == 3)
	{
		pGUI->PrintMessage("Welcome to the Silent mode ^_^", "Let's start, Click to begin!");
		PlaySound(TEXT("Sounds/Silent.wav"), NULL, SND_SYNC);
		PlaySound(TEXT("Sounds/Click.wav"), NULL, SND_SYNC);
		pGUI->waitForClick();
	}
	pGUI->UpdateInterface();
	int CurrentTimeStep = 0;
	PlaySound(TEXT("Sounds/Ramadan.wav"), NULL, SND_ASYNC);
	while (AllisDone()&& CurrentTimeStep <= 200)
	{
		//pGUI->DrawCurTimeStep(CurrentTimeStep);

		if (Mode == 1) // Interactive mode activation
			pGUI->waitForClick();
		else if (Mode == 2) // Step-by-step mode activation
			Sleep(500);

		UpdateWatingTime(CurrentTimeStep);
		AutoPromotion();
		UpdateAvailableMotorsRestStep();

		pGUI->PrintMessage(""); // instead of clear status bar;

		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step
		ResetDrawingList();

		if (Mode != 3) //Silent mode activation
			pGUI->UpdateInterface();

		// i send only some counters and recieve them as constants
		pGUI->PrintTimeStep(to_string(CurrentTimeStep));
		pGUI->DrawStatusTable(ActiveOrder, AvaliableMotors, ServedOrders, PrintedTypes, LastPosition);
		for (int i = 0; i < 4; i++) LastPosition[i] = 0;
		CheckAssigned(CurrentTimeStep);

		M_AND_O_Types temp;
		for (int i = 0; i < 4; i++)
		{
			while (ActiveOrder[0][i] > 0)
			{
				// Check if any of the motors is Available
				if (AvaliableMotors[0][i] > 0 || AvaliableMotors[2][i] > 0 || AvaliableMotors[1][i] > 0)
				{
					pOrd = VIP_PQueue[i].peek();
					OutputOrdersList.insert(1, pOrd);
					VIP_PQueue[i].remove();
					ActiveOrder[0][i]--;
					ServedOrders[0][i]++;
					temp.O_ID = pOrd->GetID(), temp.O_type = TYPE_VIP;
				}

				// Control Motors
				if (AvaliableMotors[0][i] > 0)
				{
					pMot = VIPMotors[i].peek();
					VIPMotors[i].remove();
				
					ReturnTime = pOrd->CalcTime(CurrentTimeStep, pMot->getSpeed());
					
					pMot->TrafficProblemes();
					pMot->setDamageFaactor();
					pMot->SetReturnTime(ReturnTime);
					
					VIP_AssignedMotors[i].insert(1, pMot);

					AvaliableMotors[0][i]--;
					temp.M_ID = pMot->getID(), temp.M_type = TYPE_VIP;
				}
				else if (AvaliableMotors[2][i] > 0)
				{
					pMot = NormalMotors[i].peek();
					NormalMotors[i].remove();

					ReturnTime = pOrd->CalcTime(CurrentTimeStep, pMot->getSpeed());
					
					pMot->TrafficProblemes();
					pMot->setDamageFaactor();
					pMot->SetReturnTime(ReturnTime);

					Normal_AssignedMotors[i].insert(1, pMot);

					AvaliableMotors[2][i]--;
					temp.M_ID = pMot->getID(), temp.M_type = TYPE_NRM;
				}
				else if (AvaliableMotors[1][i] > 0)
				{
					pMot = FrozenMotors[i].peek();
					FrozenMotors[i].remove();

					ReturnTime = pOrd->CalcTime(CurrentTimeStep, pMot->getSpeed());
					
					pMot->TrafficProblemes();
					pMot->setDamageFaactor();
					pMot->SetReturnTime(ReturnTime);
					
					Frozen_AssignedMotors[i].insert(1, pMot);

					AvaliableMotors[1][i]--;
					temp.M_ID = pMot->getID(), temp.M_type = TYPE_FROZ;
				}
				else break;
				PrintedTypes[i][LastPosition[i]++] = temp;
			}
		}
		for (int i = 0; i < 4; i++)
		{
			while (ActiveOrder[1][i] > 0 && AvaliableMotors[1][i] > 0)
			{
				Frozen_Queue[i].dequeue(pOrd);
				pMot = FrozenMotors[i].peek();
				FrozenMotors[i].remove();

				OutputOrdersList.insert(1, pOrd);
				Frozen_AssignedMotors[i].insert(1, pMot);


				ReturnTime = pOrd->CalcTime(CurrentTimeStep, pMot->getSpeed());
				pMot->TrafficProblemes();
				pMot->setDamageFaactor();
				pMot->SetReturnTime(ReturnTime);
			
				AvaliableMotors[1][i]--;
				ActiveOrder[1][i]--;
				ServedOrders[1][i]++;

				temp.O_ID = pOrd->GetID(), temp.O_type = TYPE_FROZ;
				temp.M_ID = pMot->getID(), temp.M_type = TYPE_FROZ;
				PrintedTypes[i][LastPosition[i]++] = temp;
			}
		}
		for (int i = 0; i < 4; i++)  // can be served by Normal OR VIP motors <-<-<-<-<
		{
			while (ActiveOrder[2][i] > 0)
			{
				// Check if any of the motors is Available
				if (AvaliableMotors[2][i] > 0 || AvaliableMotors[0][i] > 0)
				{
					pOrd = Normal_List[i].getEntry(1);
					Normal_List[i].remove(1);
					OutputOrdersList.insert(1, pOrd);
					ActiveOrder[2][i]--;
					ServedOrders[2][i]++;
					temp.O_ID = pOrd->GetID(), temp.O_type = TYPE_NRM;
				}

				if (AvaliableMotors[2][i] > 0)
				{
					pMot = NormalMotors[i].peek();
					NormalMotors[i].remove();

					ReturnTime = pOrd->CalcTime(CurrentTimeStep, pMot->getSpeed());
					pMot->SetReturnTime(ReturnTime);
					Normal_AssignedMotors[i].insert(1, pMot);

					AvaliableMotors[2][i]--;
					temp.M_ID = pMot->getID(), temp.M_type = TYPE_NRM;
				}
				else if (AvaliableMotors[0][i] > 0)
				{
					pMot = VIPMotors[i].peek();
					VIPMotors[i].remove();

					ReturnTime = pOrd->CalcTime(CurrentTimeStep, pMot->getSpeed());
					pMot->SetReturnTime(ReturnTime);
					VIP_AssignedMotors[i].insert(1, pMot);

					AvaliableMotors[0][i]--;
					temp.M_ID = pMot->getID(), temp.M_type = TYPE_VIP;
				}
				else break;

				PrintedTypes[i][LastPosition[i]++] = temp;
			}
		}
		CurrentTimeStep++;
	}

	OutputFile();
	pGUI->PrintMessage("generation done, click to END program");
	if (Mode != 3) //Silent mode activation
		pGUI->UpdateInterface();

	PlaySound(TEXT("Sounds/Thank.wav"), NULL, SND_SYNC);
	PlaySound(TEXT("Sounds/Good.wav"), NULL, SND_SYNC);
	PlaySound(TEXT("Sounds/end.wav"), NULL, SND_SYNC);
	pGUI->waitForClick();
	OutputFile();
}
////////////////

void Restaurant::AddtoVIP(Order* VIPOrder, int priority)
{
	pGUI->AddOrderForDrawing(VIPOrder);
	for (int i = 0; i < 4; i++)
	{
		if (VIPOrder->GetRegion() == i)
		{
			ActiveOrder[0][i]++;
			VIP_PQueue[i].add(VIPOrder, priority);
		}
	}
}

void Restaurant::AddtoFrozen(Order* FrozenOrder)
{
	pGUI->AddOrderForDrawing(FrozenOrder);
	for (int i = 0; i < 4; i++)
	{
		if (FrozenOrder->GetRegion() == i)
		{
			ActiveOrder[1][i]++;
			Frozen_Queue[i].enqueue(FrozenOrder);
		}
	}
}

void Restaurant::AddtoNormal(Order* NormalOrder)
{
	pGUI->AddOrderForDrawing(NormalOrder);
	for (int i = 0; i < 4; i++)
		if (NormalOrder->GetRegion() == i)
		{
			ActiveOrder[2][i]++;
			Normal_List[i].insert(Normal_List[i].getLength() + 1, NormalOrder);
		}
}
////////////////

/// ==> end of DEMO-related function
void Restaurant::ResetDrawingList()
{
	Order* pOrd;
	pGUI->ResetDrawingList();
	for (int i = 0; i < 4; i++)
	{
		PQueue<Order *, int >VIPTempPQueue;
		for (int j = 0; j < ActiveOrder[0][i]; j++)
		{
			pOrd = VIP_PQueue[i].peek();
			VIPTempPQueue.add(pOrd, pOrd->getPriority());
			pGUI->AddOrderForDrawing(pOrd);
			VIP_PQueue[i].remove();
		}

		for (int j = 0; j < ActiveOrder[0][i]; j++)
		{
			pOrd = VIPTempPQueue.peek();
			VIP_PQueue[i].add(pOrd, pOrd->getPriority());
			VIPTempPQueue.remove();
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < ActiveOrder[1][i]; j++)
		{
			Frozen_Queue[i].dequeue(pOrd);
			pGUI->AddOrderForDrawing(pOrd);
			Frozen_Queue[i].enqueue(pOrd);
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 1; j <= ActiveOrder[2][i]; j++)
		{
			pOrd = Normal_List[i].getEntry(j);
			pGUI->AddOrderForDrawing(pOrd);
		}
	}
}

void Restaurant::CancelOrder(int Normal_ID)
{
	for (int i = 0; i < 4; ++i)
	{
		int count = 1;
		while (count <= ActiveOrder[2][i])
		{
			Order* order = Normal_List[i].getEntry(count);
			if (order->GetID() == Normal_ID)
			{
				if (order->GetType() == TYPE_NRM)
				{
					ActiveOrder[2][order->GetRegion()]--;
					Normal_List[i].remove(count);
					return;
				}
				else
				{
					pGUI->PrintMessage("Sorry, ONLY NORMAL orders can be cancelled. If you have an objection, talk to the TAs :)");
				}
			}
			else count++;
		}
	}
}
void Restaurant::PromotOrder(int TS ,int Normal_ID  ,double exMon)
{
	for(int i = 0; i < 4; ++i)
	{
		int count = 1;
		while (count <= ActiveOrder[2][i])
		{
			Order* order = Normal_List[i].getEntry(count);
			if (order->GetID() == Normal_ID)
			{
				bool flag1 = order->IsWaiting(TS);
				bool flag2 = order->GetType() == TYPE_NRM;
				if (flag1 && flag2 )
				{
					Order*VIP_Ord = new Order(order->GetID(), TYPE_VIP , order->GetRegion(), order->GetDistance(), order->GetMoney() + exMon, order->getArrivalTime());
					VIP_PQueue[i].add(VIP_Ord, order->getPriority());
					ActiveOrder[0][i]++;
					Normal_List[i].remove(count);
					ActiveOrder[2][i]--;
				}
			}
			count++;
		}
	}
}
void Restaurant::AutoPromotion()
{
	for (int i = 0; i < 4; ++i)
	{
		int count = 1;
		while (count <= ActiveOrder[2][i])
		{
			Order* order = Normal_List[i].getEntry(count);
			if (order ->getWaitingTime() >= AutoPromotionTime)
			{
				Order*VIP_Ord = new Order(order->GetID(), TYPE_VIP, order->GetRegion(), order->GetDistance(), order->GetMoney() , order->getArrivalTime());
				VIP_PQueue[i].add(VIP_Ord, order->getPriority());
				ActiveOrder[0][i]++;
				ActiveOrder[2][i]--;
				Normal_List[i].remove(count);
			}
			count++; //i think, it needs modify like others && and it was
		}
	}
}
void Restaurant::UpdateWatingTime(int timestep)
{
	for (int i = 0; i < 4; ++i)
	{
		int count = 1;
		while (count <= ActiveOrder[2][i])
		{
			Order* order = Normal_List[i].getEntry(count);
			order->SetWaitingTime(timestep);
			count++;
		}
	}
}
void Restaurant::UpdateAvailableMotorsRestStep()
{
	Motorcycle*pMot;

	for (int i = 0; i < 4; i++)
	{

		PQueue<Motorcycle *, double >VIPTempPQueue;
		for (int j = 0; j < AvaliableMotors[0][i]; j++)
		{
			pMot = VIPMotors[i].peek();
			pMot->updateReststeps();
			if (pMot->getRestStep() > 3)
				pMot->setRestStep(0);
				
			VIPTempPQueue.add(pMot,1.0 /pMot->getSpeed());
			VIPMotors[i].remove();
		}
		for (int j = 0; j < AvaliableMotors[0][i]; j++)
		{
			pMot = VIPTempPQueue.peek();
			VIPMotors[i].add(pMot, 1.0 / pMot->getSpeed());
			VIPTempPQueue.remove();
		}
	}

	/////////////////////
	for (int i = 0; i < 4; i++)
	{

		PQueue<Motorcycle *, double >FrozenTempPQueue;
		for (int j = 0; j < AvaliableMotors[1][i]; j++)
		{
			pMot = FrozenMotors[i].peek();
			pMot->updateReststeps();

			if (pMot->getRestStep() > 3)
				pMot->setRestStep(0);

			FrozenTempPQueue.add(pMot, 1.0 / pMot->getSpeed());
			FrozenMotors[i].remove();
		}
		for (int j = 0; j < AvaliableMotors[1][i]; j++)
		{
			pMot = FrozenTempPQueue.peek();
			FrozenMotors[i].add(pMot, 1.0 / pMot->getSpeed());
			FrozenTempPQueue.remove();
		}
	}
	/////////////////////

	for (int i = 0; i < 4; i++)
	{

		PQueue<Motorcycle *, double >NormalTempPQueue;
		for (int j = 0; j < AvaliableMotors[2][i]; j++)
		{
			pMot = NormalMotors[i].peek();
			pMot->updateReststeps();
			if (pMot->getRestStep() > 2)
				pMot->setRestStep(0);

			NormalTempPQueue.add(pMot, 1.0 / pMot->getSpeed());
			NormalMotors[i].remove();
		}
		for (int j = 0; j <AvaliableMotors[2][i]; j++)
		{
			pMot = NormalTempPQueue.peek();
			NormalMotors[i].add(pMot, 1.0 / pMot->getSpeed());
			NormalTempPQueue.remove();
		}
	}
 	
}




void Restaurant::CheckAssigned(int timeStep)
{
	Motorcycle* pMot;
	for (int i = 0; i < 4; ++i)
	{
		int count = 0, size = VIP_AssignedMotors[i].getLength();
		while (++count <= size)
		{
			if (VIP_AssignedMotors[i].getEntry(count)->CheckAssigned(timeStep))
			{
				pMot = VIP_AssignedMotors[i].getEntry(count);
				
				VIPMotors[i].add(pMot, 1.0/pMot->getSpeed());
				AvaliableMotors[0][i]++;
				VIP_AssignedMotors[i].remove(count);
				if (count != size)
					count--;
			}
			size = VIP_AssignedMotors[i].getLength();
		}
	}

	for (int i = 0; i < 4; ++i)
	{
		int count = 0, size = Frozen_AssignedMotors[i].getLength();
		while (++count <= size)
		{
			if (Frozen_AssignedMotors[i].getEntry(count)->CheckAssigned(timeStep))
			{
				pMot = Frozen_AssignedMotors[i].getEntry(count);
				FrozenMotors[i].add(pMot, 1.0/pMot->getSpeed());
				AvaliableMotors[1][i]++;
				Frozen_AssignedMotors[i].remove(count);
				if (count != size)
					count--;
			}
			size = Frozen_AssignedMotors[i].getLength();
		}
	}

	for (int i = 0; i < 4; ++i)
	{
		int count = 0, size = Normal_AssignedMotors[i].getLength();
		while (++count <= size)
		{
			if (Normal_AssignedMotors[i].getEntry(count)->CheckAssigned(timeStep))
			{
				pMot = Normal_AssignedMotors[i].getEntry(count);
				NormalMotors[i].add(pMot, 1.0/pMot->getSpeed());
				AvaliableMotors[2][i]++;
				Normal_AssignedMotors[i].remove(count);
				if (count != size) 
					count--;
			}
			size = Normal_AssignedMotors[i].getLength();
		}
	}
}

bool Restaurant::AllisDone() const
{
	bool VIP_Orders = !VIP_PQueue[0].isEmpty() || !VIP_PQueue[1].isEmpty() || !VIP_PQueue[2].isEmpty() || !VIP_PQueue[3].isEmpty();
	bool Frozen_Orders = !Frozen_Queue[0].isEmpty() || !Frozen_Queue[1].isEmpty() || !Frozen_Queue[2].isEmpty() || !Frozen_Queue[3].isEmpty();
	bool Normal_Orders = !Normal_List[0].isEmpty() || !Normal_List[1].isEmpty() || !Normal_List[2].isEmpty() || !Normal_List[3].isEmpty();

	bool VIP_AssignedMots = !VIP_AssignedMotors[0].isEmpty() || !VIP_AssignedMotors[1].isEmpty() || !VIP_AssignedMotors[2].isEmpty() || !VIP_AssignedMotors[3].isEmpty();
	bool Frozen_AssignedMots = !Frozen_AssignedMotors[0].isEmpty() || !Frozen_AssignedMotors[1].isEmpty() || !Frozen_AssignedMotors[2].isEmpty() || !Frozen_AssignedMotors[3].isEmpty();
	bool Normal_AssignedMots = !Normal_AssignedMotors[0].isEmpty() || !Normal_AssignedMotors[1].isEmpty() || !Normal_AssignedMotors[2].isEmpty() || !Normal_AssignedMotors[3].isEmpty();

	bool total = !EventsQueue.isEmpty() || VIP_Orders || Frozen_Orders || Normal_Orders || VIP_AssignedMots || Frozen_AssignedMots || Normal_AssignedMots;
	return total;
}



// Function to Print the all regions Info to File
void Restaurant::OutputFile()
{ 
	int noOfFile = rand() % 100;
	ofstream Output;
	Output.open("Output" + to_string(noOfFile) + ".txt"); 
	
	SortOrdersByFinishTime(); 
	
	int Size = OutputOrdersList.getLength(); 
	
	double Average_Waiting_Time_A = 0; 
	double Average_Waiting_Time_B = 0;
	double Average_Waiting_Time_C = 0;
	double Average_Waiting_Time_D = 0;

	double Average_Service_Time_A = 0;
	double Average_Service_Time_B = 0;
	double Average_Service_Time_C = 0;
	double Average_Service_Time_D = 0;

	Output << "FT \t ID \t AT \t WT \t ST" << endl;
	for (int i = 1; i <= Size; i++)
	{
		Output <<OutputOrdersList.getEntry(i)->getFinishTime(); 
		Output << " \t " << OutputOrdersList.getEntry(i)->GetID();
		Output << " \t " << OutputOrdersList.getEntry(i)->getArrivalTime();
		Output << " \t " << OutputOrdersList.getEntry(i)->getWaitingTime();
		Output << " \t " << OutputOrdersList.getEntry(i)->getServiceTime() << endl;
	}

	Output << "------------------------------------------------------------------------" << endl;
	Output << "------------------------------------------------------------------------" << endl;

	int CounterOfOrders_A[3]; // Normal => Froze => VIP
	int CounterOfOrders_B[3]; // Normal => Froze => VIP
	int CounterOfOrders_C[3]; // Normal => Froze => VIP
	int CounterOfOrders_D[3]; // Normal => Froze => VIP
	
	memset(CounterOfOrders_A, 0, sizeof(CounterOfOrders_A));
	memset(CounterOfOrders_B, 0, sizeof(CounterOfOrders_B));
	memset(CounterOfOrders_C, 0, sizeof(CounterOfOrders_C));
	memset(CounterOfOrders_D, 0, sizeof(CounterOfOrders_D));

	for (int i = 1; i <= Size; i++) 
	{
		Order* Current = OutputOrdersList.getEntry(i); 
		if (Current->GetRegion() == A_REG)
		{
			Average_Waiting_Time_A += Current->getWaitingTime(); 
			Average_Service_Time_A += Current->getServiceTime();
			
			if (Current->GetType() == 0)
			{
				CounterOfOrders_A[0]++;
			}
			else if (Current->GetType() == 1)
			{
				CounterOfOrders_A[1]++;
			}
			else
			{
				CounterOfOrders_A[2]++;
			}
		}

		if (Current->GetRegion() == B_REG)
		{
			Average_Waiting_Time_B += Current->getWaitingTime();
			Average_Service_Time_B += Current->getServiceTime();
			if (Current->GetType() == 0)
			{
				CounterOfOrders_B[0]++;
			}
			else if (Current->GetType() == 1)
			{
				CounterOfOrders_B[1]++;
			}
			else
			{
				CounterOfOrders_B[2]++;
			}
		}
		
		if (Current->GetRegion() == C_REG)
		{
			Average_Waiting_Time_C += Current->getWaitingTime();
			Average_Service_Time_C += Current->getServiceTime();
			if (Current->GetType() == 0)
			{
				CounterOfOrders_C[0]++;
			}
			else if (Current->GetType() == 1)
			{
				CounterOfOrders_C[1]++;
			}
			else
			{
				CounterOfOrders_C[2]++;
			}
		}
		
		if (Current->GetRegion() == D_REG)
		{
			Average_Waiting_Time_D += Current->getWaitingTime();
			Average_Service_Time_D += Current->getServiceTime();
			if (Current->GetType() == 0)
			{
				CounterOfOrders_D[0]++;
			}
			else if (Current->GetType() == 1)
			{
				CounterOfOrders_D[1]++;
			}
			else
			{
				CounterOfOrders_D[2]++;
			}
		}
	}
	
	int TotalOrders_A = CounterOfOrders_A[0] + CounterOfOrders_A[1] + CounterOfOrders_A[2];
	int TotalOrders_B = CounterOfOrders_B[0] + CounterOfOrders_B[1] + CounterOfOrders_B[2];
	int TotalOrders_C = CounterOfOrders_C[0] + CounterOfOrders_C[1] + CounterOfOrders_C[2];
	int TotalOrders_D = CounterOfOrders_D[0] + CounterOfOrders_D[1] + CounterOfOrders_D[2];
	
	int TotalMotors_A = AvaliableMotors[0][0] + AvaliableMotors[2][0] + AvaliableMotors[1][0]; 
	int TotalMotors_B = AvaliableMotors[0][1] + AvaliableMotors[2][1] + AvaliableMotors[1][1];
	int TotalMotors_C = AvaliableMotors[0][2] + AvaliableMotors[2][2] + AvaliableMotors[1][2];
	int TotalMotors_D = AvaliableMotors[0][3] + AvaliableMotors[2][3] + AvaliableMotors[1][3];

	// Average Service time of Orders in all regions (A-B-C-D)
	Average_Service_Time_A /= TotalOrders_A; 
	Average_Service_Time_B /= TotalOrders_B;
	Average_Service_Time_C /= TotalOrders_C;
	Average_Service_Time_D /= TotalOrders_D;

	// Average Waiting time of Orders in all regions (A-B-C-D)
	Average_Waiting_Time_A /= TotalOrders_A;
	Average_Waiting_Time_B /= TotalOrders_B;
	Average_Waiting_Time_C /= TotalOrders_C;
	Average_Waiting_Time_D /= TotalOrders_D;

	Output << "Region-A : " << endl;
	Output << "Orders : " << TotalOrders_A << "  [ Normal : " << CounterOfOrders_A[0] << ",  Frozen : " << CounterOfOrders_A[1] << ",  VIP : " << CounterOfOrders_A[2] << " ] " << endl;
	Output << "Motor Cycles : " << TotalMotors_A << "  [ Normal : " << AvaliableMotors[2][0] << " ,  Frozen : " << AvaliableMotors[1][0] << " , VIP : " << AvaliableMotors[0][0] << "  ] " << endl;
	Output << "Average Waiting Time : " << fixed << setprecision(3) << Average_Service_Time_A << " ,  Average Service Time : " << fixed << setprecision(3) << Average_Service_Time_A << endl;

	Output << "-----------------------------------------------------" << endl;
	Output << "Region-B : " << endl;
	Output << "Orders : " << TotalOrders_B << "  [ Normal : " << CounterOfOrders_B[0] << ",  Frozen : " << CounterOfOrders_B[1] << ",  VIP : " << CounterOfOrders_B[2] << " ] " << endl;
	Output << "Motor Cycles : " << TotalMotors_B << "  [ Normal : " << AvaliableMotors[2][1] << " ,  Frozen : " << AvaliableMotors[1][1] << " , VIP : " << AvaliableMotors[0][1] << "  ] " << endl;
	Output << "Average Waiting Time : " << fixed << setprecision(3) << Average_Service_Time_B << " ,  Average Service Time : " << fixed << setprecision(3) << Average_Service_Time_B << endl;

	Output << "-----------------------------------------------------" << endl;
	Output << "Region-C : " << endl;
	Output << "Orders : " << TotalOrders_C << "  [ Normal : " << CounterOfOrders_C[0] << ",  Frozen : " << CounterOfOrders_C[1] << ",  VIP : " << CounterOfOrders_C[2] << " ] " << endl;
	Output << "Motor Cycles : " << TotalMotors_C << "  [ Normal : " << AvaliableMotors[2][2] << " ,  Frozen : " << AvaliableMotors[1][2] << " , VIP : " << AvaliableMotors[0][2] << "  ] " << endl;
	Output << "Average Waiting Time : " << fixed << setprecision(3) << Average_Service_Time_C << " ,  Average Service Time : " << fixed << setprecision(3) << Average_Service_Time_C << endl;

	Output << "-----------------------------------------------------" << endl;
	Output << "Region-D : " << endl;
	Output << "Orders : " << TotalOrders_D << "  [ Normal : " << CounterOfOrders_D[0] << ",  Frozen : " << CounterOfOrders_D[1] << ",  VIP : " << CounterOfOrders_D[2] << " ] " << endl;
	Output << "Motor Cycles : " << TotalMotors_D << "  [ Normal : " << AvaliableMotors[2][3] << " ,  Frozen : " << AvaliableMotors[1][3] << " , VIP : " << AvaliableMotors[0][3] << "  ] " << endl;
	Output << "Average Waiting Time : " << fixed << setprecision(3) << Average_Service_Time_D << " ,  Average Service Time : " << fixed << setprecision(3) << Average_Service_Time_D << endl;

	Output.close();

}

void Restaurant::SortOrdersByFinishTime()
{
	int Length = OutputOrdersList.getLength();
	Queue<Order *> Sorted; // Temp Queue to store Sorted orders then clear it 
	Order* Element;
	int Min = 1; 
	
	while(!OutputOrdersList.isEmpty())
	{
		for (int j = Min+1; j <= OutputOrdersList.getLength(); j++)
		{
			if (OutputOrdersList.getEntry(Min)->getFinishTime() > OutputOrdersList.getEntry(j)->getFinishTime())
				Min = j;
			else if (OutputOrdersList.getEntry(Min)->getFinishTime() == OutputOrdersList.getEntry(j)->getFinishTime())
			{
				if (OutputOrdersList.getEntry(Min)->getServiceTime() > OutputOrdersList.getEntry(j)->getServiceTime())
					Min = j; 
			}
		}
		Sorted.enqueue(OutputOrdersList.getEntry(Min)); 
		OutputOrdersList.remove(Min);
		Min = 1;
	}

	
	OutputOrdersList.clear();
	int Pos = 1; 
	while (Length--)
	{
		 Sorted.dequeue(Element);
		 OutputOrdersList.insert(Pos, Element);
		 Pos++; 
	}
}


