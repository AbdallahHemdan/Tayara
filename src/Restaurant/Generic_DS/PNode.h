#ifndef __P_NODE_H_
#define __P_NODE_H_

/*
  This a modified node specially for the generic priority queue
  why we don't use the original node? let be imagine the sinario if we used the original node :
  1- we will inherit from the original node beacuase we need to add "priority" data member
  2- we will add two method "setPriority" and "getPriority"
  that's all fine BUT the main problem when call the method "setNext()" from the base class!
  "getNext()" in the original node depends on node<T> and we use another parameter called "P" which 
  refer to priority and it will cause lots of problems with templates and it will get compilation error(50% of project grade :( );
*/

template<typename T, typename P>
class PNode
{
private:
	T item;            //value that the node holds
	P priority;        //a vlue which assign the position of the node
	PNode<T, P> *next; //next node
public:
	PNode();                                                               //default constructor 
	PNode( const T & r_Item, const P& Priority);	                       //passing by const ref.
	PNode( const T & r_Item, const P& Priority, PNode<T, P>* nextNodePtr); //non-default constructor to initialize full data members
	void setPriority(const P& Priority);                                   //assign the priority of the node
	void setItem( const T & r_Item);                                       //assign the value of the node
	void setNext(PNode<T, P>* nextNodePtr);                                //set the next node
	P getPriority() const;                                                 //return priority of the node
	T getItem() const ;                                                    //return the value of the node
	PNode<T, P>* getNext() const ;                                         //return next node pointer
};

template<typename T, typename P>
PNode<T, P>::PNode()
{
	next = nullptr;
}

template<typename T, typename P>
PNode<T, P>::PNode( const T & r_Item, const P& Priority)
{
	item = r_Item;
	priority = Priority;
	next = nullptr;
}

template<typename T, typename P>
PNode<T, P>::PNode( const T & r_Item, const P& Priority, PNode<T, P>* nextNodePtr)
{
	item = r_Item;
	priority = Priority;
	next = nextNodePtr;
}

template<typename T, typename P>
void PNode<T, P>::setPriority(const P& Priority)
{
	priority = Priority;
}

template<typename T, typename P>
P PNode<T, P>::getPriority() const
{
	return priority;
}

template<typename T, typename P>
void PNode<T, P>::setItem( const T& r_Item)
{
	item = r_Item;
} 

template<typename T, typename P>
void PNode<T, P>::setNext(PNode<T, P>* nextNodePtr)
{
	next = nextNodePtr;
} 

template<typename T, typename P>
T PNode<T, P>::getItem() const
{
	return item;
} 

template<typename T, typename P>
PNode<T, P>* PNode<T, P>::getNext() const
{
	return next;
} 
#endif