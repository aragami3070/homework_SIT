#include <iostream>


using namespace std;

/*
Создать очередь, содержащую целые числа.
После всех чисел, равных первому числу, вставить максимальный элемент.
Например, было  2 8 2 1 6 8 8 1 2 2 8 2 1.
Стало   2 8 8 2 8 1 6 8 8 1 2 8 2 8 8 2 8 1
*/

struct queue {
	int inf;
	queue* next;
};


void push_back(queue*& head, queue*& tail, int value) {
	queue* new_cell = new queue;// создаем новый элемент
	new_cell->inf = value;//добавляем значение в поле нового элемента
	new_cell->next = NULL;//новый элемент всегда последний
	if (!head && !tail) {//если очередь пуста, то 
		//новый элемент и голова и хвост
		head = tail = new_cell;
	}
	else {
		tail->next = new_cell;//новый элемент следующий для хвоста
		tail = new_cell;//теперь новый элемент это хвост
	}
}


int pop(queue*& head, queue*& tail) {
	int value;//переменная для вывода значения головы
	value = head->inf;//присваиваем значение головы
	queue* delete_cell;//создаем доп указатель 
	delete_cell = head;//ставим этот указатель на голову
	head = head->next;//голову переносим на следующий элемент
	if (!head) {//если удаляем последний элемент из очереди
		tail = NULL;
	}
	delete delete_cell;//удаляем первый элемент
	return value;//возвращаем значение удаленного элемента
}
