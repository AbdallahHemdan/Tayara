#ifndef _P_QUEUE_H_
#define _P_QUEUE_H_

/*
This is a program that implements the priority queue abstract data type using a linked list.
The priority queue is implemented as a chain of linked nodes that has one pointer, 
frontPtr pointer for the front of the priority queue.
*/

/*

				The PNode: item of type T and a "next" pointer
					------------- 
					| item| next | --->
					-------------
General Queue case:

                 frontPtr																
					\											   								
					 \											  					   		
					------------- 	  ------------- 	  ------------- 	  ------------- 	  	  
					| item| next |--->| item| next |--->  | item| next |--->  | item| next |---> NULL
					------------- 	  ------------- 	  ------------- 	  -------------	  
		
Empty Case:

                 frontptr	 
						\	 				
						 \					
					---- NULL ------


Single Node Case:
                 frontPtr	
					\			
					 \				
					-------- 	
					|	|nxt -->NULL
					--------	

*/


#include"PNode.h"
#include<stdexcept>
#include<string>

template<typename T, typename P>
class PQueue
{
private:
	PNode<T, P>* frontPtr;
public:
	PQueue();                                           //Default Constructor
	PQueue(const PQueue<T,P>& aPQueue);                 //Copy Constructor
	~PQueue();                                          //Destructor

	bool isEmpty() const;                               //O(1)
	bool add(const T& newEntry, const P& priority);     //O(n)
	bool remove();                                      //O(1)
	T peek();                                           //O(1)
};
#endif

template<typename T, typename P>
PQueue<T,P>::PQueue() : frontPtr(nullptr)
{
}

template<typename T, typename P>
PQueue<T,P>::PQueue(const PQueue<T,P>& aPQueue)
{
	if(aPQueue.isEmpty())                                                          //Special case if the queue is empty
	{
		frontPtr = nullptr;
	}
	else
	{
		PNode<T,P> *oldFront = aPQueue.frontPtr;                                   //pointer to the first node in the old queue 

		PNode<T,P> *frontNode = new Node<T>(oldFront->getItem());
		frontPtr = frontNode;

		while(oldFront->getNext())
		{
			add(oldFront->getNext()->getItem(), oldFront->getNext()->getPriority());  //just call the add fuction and it will be handle it :)
			oldFront = oldFront->getNext();
		}
	}
}

template<typename T, typename P>
PQueue<T,P>::~PQueue()
{
	while(!isEmpty())
		remove();                      //while it is not empty call the remove() fucntion and it will handle it :)
}

/*
Function: isEmpty
Sees whether this queue is empty.

Input: None.
Output: True if the queue is empty; otherwise false.
*/
template<typename T, typename P>
bool PQueue<T,P>::isEmpty() const
{
	return (frontPtr == nullptr);
}

/*Function:add
Adds newEntry at the back of this queue.

Input: newEntry and the priority.
Output: True if the operation is successful; otherwise false.
*/

template<typename T, typename P>
bool PQueue<T,P>::add(const T& newEntry, const P& priority)
{
	PNode<T,P> *node = new PNode<T,P>(newEntry, priority, nullptr);
	if(isEmpty())
		frontPtr = node;
	else
	{
		PNode<T,P> *head = frontPtr;
		//special case: if head node has priority less than the current node
		//it should added in the front and move the head ptr to pointer to it
		if(head->getPriority() > priority)
		{
			node->setNext(frontPtr);
			frontPtr = node;
		}
		else
		{
			while(head->getNext() && head->getNext()->getPriority() < priority)
				head = head->getNext();
			
			node->setNext(head->getNext());
			head->setNext(node);
		}
	}
	return true;
}

/*Function: remove
Removes the front of this queue. That is, removes the item that was added
earliest.

Input: None.
Output: True if the operation is successful; otherwise false.
*/
template<typename T, typename P>
bool PQueue<T,P>::remove()
{
	bool valid = !isEmpty();
	if(valid)
	{
		PNode<T, P> *deleted = frontPtr;
		frontPtr = frontPtr->getNext();
		deleted->setNext(NULL);
		delete deleted;
		deleted = NULL;
	}
	return valid;
}

/*
Function: peek
gets the front of this queue. The operation does not modify the queue.

Input: None.
Output: The front of the queue.
return: the item in the front and if the queue is empty it will throw an exception
*/
template<typename T, typename P>
T PQueue<T,P>::peek()
	throw(std::logic_error)
{
	if(isEmpty())
		throw std::logic_error("Empty List! No items to get");
	return frontPtr->getItem();
}