#include "GUI.h"

//////////////////////////////////////////////////////////////////////////////////////////
GUI::GUI()
{
	pWind = new window(WindWidth+15,WindHeight,0,0); 
	pWind->ChangeTitle("The Restautant");

	OrderCount = 0;
	theme = 2;

	//Set color for each order type
	if (theme == 1)
		OrdersClrs[TYPE_NRM] = 	GREEN;	//normal-order color
	else 
		OrdersClrs[TYPE_NRM] = DARKBLUE;	//normal-order color
	OrdersClrs[TYPE_FROZ] = VIOLETRED;		//Frozen-order color
	OrdersClrs[TYPE_VIP] = RED;		//VIP-order color					

	ClearStatusBar();
	ClearDrawingArea(); 
	DrawRestArea();  
	
}
//////////////////////////////////////////////////////////////////////////////////////////
GUI::~GUI()
{
	delete pWind;
}

//////////////////////////////////////////////////////////////////////////////////////////
// ================================== INPUT FUNCTIONS ====================================
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::waitForClick() const
{
	int x,y;
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}
//////////////////////////////////////////////////////////////////////////////////////////
string GUI::GetString() const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label += Key;
		
		PrintMessage(Label);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
// ================================== OUTPUT FUNCTIONS ===================================
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::PrintMessage(string msg, string msg1, string msg2, string msg3, string msg4) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	if (theme == 1)
		pWind->SetPen(color(80, 140, 240));
	else if (theme == 2)
		pWind->SetPen(color(150, 60, 110));

	pWind->SetFont(30, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(10, WindHeight - (int) (StatusBarHeight/(1.0*15/13)), msg); // You may need to change these coordinates later 
	                                                                      // to be able to write multi-line
	pWind->DrawString(10, WindHeight - (int)(StatusBarHeight / (1.0*15/11)), msg1);
	pWind->DrawString(10, WindHeight - (int)(StatusBarHeight / (1.0*5/3)), msg2);
	pWind->DrawString(10, WindHeight - (int)(StatusBarHeight / (1.0*15/7)), msg3);
	pWind->DrawString(10, WindHeight - (int)(StatusBarHeight / 3), msg4);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawString(const int iX, const int iY, const string Text)
{
	pWind->SetPen(LIGHTSEAGREEN);
	pWind->SetFont(18, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(iX, iY, Text);
}

//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusBar() const
{
	if (theme == 1)
	{
		pWind->SetPen(color(100, 100, 100), 3);
		pWind->SetBrush(color(100, 100, 100));
	}
	else if (theme == 2)
	{
		pWind->SetPen(color(210, 190, 200), 3);
		pWind->SetBrush(color(210, 190, 200));
	}
	pWind->DrawRectangle(0, WindHeight - StatusBarHeight, WindWidth, WindHeight);

	pWind->SetPen(color(150, 150, 150), 3);
	pWind->DrawLine(0, WindHeight - StatusBarHeight, WindWidth, WindHeight - StatusBarHeight);

	/*pWind->SetPen(WHITE, 3);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, WindHeight - StatusBarHeight , WindWidth, WindHeight);	

	pWind->SetPen(LIGHTSEAGREEN, 3);
	pWind->DrawLine(0, WindHeight - StatusBarHeight , WindWidth, WindHeight - StatusBarHeight);	*/
}
///////////////////////////////////////////////////////////////////////////////////
void GUI::ClearDrawingArea() const
{
	if (theme == 1)
	{
		pWind->SetPen(color(60, 60, 60), 3);
		pWind->SetBrush(color(60, 60, 60));
	}
	else if (theme == 2)
	{
		pWind->SetPen(color(240, 240, 240), 3);
		pWind->SetBrush(color(240, 240, 240));
	}
	pWind->DrawRectangle(0, MenuBarHeight, WindWidth, WindHeight - StatusBarHeight);

	// Clearing the Drawing area
	/*pWind->SetPen(GOLD, 3);
	pWind->SetBrush(GOLD);
	pWind->DrawRectangle(0, MenuBarHeight, WindWidth, WindHeight - StatusBarHeight);*/
}
///////////////////////////////////////////////////////////////////////////////////
void GUI::DrawRestArea() const
{
	int L = RestWidth / 2;

	// 1- Drawing the 8th star of the Rest
	if (theme == 1)
	{
		pWind->SetPen(color(120, 120, 120));
		pWind->SetBrush(color(120, 120, 120));
	}
	else if (theme == 2)
	{
		pWind->SetPen(color(150, 60, 110));
		pWind->SetBrush(color(150, 60, 110));
	}
	pWind->DrawRectangle(RestStartX, RestStartY, RestEndX, RestEndY);
	int arrX[4] = { RestCenterX, RestCenterX, RestCenterX - pow(2, 0.5)*(RestEndX - RestStartX) / 2, RestCenterX + pow(2, 0.5)*(RestEndX - RestStartX) / 2 };
	int arrY[4] = { RestCenterY - pow(2, 0.5)*(RestEndX - RestStartX) / 2, RestCenterY + pow(2, 0.5)*(RestEndX - RestStartX) / 2, RestCenterY, RestCenterY };
	int arrY2[4] = { RestCenterY + pow(2, 0.5)*(RestEndX - RestStartX) / 2, RestCenterY - pow(2, 0.5)*(RestEndX - RestStartX) / 2, RestCenterY, RestCenterY };
	pWind->DrawPolygon(arrX, arrY, 4);
	pWind->DrawPolygon(arrX, arrY2, 4);


	// 1- Drawing the LIGHTSEAGREEN square of the Rest
	if (theme == 1)
		pWind->SetPen(color(80, 140, 240), 3);
	else if (theme == 2)
		pWind->SetPen(color(200, 120, 190), 3);
	/*pWind->SetPen(LIGHTSEAGREEN);
	pWind->SetBrush(LIGHTSEAGREEN);
	pWind->DrawRectangle(RestStartX, YHalfDrawingArea - L, RestEndX, YHalfDrawingArea + L);*/

	// 2- Drawing the 2 LIGHTSEAGREEN crossed lines (for making 4 regions)
	//pWind->SetPen(LIGHTSEAGREEN, 3);
	pWind->DrawLine(0, YHalfDrawingArea, WindWidth, YHalfDrawingArea);
	pWind->DrawLine(WindWidth / 2, MenuBarHeight, WindWidth / 2, WindHeight - StatusBarHeight);	

	//// 3- Drawing the 2 white crossed lines (inside the Rest)
	//pWind->SetPen(WHITE);
	//pWind->DrawLine(WindWidth/2, YHalfDrawingArea - RestWidth/2, WindWidth/2, YHalfDrawingArea + RestWidth/2);
	//pWind->DrawLine(WindWidth/2 - RestWidth/2, YHalfDrawingArea, WindWidth/2 + RestWidth/2, YHalfDrawingArea);

	pWind->SetPen(color(255, 255, 225));
	pWind->SetBrush(color(255, 255, 255));

	pWind->DrawRectangle(RestStartx, RestStarty, RestEndx, RestEndy);
	int arrx[4] = { RestCenterX, RestCenterX, RestCenterX - pow(2, 0.5)*(RestEndX - RestStartX) / 4, RestCenterX + pow(2, 0.5)*(RestEndX - RestStartX) / 4 };
	int arry[4] = { RestCenterY - pow(2, 0.5)*(RestEndX - RestStartX) / 4, RestCenterY + pow(2, 0.5)*(RestEndX - RestStartX) / 4, RestCenterY, RestCenterY };
	int arry2[4] = { RestCenterY + pow(2, 0.5)*(RestEndX - RestStartX) / 4, RestCenterY - pow(2, 0.5)*(RestEndX - RestStartX) / 4, RestCenterY, RestCenterY };
	pWind->DrawPolygon(arrx, arry, 4);
	pWind->DrawPolygon(arrx, arry2, 4);

	// 4- Drawing the 4 white squares inside the Rest (one for each tower)
	/*pWind->SetPen(WHITE);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(RestStartX + L/3, RestStartY + L/3, RestStartX + 2*L/3, RestStartY + 2*L/3);
	pWind->DrawRectangle(RestStartX + L/3, RestEndY - L/3, RestStartX + 2*L/3, RestEndY - 2*L/3);
	pWind->DrawRectangle(RestEndX - 2*L/3, RestStartY + L/3, RestEndX - L/3, RestStartY + 2*L/3);
	pWind->DrawRectangle(RestEndX - 2*L/3, RestEndY - L/3, RestEndX - L/3, RestEndY - 2*L/3);*/

	// 5- Writing the letter of each region (A, B, C, D)
	if (theme == 1)
		pWind->SetPen(color(80, 140, 240));
	else if (theme == 2)
		pWind->SetPen(color(200, 120, 190));
	pWind->SetFont(25, BOLD, BY_NAME, "Arial");
	pWind->DrawString(RestStartX + (int)(0.33*L), RestStartY + 3 * L / 12, "A");
	pWind->DrawString(RestStartX + (int)(0.33*L), YHalfDrawingArea + 7 * L / 12, "D");
	pWind->DrawString(WindWidth / 2 + (int)(0.55*L), RestStartY + 3 * L / 12, "B");
	pWind->DrawString(WindWidth / 2 + (int)(0.55*L), YHalfDrawingArea + 7 * L / 12, "C");
	/*pWind->SetPen(LIGHTSEAGREEN);
	pWind->SetFont(25, BOLD , BY_NAME, "Arial");
	pWind->DrawString(RestStartX + (int)(0.44*L), RestStartY + 5*L/12, "A");
	pWind->DrawString(RestStartX + (int)(0.44*L), YHalfDrawingArea + 5*L/12, "D");
	pWind->DrawString(WindWidth/2 + (int)(0.44*L), RestStartY + 5*L/12, "B");
	pWind->DrawString(WindWidth/2 + (int)(0.44*L), YHalfDrawingArea + 5*L/12, "C"); 
*/
	//////////////////////////////////
	CreateToolBar();
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawSingleOrder(Order* pO, int RegionCount) const       // It is a private function
{

	//check overflowing 
	if (RegionCount > MaxRegionOrderCount) 
		return; //no more orders can be drawn in this region

	int DrawDistance = RegionCount;
	int YPos = 1;
	if(RegionCount>=MaxHorizOrders )	//max no. of orders to draw in one line
	{
		DrawDistance = (RegionCount-1)%MaxHorizOrders + 1;
		YPos = (RegionCount-1) / MaxHorizOrders + 1; 
	}

	color clr = OrdersClrs[pO->GetType()];
	REGION Region = pO->GetRegion();

	int x, y, refX, refY;
	//First calculate x,y position of the order on the output screen
	//It depends on the region and the order distance
	switch (Region)
	{
	case A_REG:
		refX = (WindWidth / 2 - pow(2, 0.5)* RestWidth / 2);
		refY = YHalfDrawingArea - OrderHeight; //
		x = refX - DrawDistance*OrderWidth - DrawDistance; //(Distance)
		y = refY - YPos*OrderHeight - YPos; // YPos
		break;
	case B_REG:
		refX = (WindWidth / 2 + pow(2, 0.5)*RestWidth / 2);
		refY = YHalfDrawingArea - OrderHeight; //
		x = refX + (DrawDistance - 1)*OrderWidth + DrawDistance; //(Distance)
		y = refY - YPos*OrderHeight - YPos; // YPos
		break;
	case C_REG:
		refX = (WindWidth / 2 + pow(2, 0.5)*RestWidth / 2);
		refY = YHalfDrawingArea + OrderHeight; //
		x = refX + (DrawDistance - 1)*OrderWidth + DrawDistance; //(Distance)
		y = refY + (YPos - 1)*OrderHeight + YPos; // YPos
		break;
	case D_REG:
		refX = (WindWidth / 2 - pow(2, 0.5)*RestWidth / 2);
		refY = YHalfDrawingArea + OrderHeight; //
		x = refX - DrawDistance*OrderWidth - DrawDistance; //(Distance)
		y = refY + (YPos - 1)*OrderHeight + YPos; // YPos
		break;
	default:
		break;
	}

	// Drawing the Order
	pWind->SetPen(clr);
	pWind->SetBrush(clr);
	//pWind->DrawRectangle(x, y, x + OrderWidth, y + OrderHeight);
	pWind->SetFont(20,BOLD, MODERN);
	pWind->DrawInteger(x,y,pO->GetID());
}


//////////////////////////////////////////////////////////////////////////////////////////
/* A function to draw a list of orders and ensure there is no overflow in the drawing*/
// To use this function, you must prepare its input parameters as specified
// [Input Parameters]:
//    orders [ ] : array of Order pointers (ALL orders from all regions in one array)
//    TotalOrders : the size of the array (total no. of orders)
void GUI::DrawOrders() const
{

	//Prepare counter for each region
	int RegionsCounts[REG_CNT]={0};	//initlaize all counters to zero

	for(int i=0; i<OrderCount; i++)
	{
		int orderRegion = OrdListForDrawing[i]->GetRegion();
		RegionsCounts[orderRegion]++;
		DrawSingleOrder(OrdListForDrawing[i], RegionsCounts[orderRegion]);
	}

}

void GUI::UpdateInterface() 
{
	ClearDrawingArea();
	DrawRestArea();
	DrawOrders();
}

/*
	AddOrderForDrawing: Adds a new order to the drawing list
*/
void GUI::AddOrderForDrawing(Order* ptr)
{
	if (OrderCount < MaxPossibleOrdCnt) 
		OrdListForDrawing[OrderCount++] = ptr;

	// Note that this function doesn't allocate any Order objects
	// It only makes the first free pointer in the array
	// points to the same Order pointed to by "ptr"
}

void GUI::ResetDrawingList()
{
	OrderCount = 0;		//resets the orders count to be ready for next timestep updates
}


PROG_MODE	GUI::getGUIMode() const
{
	PROG_MODE Mode;
	do
	{
		PrintMessage("Please select GUI mode:  (1)Interactive",
			"                                           (2)StepByStep",
			"                                           (3)Silent",
			"                                           (4)Phase1");
		PlaySound(TEXT("Sounds/Mode.wav"), NULL, SND_SYNC);
		
		string S = GetString();
		Mode = (PROG_MODE) (atoi(S.c_str())-1);
	}
	while(Mode< 0 || Mode >= MODE_CNT);
	
	return Mode;
}

//////////////////////////////////////////////////////////////////////////////////////////

void GUI::PrintTimeStep(string msg)
{
	// clear the inner circle
	/*pWind->SetPen(color(255, 255, 225));
	pWind->SetBrush(color(255, 255, 255));
	pWind->DrawCircle(RestCenterX, RestCenterY, (RestStartX - RestEndX) / 4);*/

	if (theme == 1)
		pWind->SetPen(color(80, 140, 240));
	else if (theme == 2)
		pWind->SetPen(color(200, 120, 190));

	pWind->SetFont(50, BOLD, BY_NAME, "Arial");
	if (msg.length() == 1)
		pWind->DrawString(RestCenterX - 12, RestCenterY - 23, msg);
	else if (msg.length() == 2)
		pWind->DrawString(RestCenterX - 23, RestCenterY - 23, msg);
	else if (msg.length() == 3)
		pWind->DrawString(RestCenterX - 35, RestCenterY - 23, msg);
}

void GUI::CreateToolBar() const
{
	pWind->SetPen(WHITE, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, WindWidth, 50);

}

/*void GUI::DrawCurTimeStep(int TimeStep) const
{
	pWind->SetPen(LIGHTSEAGREEN);
	pWind->SetFont(50, BOLD, BY_NAME, "Arial");
	if (TimeStep < 10)
		pWind->DrawString(WindWidth / 2 - 12, 4, to_string(TimeStep));
	else if (TimeStep < 100)
		pWind->DrawString(WindWidth / 2 - 24, 4, to_string(TimeStep));
	else
		pWind->DrawString(WindWidth / 2 - 36, 4, to_string(TimeStep));
}*/

void GUI::DrawStatusTable(const int ActiveOrders[3][4], const int AvaliableMotors[3][4], const int ServedOrders[3][4], M_AND_O_Types PrintedTypes[4][50], int LastPosition[4]) const
{
	string Words[5] = { "Region", "Orders", "Motors", "Served" , "Last Step" };
	string chars[4] = { "A", "B", "C", "D" };
	string types[3] = { "V", "F", "N" }, temp = "", temp2 = "";
 	//pWind->SetPen(LIGHTSEAGREEN, 4);
	if (theme == 1)
		pWind->SetPen(color(80, 140, 240), 3);
	else if (theme == 2)
		pWind->SetPen(color(150, 60, 110), 3);

	//Horizontal lines of the table
	for(int i = 0; i < 5; i++)
		pWind->DrawLine(0, WindHeight - (50 + 38 * i), WindWidth, WindHeight - (50 + 38 * i));

	//Vertical lines of the table
	pWind->DrawLine(0, WindHeight - 200, 0, WindHeight);
	for(int i =0 ; i < 5; i++)
		pWind->DrawLine(180 + i * 255, WindHeight - 198, 180 + i * 255, WindHeight);


	//Points of comparison
	pWind->SetFont(29, BOLD, BY_NAME, "Arial");
	for(int i = 0; i < 5; i++)
		pWind->DrawString(49, WindHeight - (195 - i * 37), Words[i]);
	
	pWind->SetFont(30, BOLD, BY_NAME, "Arial");
	for(int i = 0; i < 4; i++)
		pWind->DrawString(301 + (i * 255), WindHeight - 195, chars[i]);

	//Orders drawing
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 4; j++)
			pWind->DrawString((232 + 70 * i) + j * 255, WindHeight - 157, to_string(ActiveOrders[i][j]));

	//Motors drawing
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 4; j++)
			pWind->DrawString((232 + 70 * i) + j * 255, WindHeight - 119, to_string(AvaliableMotors[i][j]));

	//Served orders
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 4; j++)
			pWind->DrawString((232 + 70 * i) + j * 255, WindHeight - 85, to_string(ServedOrders[i][j]));

	//Last time step orders 
	pWind->SetFont(15, BOLD, BY_NAME, "Arial");
	int j = 0;
	for (int i = 0; i < LastPosition[0]; i++)
	{
		if (i < 5)
			temp += types[abbreviation(PrintedTypes[0][i].M_type)] + to_string(PrintedTypes[0][i].M_ID) + "(" + types[abbreviation(PrintedTypes[0][i].O_type)] + to_string(PrintedTypes[0][i].O_ID) + ")" + (i != 4 ? "-" : "");
		else if (i < 10)
			temp2 += types[abbreviation(PrintedTypes[0][i].M_type)] + to_string(PrintedTypes[0][i].M_ID) + "(" + types[abbreviation(PrintedTypes[0][i].O_type)] + to_string(PrintedTypes[0][i].O_ID) + ")" + (i != 9 ? "-" : "");
		else break;
	}
	pWind->DrawString(183, WindHeight - 48, temp), temp = "";
	pWind->DrawString(183, WindHeight - 30, temp2), temp2 = "";

	for (int i = 0; i < LastPosition[1]; i++)
	{
		if (i < 5)
			temp += types[abbreviation(PrintedTypes[1][i].M_type)] + to_string(PrintedTypes[1][i].M_ID) + "(" + types[abbreviation(PrintedTypes[1][i].O_type)] + to_string(PrintedTypes[1][i].O_ID) + ")" + (i != 4 ? "-" : "");
		else if (i < 10)
			temp2 += types[abbreviation(PrintedTypes[1][i].M_type)] + to_string(PrintedTypes[1][i].M_ID) + "(" + types[abbreviation(PrintedTypes[1][i].O_type)] + to_string(PrintedTypes[1][i].O_ID) + ")" + (i != 9 ? "-" : "");
		else break;
	}
	pWind->DrawString(437 , WindHeight - 48, temp), temp = "";
	pWind->DrawString(437 , WindHeight - 30, temp2), temp2 = "";

	for (int i = 0; i < LastPosition[2]; i++)
	{
		if (i < 5)

			temp += types[abbreviation(PrintedTypes[2][i].M_type)] + to_string(PrintedTypes[2][i].M_ID) + "(" + types[abbreviation(PrintedTypes[2][i].O_type)] + to_string(PrintedTypes[2][i].O_ID) + ")";
		else if (i < 10)
			temp2 += types[abbreviation(PrintedTypes[2][i].M_type)] + to_string(PrintedTypes[2][i].M_ID) + "(" + types[abbreviation(PrintedTypes[2][i].O_type)] + to_string(PrintedTypes[2][i].O_ID) + ")" + (i != 9 ? "-" : "");
		else break;
	}
	pWind->DrawString(693, WindHeight - 48, temp), temp = "";
	pWind->DrawString(693, WindHeight - 30, temp2), temp2 = "";

	for (int i = 0; i < LastPosition[3]; i++)
	{
		if (i < 5)
			temp += types[abbreviation(PrintedTypes[3][i].M_type)] + to_string(PrintedTypes[3][i].M_ID) + "(" + types[abbreviation(PrintedTypes[3][i].O_type)] + to_string(PrintedTypes[3][i].O_ID) + ")" + (i != 4 ? "-": "") ;
		else if (i < 10)
			temp2 += types[abbreviation(PrintedTypes[3][i].M_type)] + to_string(PrintedTypes[3][i].M_ID) + "(" + types[abbreviation(PrintedTypes[3][i].O_type)] + to_string(PrintedTypes[3][i].O_ID) + ")" + (i != 9 ? "-" : "");
		else break;
	}
	pWind->DrawString(953, WindHeight - 48, temp);
	pWind->DrawString(953, WindHeight - 30, temp2);

}

int GUI::abbreviation(const ORD_TYPE type) const
{
	if (type == TYPE_VIP) return 0;
	else if (type == TYPE_FROZ) return 1;
	else return 2;
}
