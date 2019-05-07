#ifndef __GUI_H_
#define __GUI_H_

#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\Defs.h"

#include "..\Rest\Order.h"

#include <string>
using namespace std;

struct M_AND_O_Types
{
	int M_ID, O_ID;
	ORD_TYPE O_type, M_type;
};

class GUI
{

private:
	window *pWind;
	color OrdersClrs[TYPE_CNT];
	int theme;


	// Some Static Constant Data Members: ---------------------

	static const int
		WindWidth = 1200, WindHeight = 700,		//Window width and height
		StatusBarHeight = 200,	//Status Bar Height
		MenuBarHeight = 50,		//Menu Bar Height (distance from top of window to bottom line of menu bar)
		MenuItemWidth = 80,		//Width of each item in menu bar menu

		DrawingAreaHeight = WindHeight - MenuBarHeight - StatusBarHeight,
		YHalfDrawingArea = MenuBarHeight + DrawingAreaHeight / 2, //The y coordinate of half the Drawing area

		RestStartX = (int)(WindWidth * 0.4), //The x coordinate of the upper left corner of the Rest
		RestEndX = (int)(WindWidth * 0.6),   //The x coordinate of the lower right corner of the Rest

		RestStartx = int(WindWidth*0.45),
		RestEndx = int(WindWidth*0.55),

		RestWidth = RestEndX - RestStartX, //The width of the Rest (Note: the Rest is a Square)		

		RestStartY = YHalfDrawingArea - RestWidth / 2, //The y coordinate of the upper left corner of the Rest
		RestEndY = YHalfDrawingArea + RestWidth / 2,   //The y coordinate of the lower right corner of the Rest

		RestStarty = YHalfDrawingArea - RestWidth / 4,
		RestEndy = YHalfDrawingArea + RestWidth / 4,

		RestCenterX = (int)(WindWidth * 0.5),
		RestCenterY = (int)(YHalfDrawingArea),

		FontSize = 25,	//font size used to draw orders ID on Interface
		OrderWidth = 2*FontSize,	//width of the order to be drawn on GUI
		OrderHeight = FontSize,		//height of the order to be drawn on GUI


		MaxHorizOrders	= ((WindWidth-RestWidth)/2 ) / (OrderWidth+1),		//The max no. of orders the can be drwan in on Horizontal line in a region
		MaxVerticalOrders = (DrawingAreaHeight /2)/(OrderHeight + 1),   //The max no. of orders the can be drwan in on Horizontal line in a region


		//Max no of orders that can be drawn in a single region
		MaxRegionOrderCount  = MaxHorizOrders*MaxVerticalOrders;
		
		
		

	/////////
	////////
	////////

	int OrderCount;		//the total number of orders to be drawn
	
	Order * OrdListForDrawing[MaxPossibleOrdCnt]; // This Array of Pointers is used for drawing elements in the GUI
	//NOTES: 
	//Orders are assumed to be sorted by arrival time
	// At every time step, you should update those pointers 
	// to point to the current waiting orders only
	




	// 
	// TODO: Add more members if needed
	//

	void DrawSingleOrder(Order* pO, int RegionCount) const;		//draws ONE order 
	void DrawOrders() const;		//drwas ALL orders in OrdListForDrawing



	void DrawString(const int iX, const int iY, const string Text); // prints a message in the passed coordinates
	void DrawRestArea() const;	    // draws the restaurant area

	void ClearStatusBar() const;    // clears the status bar
	void ClearDrawingArea() const;	// clears the Drawing area from all drawings

	void CreateToolBar() const;
	int abbreviation(const ORD_TYPE type) const;

public:
	GUI();
	~GUI();

	// Input Functions  ---------------------------
	void waitForClick() const;	// waits a user click from the user
	string GetString() const ; // reads a string (keyboard input) from the user

	// Output Functions  ---------------------------
	void PrintMessage(string msg, string msg1 = "", string msg2 = "", string msg3 = "", string msg4 = "") const; // prints a message in the status bar


	void UpdateInterface();
	void AddOrderForDrawing(Order* pOrd);	//Adds a new order to the drawing list
	void ResetDrawingList();		//resets drawing list (should be called every timestep after drawing)
	void PrintTimeStep(string msg);

	PROG_MODE getGUIMode() const;			//returns the mode of the program

	//void DrawCurTimeStep(int TimeStep) const;
	void DrawStatusTable(const int ActiveOrders[3][4], const int AvaliableMotors[3][4], const int ServedOrders[3][4], M_AND_O_Types PrintedTypes[4][50], int LastPosition[4]) const;
};

#endif