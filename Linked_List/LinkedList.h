#pragma once
#include "LinkedListInterface.h"
#include <iostream>
#include <ostream>
using namespace std;

template <typename T>
class LinkedList : public LinkedListInterface<T>
{
	/*Each item in the linked list is a node*/
	struct Node
	{
		T data;
		Node* next;
		Node* previous;
		Node(const T& d, Node* p = NULL, Node* n = NULL) : data(d), next(n), previous(p) {}
		~Node() = default;
	};
	Node* head;
	Node* tail;
public:
	LinkedList() : head(NULL), tail(NULL) {}
	~LinkedList() = default;

	/** Add to the beginning of the list */
	virtual void push_front(const T& item)
	{
		Node* newNode = new Node(item, NULL, head);
		if (head != NULL) head->previous = newNode;
		head = newNode;
		if (tail == NULL) tail = newNode;
		return;
	}

	/*cout << [linked list] will print out the linked list*/
	friend ostream& operator<<(ostream& os, LinkedList& list)
	{
		os << list.toString() << endl;
		return os;
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class Iterator
	{
	private:
		Node* iNode;
	public:
		Iterator(Node* head) : iNode(head) { }
		~Iterator() {}

		bool operator!=(const Iterator& rhs) const
		{
			return this->iNode != rhs.iNode;
		}

		Iterator& operator++()
		{
			iNode = iNode->next;
			return *this;
		}

		T& operator*() const
		{
			return iNode->data;
		}

		Node* getPrevious()
		{
			return iNode->previous;
		}

		Node* getNext()
		{
			return iNode->next;
		}
		Node* getNode()
		{
			return iNode;
		}
	};

	Iterator begin() { return Iterator(this->head); }
	Iterator end() { return Iterator(this->tail); }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/* Iterate through the list */
	ostream& iterate(ostream& os, Iterator& iter)
	{
		iter = this->begin();
		if (this->empty())
		{
			os << " Empty!" << endl;
		}
		else
		{
			os << endl;
			while (iter != NULL)
			{
				os << " [" << *iter << "]" << endl;
				++iter;
			}
		}
		return os;
	}

	/** Find any item in the list */
	Iterator find(Iterator& first, Iterator& last, const T& value)
	{
		first = this->begin();

		while (first != NULL)
		{
			if (*first == value)
			{
				return first;
			}
			++first;
		}
		return NULL;
	}

	/** Return iterator pointing to inserted value in linked list */
	Iterator insert(Iterator& position, const T& value)
	{
		//Sets the new node to the correct value with the correct previous and next depending on its location
		Node* newNode = new Node(value, ((position.getNext() == NULL) ? ((position.getPrevious() == NULL) ? NULL : position.getPrevious()->next->previous) : ((position.getPrevious() == NULL) ? NULL : position.getNext()->previous->previous)), ((position.getPrevious() == NULL) ? ((position.getNext() == NULL) ? NULL : position.getNext()->previous) : position.getPrevious()->next));
		if (newNode->next != NULL) newNode->next->previous = newNode;
		if (newNode->previous != NULL) newNode->previous->next = newNode;
		else this->head = newNode;
		return position.getPrevious();
	}

	/** Return iterator pointing to inserted value in linked list */
	Iterator insert_after(Iterator position, const T& value)
	{
		//Sets the new node to the correct value with the correct previous and next depending on its location
		Node* newNode = new Node(value, ((position.getNext() == NULL) ? ((position.getPrevious() == NULL) ? NULL : position.getPrevious()->next) : position.getNext()->previous), ((position.getPrevious() == NULL) ? ((position.getNext() == NULL) ? NULL : position.getNext()->previous->next) : ((position.getNext() == NULL) ? NULL : position.getPrevious()->next->next)));
		if (newNode->next != NULL) newNode->next->previous = newNode;
		else this->tail = newNode;
		if (newNode->previous != NULL) newNode->previous->next = newNode;
		return position.getNext();
	}

	/** Return iterator pointing to next item after deleted node linked list */
	Iterator erase(Iterator position)
	{
		Node* node_ptr = position.getNode();
		if (position.getNext() != NULL) position.getNext()->previous = position.getPrevious();
		else tail = position.getPrevious();
		if (position.getPrevious() != NULL) position.getPrevious()->next = position.getNext();
		else head = position.getNext();
		++position;
		delete node_ptr;
		return position;
	}

	/** Replace all old_value(s) with new_value */
	void replace(Iterator first, Iterator last, const T& old_value, const T& new_value)
	{
		first = this->begin();

		while (first != NULL)
		{
			if (*first == old_value)
			{
				*first = new_value;
			}
			++first;
		}
	}

	/** Remove Node at beginning of linked list */
	virtual void pop_front(void)
	{
		if (this->empty()) return;
		Node* node_ptr = head;
		if (node_ptr->next)
		{
			head = node_ptr->next;
			node_ptr->next->previous = NULL;
		}
		else
		{
			head = NULL;
			tail = NULL;
		}
		delete node_ptr;
		return;
	}

	/** Return reference to value of Node at beginning of linked list */
	virtual T& front(void)
	{
		return head->data;
	}

	/** Return true if linked list size == 0 */
	virtual bool empty(void) const
	{
		if (head != NULL) return false;
		return true;
	}

	/** Remove all Nodes with value from linked list */
	virtual void remove(const T& value)
	{
		Node* node_ptr = head;
		Node* node_ptr_2 = head;
		if (this->empty()) return;
		while (node_ptr != NULL)
		{
			if (node_ptr->data == value)
			{
				// Change the node before to skip this one going forward
				if (!node_ptr->previous)
				{
					head = node_ptr->next;
				}
				else
				{
					node_ptr->previous->next = node_ptr->next;
				}

				// Change the node after to skip this one going backwards
				if (!node_ptr->next)
				{
					tail = node_ptr->previous;
				}
				else
				{
					node_ptr->next->previous = node_ptr->previous;
				}

				// Set node_ptr_2 to the previous node so that once we delete the current node we know where we are
				if (!node_ptr->previous)
				{
					node_ptr_2 = head;
				}
				else
				{
					node_ptr_2 = node_ptr->previous;
				}
				delete node_ptr;
				if (node_ptr_2) node_ptr = node_ptr_2;
				else node_ptr = NULL;
				if ((node_ptr != NULL) && (node_ptr->previous != NULL) && (!this->empty()))
				{
					node_ptr = node_ptr->next;
				}
				/*else
				{
					head = NULL;
					tail = NULL;
				}*/
			}
			else
			{
				node_ptr = node_ptr->next;
			}
		}
	}

	/** Remove all Nodes from linked list */
	virtual void clear(void)
	{
		Node* node_ptr = head;
		Node* node_ptr_2 = head;
		if (this->empty()) return;
		while (node_ptr != NULL)
		{
			// Set node_ptr_2 to the next node so that once we delete the current node we know where we are
			node_ptr_2 = node_ptr->next;
			delete node_ptr;
			node_ptr = node_ptr_2;
		}
		head = NULL;
		tail = NULL;
	}

	/** Reverse Nodes in linked list */
	virtual void reverse(void)
	{
		if (this->empty()) return;
		Node* node_ptr = tail;
		Node* node_ptr_2 = tail;
		head = node_ptr;
		while (node_ptr_2 != NULL)
		{
			if (node_ptr != NULL) node_ptr = node_ptr->previous;
			node_ptr_2->previous = node_ptr_2->next;
			node_ptr_2->next = node_ptr;
			if (node_ptr == NULL)
			{
				node_ptr_2->next = NULL;
				tail = node_ptr_2;
			}
			node_ptr_2 = node_ptr;
		}
	}

	/** Return the number of nodes in the linked list */
	virtual size_t size(void) const
	{
		Node* node_ptr = head;
		size_t sizeList = 0;
		while (node_ptr != NULL)
		{
			sizeList++;
			node_ptr = node_ptr->next;
		}
		return sizeList;
	}

	/** Return contents of Linked List as a string */
	virtual std::string toString(void) const
	{
		if (this->empty()) return "Empty!";
		Node* node_ptr = head;
		string s = "";
		while (node_ptr != NULL)
		{
			s = s + node_ptr->data + (node_ptr->next ? " " : "");
			node_ptr = node_ptr->next;
		}
		return s;
	}

	/** BONUS ** Insert Node(value) at end of linked list */
	virtual void push_back(const T& value)
	{
		Node* newNode = new Node(value, tail, NULL);
		if (tail != NULL) tail->next = newNode;
		tail = newNode;
		if (head == NULL) head = newNode;
		return;
	}

	/** BONUS ** Remove Node at end of linked list */
	virtual void pop_back(void)
	{
		if (this->empty()) return;
		Node* node_ptr = tail;
		if (node_ptr->previous)
		{
			tail = node_ptr->previous;
			node_ptr->previous->next = NULL;
		}
		else
		{
			tail = NULL;
			head = NULL;
		}
		delete node_ptr;
		return;
	}

	/** BONUS ** Return reference to value of Node at end of linked list */
	virtual T& back(void)
	{
		return tail->data;
	}

	/*void copy(LinkedList& list2)
	{
		Node* node_ptr = this->head;
		list2.clear();
		while (node_ptr != NULL)
		{
			list2.push_back(this->data);
			node_ptr = node_ptr->next;
		}
	}*/
};
