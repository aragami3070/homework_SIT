#include <iostream>


using namespace std;

struct list {
	int inf;
	list* next;
	list* prev;
};

void push_back(list*& head, list*& tail, int value) {
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


void print(list*& head, list*& tail) {
	list* temp = head;//доп указатель на голову
	while (temp != tail->next && temp != NULL) {//пока не дошли до конца
		//вывод значения элемента на котором находится указатель temp
		cout << temp->inf << " ";
		//передвигаем указатель на следующий элемент
		temp = temp->next;
	}
	cout << endl;
}
