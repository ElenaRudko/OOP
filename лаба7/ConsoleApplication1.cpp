﻿#include <iostream>
#include <string>
#include <list>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <functional>
#include <utility>

#pragma warning(disable : 4996)

using namespace std;

class Subscriber {
public:
	string lastName;
	string phoneNumber;
	string year;

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
	friend bool operator <(const Subscriber& a, const Subscriber& b);
	friend bool operator >=(const Subscriber& a, const Subscriber& b);

	friend bool com(const Subscriber& a, const Subscriber& b);

	friend ostream& operator << (ostream& out, const Subscriber& obj);
	friend istream& operator >> (istream& in, Subscriber& obj);
};

//operator overloading
bool operator <(const Subscriber& a, const Subscriber& b)
{
	return a.lastName[0] < b.lastName[0] ? true : false;
}

bool operator <=(const Subscriber& a, const Subscriber& b)
{
	return a.lastName[0] <= b.lastName[0] ? true : false;
}

bool operator >=(const Subscriber& a, const Subscriber& b)
{
	return a.lastName[0] >= b.lastName[0] ? true : false;
}

bool compareYear(const Subscriber& a, const Subscriber& b) {
	return (a.year < b.year);
}

bool comparePhone(const Subscriber& a, const Subscriber& b) {
	return (a.phoneNumber < b.phoneNumber);
}

template<class T>
class Algorithm {
	list<T> subscriber;
	int count = 0;

public:
	void AddHead(T);
	void AddTail(T);
	void ShowList();
	void DeleteHead();
	void DeleteTail();

	void FindElement(string);
	void DeleteElement(string);

	void quicksort(list<Subscriber>::iterator beg, list<Subscriber>::iterator end);
	void quickSort();

	void SortYear() { subscriber.sort(compareYear); }
	void SortPhone() { subscriber.sort(comparePhone); }

	list<Subscriber>::iterator left()
	{
		return subscriber.begin();
	}
	list<Subscriber>::iterator right()
	{
		auto it = subscriber.end();
		return --it;
	}
};

template<class T>
void Algorithm<T>::AddHead(T data)
{
	subscriber.push_front(data);
	count++;
}

template<class T>
void Algorithm<T>::AddTail(T data)
{
	subscriber.push_back(data);
	count++;

}

template<class T>
void Algorithm<T>::ShowList()
{
	try {
		if (subscriber.empty())
			throw "The list is empty";

		cout << endl << setw(40) << "List of available subscriber" << endl;
		cout << endl;
		cout << setw(15) << "Surname" << setw(15) << "Phone number" << setw(15) << "Year" << endl;

		for (auto it = subscriber.begin(); it != subscriber.end(); it++) {
			cout << *it << endl;
		}
	}
	catch (char* str) {
		cout << str << endl;
	}
}

template<class T>
void Algorithm<T>::DeleteHead()
{
	if (subscriber.size() == 0)
		cout << "\nThe list is empty" << endl;
	else
		subscriber.pop_front();
}

template<class T>
void Algorithm<T>::DeleteTail()
{
	if (subscriber.size() == 0)
		cout << "\nThe list is empty" << endl;
	else
		subscriber.pop_back();
}

template<class T>
void Algorithm<T>::FindElement(string props)
{
	if (subscriber.size() != 0) {
		bool result = false;

		for (auto it = subscriber.begin(); it != subscriber.end(); it++) {
			if (it->lastName == props || it->phoneNumber == props || it->year == props) {
				cout << endl << setw(15) << "Surname" << setw(15) << "Phone number" << setw(15) << "Year";
				cout << endl << *it << endl;
				cout << endl;
				result = true;
				break;
			}
		}

		if (result == false)
			cout << "\nThere is no such subscriber" << endl;
	}
	else
		cout << endl << "The list if empty" << endl;
}

template<class T>
void Algorithm<T>::DeleteElement(string props)
{
	if (subscriber.size() != 0) {
		for (auto it = subscriber.begin(); it != subscriber.end(); it++) {
			if (it->lastName == props || it->phoneNumber == props || it->year == props) {
				subscriber.erase(it);
				break;
			}
		}
	}
	else
		cout << endl << "The list if empty" << endl;
}

template <class Itr>
list<Subscriber>::iterator partition(Itr left, Itr right)
{
	Itr i = left++;

	Itr it = left;

	while (it != right)
	{
		if (*it <= *right)
		{
			++i;
			swap(*i, *it);
		}
		++it;
	}

	swap(*(i++), *right);
	return ++i;
}

auto part(list<Subscriber>::iterator beg, list<Subscriber>::iterator end, list<Subscriber>::iterator::value_type& pivot)
{
	auto head = beg;
	auto tail = prev(end);
	while (head != tail) {
		while (*head < pivot) {
			if (++head == tail) {
				return head;
			}
		}
		while (*tail >= pivot) {
			if (--tail == head) {
				return head;
			}
		}
		//cout << "swap  " << *head << " ↔ " << *tail << std::endl;
		iter_swap(head, tail);
		if (++head == tail--) {
			return head;
		}
	}
	return head;
}

template<typename T>
void Algorithm<T>::quicksort(list<Subscriber>::iterator beg, list<Subscriber>::iterator end) {

	if (beg == end) {
		return;
	}

	auto pivot = *beg;
	auto split = part(beg, end, pivot);

	// sort left
	quicksort(beg, split);
	// sort right
	auto new_middle = beg;
	quicksort(++new_middle, end);
}

template<class T>
void Algorithm<T>::quickSort()
{
	quicksort(this->subscriber.begin(), this->subscriber.end());
}

ostream& operator<<(ostream& out, const Subscriber& obj)
{
	out << setw(15) << obj.lastName << setw(15) << obj.phoneNumber << setw(15) << obj.year;
	return out;
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

int main()
{
	Subscriber subsctiber;
	Algorithm<Subscriber> list;

	int choice = 1;
	cout << "1 - push_front; 2 - push_back; 3 - pop_front; 4 - pop_back; \n5 - Show; 6 - Search; 7 - Sort by lastName; 8 - Sort by phone; \n9 - Sort by year; 10 - Removal" << endl;
	cout << "\nYour choice: ";
	cin >> choice;

	while (choice >= 1 & choice <= 10) {
		switch (choice)
		{
		case 1: {
			cin >> subsctiber;
			list.AddHead(subsctiber);
			break;
		}
		case 2: {
			cin >> subsctiber;
			list.AddTail(subsctiber);
			break;
		}
		case 3: {
			list.DeleteHead();
			list.ShowList();
			break;
		}
		case 4: {
			list.DeleteTail();
			list.ShowList();
			break;
		}
		case 5: {
			list.ShowList();
			break;
		}
		case 6: {
			string data;

			cout << "\nEntering the data: ";
			cin >> data;

			list.FindElement(data);
			break;
		}
		case 7: {
			list.quickSort();
			break;
		}
		case 8: {
			list.SortPhone();
			break;
		}
		case 9: {
			list.SortYear();
			break;
		}
		case 10: {
			string data;

			cout << "\nEntering the data: ";
			cin >> data;

			list.DeleteElement(data);

			cout << "The result of the removal" << endl;
			list.ShowList();
			break;
		}
		}
		cout << "\nYour choice: ";
		cin >> choice;
	}
}