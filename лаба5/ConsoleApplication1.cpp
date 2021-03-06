﻿//#include "pch.h"
#include <iostream>
#include <string>
#pragma warning(disable : 4996)

using namespace std;

template <class T>
struct Node {
	T data;
	Node<T>* next;
	Node<T>* prev;
};

template<class T>
class Stack
{
	template<class T>
	friend class Iterator;
public:
	int count;
	Node<T>* head;
	Node<T>* tail;

	Stack();
	Stack(const T& obj);
	~Stack();

	void AddHead(T);
	void AddTail(T);
	void DeleteHead();
	void DeleteTail();
	void show();
	void ShowCount();

	Iterator<T> begin() { return head; }
	Iterator<T> end() { return tail; }
};

template<class T>
class Iterator
{
	Stack<T>* q;
	Node<T>* current;
public:

	Iterator();
	Iterator(Stack<T>* obj);

	bool begin();
	bool end();
	bool operator++();
	bool operator--();
	bool operator == (T data);

	T operator *();

	void quickSort(Stack<T>* obj);
	void _quickSort(Node<T>* l, Node<T>* h);
	void swap(T* a, T* b);

	Node<T>* partition(Node<T>* l, Node<T>* h);
};

template<class T>
Stack<T>::Stack()
{
	head = NULL;
	tail = NULL;
}

template<class T>
Stack<T>::Stack(const T& obj)
{
	head = new Node<T>;
	head->data = obj.data;
	head->next = NULL;
}

template<class T>
Stack<T>::~Stack()
{
	if (head) {
		while (head != NULL) {
			Node<T>* temp = head;
			head = head->next;
			delete temp;
		}
	}
}

template<class T>
void Stack<T>::AddHead(T data)
{
	Node<T>* temp = new Node<T>;
	temp->next = head;
	temp->data = data;
	temp->prev = 0;

	if (head != 0)
		head->prev = temp;

	if (count == 0)
		head = tail = temp;
	else
		head = temp;

	++count;
}

template<class T>
void Stack<T>::AddTail(T data)
{
	Node<T>* temp = new Node<T>;
	temp->next = 0;
	temp->data = data;
	temp->prev = tail;

	if (tail != 0)
		tail->next = temp;

	if (count == 0)
		head = tail = temp;
	else
		tail = temp;

	++count;
}

template<class T>
void Stack<T>::DeleteTail()
{
	try {
		if (!tail)
			throw "Stack is empty.";

		Node<T>* temp = tail;

		if (count == 1) {
			head = tail = NULL;
			delete temp;
		}
		else {
			tail = tail->prev;
			tail->next = 0;
			delete temp;
		}
		--count;
	}
	catch (char* str) {
		cout << str << endl;
	}
}

template<class T>
void Stack<T>::DeleteHead()
{
	try {
		if (!head)
			throw "Stack is empty.";

		Node<T>* temp = head;

		if (count == 1) {
			head = tail = NULL;
			delete temp;
		}
		else {
			head = head->next;
			head->prev = 0;
			delete temp;
		}
		--count;
	}
	catch (char* str) {
		cout << str << endl;
	}
}

template<class T>
void Stack<T>::show()
{
	if (head) {
		Node<T>* temp = head;
		while (temp->next != NULL)
		{
			cout << temp->data << endl;
			temp = temp->next;
		}
		cout << temp->data << endl;
	}
	else
		cout << "Stack is empty." << endl;

	cout << endl;
}

template<class T>
void Stack<T>::ShowCount()
{
	cout << "Count of elements: " << count << endl;
}

template<class T>
Iterator<T>::Iterator()
{
	q = new Stack<T>;
	current = NULL;
}

template<class T>
Iterator<T>::Iterator(Stack<T>* obj)
{
	q = obj;
}

template<class T>
bool Iterator<T>::begin()
{
	if (q->head) {
		current = q->head;
		return true;
	}
	else
		return false;
}

template<class T>
bool Iterator<T>::end()
{
	if (q->tail) {
		current = q->tail;
		return true;
	}
	else
		return false;
}

template<class T>
bool Iterator<T>::operator++()
{
	if (current->next) {
		current = current->next;
		return true;
	}
	else
		return false;
}

template<class T>
bool Iterator<T>::operator--()
{
	if (current->prev) {
		current = current->prev;
		return true;
	}
	else
		return false;
}

template<class T>
bool Iterator<T>::operator==(T data)
{
	if (current->data != data)
		return true;
	else
		return false;
}

template<class T>
T Iterator<T>::operator*()
{
	if (current)
		return current->data;
}

class Subscriber {
public:
	string lastName;
	string phoneNumber;
	int year;
	Subscriber() { }
	Subscriber(string lName, string pNumber, int y) {
		lastName = lName;
		phoneNumber = pNumber;
		year = y;
	}
	Subscriber(const Subscriber& obj) {
		lastName = obj.lastName;
		phoneNumber = obj.phoneNumber;
		year = obj.year;
	}
	Subscriber& operator =(const Subscriber& obj) {
		if (&obj != this) {
			lastName = obj.lastName;
			phoneNumber = obj.phoneNumber;
			year = obj.year;
		}
		return *this;
	}
	friend bool operator <=(const Subscriber& a, const Subscriber& b);
	friend ostream& operator << (ostream& out, const Subscriber& obj);
	friend istream& operator >> (istream& in, Subscriber& obj);
};

ostream& operator<<(ostream& out, const Subscriber& obj)
{
	out << "Surname: " << obj.lastName << "\nPhone number: " << obj.phoneNumber << "\nYear: " << obj.year;
	return out;
}

bool operator<=(const Subscriber& a, const Subscriber& b)
{
	return a.year <= b.year ? true : false;
}

istream& operator>>(istream& in, Subscriber& obj)
{
	flushall();
	cout << "\nSurname: ";
	in >> obj.lastName;

	cout << "Phone number: ";
	in >> obj.phoneNumber;

	cout << "Year: ";
	in >> obj.year;
	return in;
}

template<typename T>
void Iterator<T>::quickSort(Stack<T>* obj)
{
	// Find last node  
	Node<T>* h = obj->head;

	// Call the recursive QuickSort  
	_quickSort(obj->tail, h);
}
template<typename T>
void Iterator<T>::_quickSort(Node<T>* l, Node<T>* h)
{
	if (h != NULL && l != h && l != h->prev)
	{
		Node<T>* p = partition(l, h);
		_quickSort(l, p->next);
		_quickSort(p->prev, h);
	}
}
template<typename T>
Node<T>* Iterator<T>::partition(Node<T>* l, Node<T>* h)
{
	auto x = h->data;
	// similar to i = l-1 for array implementation  
	auto* i = l->next;

	// Similar to "for (int j = l; j <= h- 1; j++)"  
	for (auto* j = l; j != h; j = j->prev)
	{
		if (j->data <= x)
		{
			// Similar to i++ for array  
			i = (i == NULL) ? l : i->prev;

			swap(&(i->data), &(j->data));
		}
	}
	i = (i == NULL) ? l : i->prev; // Similar to i++  
	swap(&(i->data), &(h->data));
	return i;
}
template<typename T>
void Iterator<T>::swap(T* a, T* b)
{
	T temp = *a;
	*a = *b;
	*b = temp;
}

int main()
{
	Stack<Subscriber>* temp = new Stack<Subscriber>;
	Iterator<Subscriber> iter(temp);

	Subscriber objSubsctiber;

	int choice = 1;
	cout << "1 - AddHead; 2 - AddTail; 3 - DeleteHead; 4 - DeleteTail; \n5 - Show (iter++); 6 - Show (iter--); 7 - getElement; 8 - Sort" << endl;
	cout << "\nYour choice: ";
	cin >> choice;
	while (choice >= 1 & choice <= 8) {
		switch (choice)
		{
		case 1: {
			cin >> objSubsctiber;
			temp->AddHead(objSubsctiber);
			break;
		}
		case 2: {
			cin >> objSubsctiber;
			temp->AddTail(objSubsctiber);
			break;
		}
		case 3: {
			temp->ShowCount();
			temp->DeleteHead();
			temp->ShowCount();
			break;
		}
		case 4: {
			temp->ShowCount();
			temp->DeleteTail();
			temp->ShowCount();
			break;
		}
		case 5: {
			int count = 0;

			try {
				if (iter.begin() != true)
					throw "Stack is empty.";

				do {
					cout << count + 1 << " subscriber" << endl;
					cout << *iter << endl;
					cout << "\n";
					++count;
				} while ((++iter) == true);
			}
			catch (char* str) {
				cout << str << endl;
			}

			break;
		}
		case 6:
		{
			int count = temp->count;

			try {
				if (iter.end() != true)
					throw "Stack is empty.";

				do {
					cout << count << " subscriber" << endl;
					cout << *iter << endl;
					cout << "\n";
					--count;
				} while ((--iter) == true);
			}
			catch (char* str) {
				cout << str << endl;
			}

			break;
		}
		case 7: {
			int subscriber = 0;
			cout << "Get subcriber: ";
			cin >> subscriber;

			if (subscriber > temp->count)
				cout << "Your choise isn't correct." << endl;
			else {
				if (iter.begin() == true) {
					if (subscriber == 1)
						cout << "\nResult\n" << *iter << endl;
					else {
						for (int i = 0; i < subscriber; ++i)
							++iter;

						cout << "\nResult\n" << *iter << endl;
					}
				}
			}
			break;
		}
		case 8: {
			cout << "\nSorting result\n" << endl;
			iter.quickSort(temp);
			int count = temp->count;

			temp->show();
		}
		}
		cout << "\nYour choice: ";
		cin >> choice;
	}

	system("pause");
}
