#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;



struct date_of_birth {//структура для данных даты рождения 
	int day, month, year;
};

//функция превода строки в дату
date_of_birth str_to_date(string str) {
	date_of_birth date;
	date.day = (str[0] - '0') * 10 + str[1] - '0';
	date.month = (str[3] - '0') * 10 + str[4] - '0';
	date.year = (str[6] - '0') * 1000 + (str[7] - '0') * 100 +
		(str[8] - '0') * 10 + str[9] - '0';
	return date;
}


struct people_info {//структура для всех данных считываемых из файла
	string surname, post;//фамилия, должность
	date_of_birth date;//дата рождения
	double work_experience;//опыт работы
	int salary;//зарплата
};


struct list {
	people_info inf;
	list* next = NULL;
	list* prev = NULL;
};


void push_back(list*& head, list*& tail, people_info value) {
	list* new_cell = new list;//создали новый элемент
	new_cell->inf = value;//присвоили ему значение;
	if (!head && !tail) {//если список пуст
		new_cell->prev = NULL;// предыдущий пустой 
		head = new_cell;//делаем новый элемент головой
	}
	else {
		tail->next = new_cell;//делаем новый элемент следующим после хвоста
		new_cell->prev = tail;//хвост - предыдущий элемент для нового элемента
	}
	tail = new_cell;//делаем новый элемент хвостом
}


void insert_after(list*& head, list*& tail, list* after_this, people_info value) {
	list* temp = new list;//новый элемент
	temp->inf = value;//присваиваем значение
	//если вставляем после хвоста
	if (after_this == tail) {
		temp->next = NULL;//вставляемый элемент будет последним
		tail->next = temp;//делаем связи между хвостом и последним элементом
		temp->prev = tail;
		tail = temp;//ставим указатель на хвост на последний элемент
	}
	else {
		//для temp следующий элемент это следующий за after_this
		temp->next = after_this->next;
		//для temp предыдущий after_this
		temp->prev = after_this;
		//для следуещего за after_this элемента предыдущий temp
		after_this->next->prev = temp;
		//для after_this следующий 
		after_this->next = temp;
	}
}
