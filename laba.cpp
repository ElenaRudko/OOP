#include <stdlib.h>
#include <iostream>

using namespace std;


template<typename T>//шаблон
class Node                             //Структура, являющаяся звеном списка
{
public:
	T x;                             //Значение x будет передаваться в список
	Node* Next, *Prev;                 //Указатели на адреса следующего и предыдущего элементов списка
};


class MyExeption : public exception
{
public:
	MyExeption(const char* msg, int dataState) : exception(msg)
	{
		this->dataState = dataState;
	}

	int getDataState()
	{
		return dataState;
	}
private:
	int dataState = 0;
};

template<typename T>
class List                              //Создаем тип данных Список
{
	int count = 0;
	Node<T>* Head, *Tail;                 //Указатели на адреса начала списка и его конца
public:
	List() :Head(NULL), Tail(NULL) {};    //Инициализируем адреса как пустые
	~List();                           //Прототип деструктора
	void Show();                       //Прототип функции отображения списка на экране
	void Add(int x);                   //Прототип функции добавления элементов в список
	void sort();
	void del();
	void find();//Прототип функции поиска элементов в список
};


template<typename T>
List<T>::~List()                           //Деструктор
{
	while (Head)                       //Пока по адресу на начало списка что-то есть
	{
		Tail = Head->Next;             //Резервная копия адреса следующего звена списка
		delete Head;                   //Очистка памяти от первого звена
		Head = Tail;                   //Смена адреса начала на адрес следующего элемента
	}
}

template<typename T>
void List<T>::Add(int x)
{
	this->count++;//указатель на объект
	Node<T>* temp = new Node<T>;               //Выделение памяти под новый элемент структуры
	temp->Next = NULL;                   //Указываем, что изначально по следующему адресу пусто
	temp->x = x;                         //Записываем значение в структуру
	//cout << " hui" << temp->x;
	if (Head != NULL)                    //Если список не пуст
	{
		temp->Prev = Tail;               //Указываем адрес на предыдущий элемент в соотв. поле
		Tail->Next = temp;               //Указываем адрес следующего за хвостом элемента
		Tail = temp;                     //Меняем адрес хвоста
	}
	else //Если список пустой
	{
		temp->Prev = NULL;               //Предыдущий элемент указывает в пустоту
		Head = Tail = temp;              //Голова=Хвост=тот элемент, что сейчас добавили
	}
}

template<typename T>
void List<T>::sort()
{
	int n;
	cout << "1 - по убыванию; 2 - по возрастанию\nваш выборr: ";
	cin >> n;
	if (this->Head == NULL) {
		throw MyExeption("Массив пустой", 0);//обработка исключений
	}

	for (Node<T>* i = Head; i; i = i->Next) {
		for (Node<T>* j = Head; j; j = j->Next) {
			//В зависимости от указанного направления
			if (n == 1) {
				if (i->x > j->x) {
					//Произведем обмен контейнера списка
					int r = i->x;
					i->x = j->x;
					j->x = r;
				}
			}
			else if (n == 2) {
				if (i->x < j->x) {
					//Произведем обмен контейнера списка
					int r = i->x;
					i->x = j->x;
					j->x = r;
				}
				else cout << "Неверный ввод\n";
			}

		}
	}
	this->Show();
}

template<typename T>
void List<T>::del()
{
	this->Show();
	int n;
	cout << "\nВведите номер элемента, который нужно удалить': ";
	cin >> n;
	if (n <= 0 || n > count)
	{
		throw MyExeption("Выход за пределы массива", n);
	}
	if ((n == 1) and (Head->Next)) {
		Node<T>* temp = Head;
		Head = Head->Next;
		Head->Prev = NULL;
		delete temp;
		this->count--;
		return;
	}
	else if ((n == 1) and (Head == Tail)) {

		Head->Next = NULL;
		Head = NULL;
		delete Head;
		this->count = 0;
		return;


		if (n == this->count) {
			Node<T>* temp = Tail;
			Tail = Tail->Prev;
			Tail->Next = NULL;
			delete temp;
			this->count--;
			return;
		}


		Node<T>* temp = Head, *temp2;
		for (int i = 0; i < n - 1; i++)
		{
			temp = temp->Next;
		}
		temp2 = temp;
		temp2->Prev->Next = temp->Next;
		temp2->Next->Prev = temp->Prev;
		delete temp;

		this->count--;
	}
}

template<typename T>
void List<T>::Show()
{
	//ВЫВОДИМ СПИСОК С КОНЦА
	Node<T>* temp = Tail;                   //Временный указатель на адрес последнего элемента
	//ВЫВОДИМ СПИСОК С НАЧАЛА
	temp = Head;                       //Временно указываем на адрес первого элемента
	while (temp != NULL)              //Пока не встретим пустое значение
	{
		cout << temp->x << " ";        //Выводим каждое считанное значение на экран
		temp = temp->Next;             //Смена адреса на адрес следующего элемента
	}
	cout << "\n";
}

template<typename T>
void List<T>::find()
{
	int n, idx = 0;;
	try {
		cout << "\nВведите элемент, который нужно найти: ";
		cin >> n;
		Node<T>* res = Head;
		while (res != NULL) {
			idx++;
			if (res->x == n) {
				cout << "Номер элемента: " << idx << "\n";
				break;
			}
			else
				res = res->Next;
		}
	}
	catch (exception ex)
	{

		cout << "Номер элемента ne naiden " << endl;
		//count << ex.what() << endl;


	}
}

int menu() {
	cout << "Меню:\n";
	cout << "1. Добавить\n";
	cout << "2. Удалить\n";
	cout << "3. Найти\n";
	cout << "4. Сортировка\n";
	cout << "5. Просмотр\n";
	cout << "6. Выход\n";
	int ch;
	cin >> ch;
	return ch;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	bool flag = true;
	List<int> lst; //Объявляем переменную, тип которой есть список
	while (flag) {
		switch (menu())
		{
		case 1:
			try
			{
				int x;
				cout << "Введите данные: ";
				cin >> x;
				if (std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(32767, '\n');
					lst.Add(rand() % 10);
					throw 1;
				}
				else
				{
					lst.Add(x);
				}

			}
			catch (...)
			{
				cout << "ERROR INPUT" << endl;
			}
			break;
		case 2:
			try
			{
				lst.del();
			}
			catch (MyExeption &ex)
			{
				cout << "Мы поймали исключение " << ex.what() << endl;
				cout << "Состояние данных " << ex.getDataState() << endl;
			}
			break;//удаление
		case 3:
			try
			{
				lst.find();
			}
			catch (MyExeption &ex)
			{
				cout << "Мы поймали исключение " << ex.what() << endl;
				cout << "Состояние данных " << ex.getDataState() << endl;
			}
			break;//найти
		case 4:
			try
			{
				lst.sort();
			}
			catch (MyExeption& ex)
			{
				cout << "Мы поймали исключение " << ex.what() << endl;
				cout << "Состояние данных " << ex.getDataState() << endl;
			}
			break;//сортировка
		case 5: lst.Show(); break;//показать
		case 6: flag = false; break;
		default: break;
		}
		system("PAUSE");
	}
	return 0;
}