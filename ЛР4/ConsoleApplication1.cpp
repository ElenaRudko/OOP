﻿//#include "pch.h"
#include<iostream>
#include<fstream>
#include<iomanip>
#include<string.h>
#include <clocale>
#include <Windows.h>
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
	void sortData(int chose);
	//bool parametr(Element<T1, T2, T3> left, Element<T1, T2, T3> right, int chose);
	bool parametr(Element<string, int, string> left, Element<string, int, string> right, int chose);
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

		cout << "\nПродолжить? 1 - Да, 0 - Нет: ";
		cin >> choice;
		cout << endl;
		++this->count;
	} while (choice == 1);
	file.close();
}

template <typename T1, typename T2, typename T3>
void TextFile<T1, T2, T3>::sortData(int chose) {

	FILE* f = std::fopen(this->fileName, "r+");
	Element<string, int, string> left, right;
	for (int i = 0; i < count; i++)
	{
		std::fseek(f, i * (sizeof(Element<T1, T2, T3>)), SEEK_SET);
		std::fread(&left, sizeof(Element<T1, T2, T3>), 1, f);

		for (int j = count - 1; j > i; j--)
		{
			std::fseek(f, j * (sizeof(Element<T1, T2, T3>)), SEEK_SET);
			std::fread(&right, sizeof(Element<T1, T2, T3>), 1, f);
			if (parametr(left, right, chose))
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
bool TextFile<T1, T2, T3>::parametr(Element<string, int, string> left, Element<string, int, string> right, int chose)
{
	switch (chose)
	{
	case 1: return left.firstName[0] > right.firstName[0] ? true : false;
	case 2: return left.klas[0] > right.klas[0] ? true : false;
	case 3: return left.counture[0] > right.counture[0] ? true : false;
	case 4: return left.year > right.year ? true : false;
	case 5: return left.c > right.c ? true : false;
	default: return left.firstName[0] > right.firstName[0] ? true : false;
	}
}

template <typename T1, typename T2, typename T3>
void TextFile<T1, T2, T3>::showData() {
	setlocale(LC_ALL, "Russian");
	cout << setw(40) << "\nПолученные данные\n" << endl;
	FILE* f;
	Element<T1, T2, T3> object;
	f = std::fopen(this->fileName, "rb");
	cout << setw(15) << "Имя" << setw(15) << "Класс музыкального инструмента" << setw(15) << "Страна" << setw(15) << "Возраст" << setw(15) << "Занятое место" << setw(15) << endl;
	for (int i = 0; i < count; i++) {
		setlocale(LC_ALL, "Russian");
		std::fread(&object, sizeof(Element<T1, T2, T3>), 1, f);
		cout << setw(15) << object.firstName << setw(15) << object.klas << setw(15) << object.counture << setw(15) << object.year << setw(15) << object.c << setw(15) << endl;
	}
	cout << endl;
	std::fclose(f);
}

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	TextFile< char, int, char>* example = new TextFile< char, int, char>();
	int choice;
	cout << "1 - Добавить; 2 - Просмотр; 3 - Сортировка по году рождения;4-Сортировка по имени; 5 - выход" << endl;
	cout << "\nВыберите: ";
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
			int chose;
			cout << "Выберите поле для сортировки 1-5" << endl;
			cin >> chose;
			example->sortData(chose);
			cout << setw(40) << "Результат сортировки" << endl;
			example->showData();
			break;
		}
		cout << "Выберите: ";
		cin >> choice;
	}

	system("pause");
}