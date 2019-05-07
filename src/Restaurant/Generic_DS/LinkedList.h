#ifndef __LINKED_LIST_H
#define __LINKED_LIST_H

#include "Node.h"
#include <string>
#include <exception>


template<class ItemType>
class LinkedList
{
private:
	Node<ItemType>* headPtr;
	int itemCount;
	Node<ItemType>* getNodeAt(int position) const;
public:
	LinkedList();
	LinkedList(const LinkedList<ItemType> &list);
	virtual ~LinkedList();
	bool isEmpty() const;
	int getLength() const;
	bool insert(int newPosition, const ItemType& newEntry);
	bool remove(int position);
	void clear();

	ItemType getEntry(int position) const;

	void setEntry(int position, const ItemType& newEntry);
};

template<class ItemType>
LinkedList<ItemType>::LinkedList() : headPtr(nullptr), itemCount(0)
{
}

template<class ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList<ItemType> &list)
{
	itemCount = list.itemCount;
	Node<ItemType> *OrigHeadPtr = list->head;  //keep track with original head
	if (OrigHeadPtr == NULL)
		headPtr = NULL;
	else
	{
		headPtr = new Node<ItemType>();
		headPtr->setItem(OrigHeadPtr->getItem());

		Node<ItemType> *newPtr = headPtr; //keep track with the new head
		while (OrigHeadPtr != NULL)
		{
			OrigHeadPtr = OrigHeadPtr->getNext();
			ItemType item = OrigHeadPtr->getItem();

			Node<ItemType> *newNode = new Node<ItemType>(item);
			newPtr->setNext(newNode);
			newPtr = newPtr->getNext();
		}
		newPtr = newPtr->setNext(NULL);
	}
	/*if(this == &list)
	return;
	for(int i=1; i<=list.getLength(); ++i)
	insert(i, list.getEntry(i));*/
}

template<class ItemType>
bool LinkedList<ItemType>::isEmpty() const
{
	return itemCount == 0;
}

template<class ItemType>
int LinkedList<ItemType>::getLength() const
{
	return itemCount;
}

template<class ItemType>
Node<ItemType>* LinkedList<ItemType>::getNodeAt(int position) const
{

	if ((position < 1) && (position > itemCount))
		return NULL;

	Node<ItemType>* curPtr = headPtr;
	for (int skip = 1; skip < position; skip++)
		curPtr = curPtr->getNext();
	return curPtr;
}

template<class ItemType>
ItemType LinkedList<ItemType>::getEntry(int position) const
{
	bool ableToGet = (position >= 1) && (position <= itemCount);
	if (ableToGet)
	{
		Node<ItemType>* nodePtr = getNodeAt(position);
		return nodePtr->getItem();
	}
	else
	{
		string message = "getEntry() called with an empty list or ";
		message = message + "invalid position.";
		throw  std::logic_error(message);
	}
}

template<class ItemType>
bool LinkedList<ItemType>::insert(int newPosition, const ItemType& newEntry)
{
	bool ableToInsert = (newPosition >= 1) && (newPosition <= itemCount + 1);
	if (ableToInsert)
	{

		Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);

		if (newPosition == 1)
		{

			newNodePtr->setNext(headPtr);
			headPtr = newNodePtr;
		}
		else
		{

			Node<ItemType>* prevPtr = getNodeAt(newPosition - 1);

			newNodePtr->setNext(prevPtr->getNext());
			prevPtr->setNext(newNodePtr);
		}
		itemCount++;
	}
	return ableToInsert;
}

template<class ItemType>
bool LinkedList<ItemType>::remove(int position)
{
	bool ableToRemove = (position >= 1) && (position <= itemCount);
	if (ableToRemove)
	{
		Node<ItemType>* curPtr = nullptr;
		if (position == 1)
		{

			curPtr = headPtr;
			headPtr = headPtr->getNext();
		}
		else
		{

			Node<ItemType>* prevPtr = getNodeAt(position - 1);

			curPtr = prevPtr->getNext();

			prevPtr->setNext(curPtr->getNext());
		}
		curPtr->setNext(nullptr);
		delete curPtr;
		curPtr = nullptr;
		itemCount--;
	}
	return ableToRemove;
}

template<class ItemType>
void LinkedList<ItemType>::clear()
{
	while (!isEmpty())
		remove(1);
}

template<class ItemType>
LinkedList<ItemType>::~LinkedList()
{
	clear();
}


#endif