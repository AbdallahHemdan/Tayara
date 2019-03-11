#ifndef __DEFS_H_
#define __DEFS_H_


//The four regions: A, B, C , and D
enum REGION {	
	A_REG,
	B_REG,
	C_REG,
	D_REG,
	REG_CNT		//Total number of regions
};


enum ORD_TYPE	//types of orders
{
	TYPE_NRM,	//normal order
	TYPE_FROZ,	//frozen
	TYPE_VIP,	//VIP
	TYPE_CNT	//Number of types

};

enum STATUS	//status of motorcycles
{
	IDLE,	//idle ==> waiting to be assigned at order
	SERV	//is-service ==> is delivering at order but hasn't returned yet.
};


enum PROG_MODE	//mode of the program interface
{
	MODE_INTR,	//interactive mode
	MODE_STEP,	//Step-by-step mode
	MODE_SLNT,	//Silent mode
	MODE_DEMO,	//Demo mode (for introductory phase only, should be removed in phases 1&2)
	MODE_CNT	//number of possible modes
};


#define MaxPossibleOrdCnt 999	//arbitrary value





#endif