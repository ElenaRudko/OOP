//#include "pch.h"
#include<iostream>
#include<fstream>
#include<iomanip>
#include<string.h>
#pragma warning(disable : 4996)

using namespace std;

template <typename T1, typename T2, typename T3>
struct Element {
	char firstName[40];
	char klas[40];
	char counture[40];
	int year;
	int c;
};

template <typename T1, typename T2, typename T3>
class TextFile {
private:
	Element<T1, T2, T3> object;
	char fileName[20] = "file.dat";
	int count = 0;
public:
	TextFile();
	void setData();
	void sortData();
	void showData();
};

template <typename T1, typename T2, typename T3>
TextFile<T1, T2, T3>::TextFile() {
	FILE* f = std::fopen(this->fileName, "rb");
	while (std::fread(&object, sizeof(Element<T1, T2, T3>), 1, f)) {
		++count;
	}
}

template <typename T1, typename T2, typename T3>
void TextFile<T1, T2, T3>::setData() {
	int choice = 1;
	fstream file;
	file.open(this->fileName, ios::binary | ios::out);
	this->count = 0;
	do
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "\nИмя: ";
		cin.getline(object.firstName, 40);
		cout << "Класс музыкального инструмента: ";
		cin.clear();
		cin.getline(object.klas, 40);
		cout << "Страна: ";
		cin.getline(object.counture, 40);
		cout << "Возраст: ";
		cin >> object.year;
		cout << "Занятое место: ";
		cin >> object.c;
		file.write(reinterpret_cast<char*>(&object), sizeof(Element<T1, T2, T3>));

		cout << "\nAdd another subscriber? 1 - Yes, 0 - No: ";
		cin >> choice;
		cout << endl;
		++this->count;
	} while (choice == 1);
	file.close();
}

template <typename T1, typename T2, typename T3>
void TextFile<T1, T2, T3>::sortData() {
	FILE* f = std::fopen(this->fileName, "r+");
	Element<string, int,string> left, right;
	for (int i = 0; i < count; i++)
	{
		std::fseek(f, i * (sizeof(Element<T1, T2, T3>)), SEEK_SET);
		std::fread(&left, sizeof(Element<T1, T2, T3>), 1, f);

		for (int j = count - 1; j > i; j--)
		{
			std::fseek(f, j * (sizeof(Element<T1, T2, T3>)), SEEK_SET);
			std::fread(&right, sizeof(Element<T1, T2, T3>), 1, f);
			if (left.year > right.year)
			{
				std::fseek(f, j * (sizeof(Element<T1, T2, T3>)), SEEK_SET);
				std::fwrite(&left, sizeof(Element<T1, T2, T3>), 1, f);
				std::fseek(f, i * (sizeof(Element<T1, T2, T3>)), SEEK_SET);
				std::fwrite(&right, sizeof(Element<T1, T2, T3>), 1, f);
				left = right;
			}
		}
	}
	std::fclose(f);
}

template <typename T1, typename T2, typename T3>
void TextFile<T1, T2, T3>::showData() {
	cout << setw(40) << "\nList of available subscriber\n" << endl;
	FILE* f;
	Element<T1, T2, T3> object;
	f = std::fopen(this->fileName, "rb");
	cout << setw(15) << "Имя" << setw(15) << "Класс музыкального инструмента" << setw(15) << "Страна" << setw(15) << "Возраст" << setw(15)<<"Занятое место"<< setw(15)<< endl;
	for (int i = 0; i < count; i++) {
		std::fread(&object, sizeof(Element<T1, T2,T3>), 1, f);
		cout  << setw(15) << object.firstName << setw(15) << object.klas << setw(15) << object.counture<< setw(15) << object.year<< setw(15)<< object.c<< setw(15)<< endl;
	}
	cout << endl;
	std::fclose(f);
}

int main()
{
	setlocale(LC_ALL, "Russian");
	TextFile< char,int,char>* example = new TextFile< char,int,char>();
	int choice;

	cout << "1 - Input; 2 - Display; 3 - Sorting by year; 4 - exit" << endl;
	cout << "\nYour choice: ";
	cin >> choice;

	while (choice >= 1 & choice <= 3) {
		switch (choice)
		{
		case 1: {
			example->setData();
			break;
		}
		case 2: {
			example->showData();
			break;
		}
		case 3:
			example->sortData();
			cout << setw(40) << "The result of sorting" << endl;
			example->showData();
			break;
		}
		cout << "Your choice: ";
		cin >> choice;
	}

	system("pause");
}