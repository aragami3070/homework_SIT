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


void change_2(queue*& head, queue*& tail, int mmax, int first_in, int& len) {
	queue* buffer_head = NULL;//буферная очередь(голова)
	queue* buffer_tail = NULL;//буферная очередь(хвост)
	while (head) {
		//удаляем элемент и записываем его значение 
		int x = pop(head, tail);
		//добавляем удаленный элемент в буферную очередь
		push_back(buffer_head, buffer_tail, x);
		//если этот элемент равен первому, то добавляем в буферную очередь mmax
		if (x == first_in) {
			push_back(buffer_head, buffer_tail, mmax);
			len++;
		}
	}
	//переобозначаем указатели
	head = buffer_head;
	tail = buffer_tail;
}


void task_2() {
	setlocale(LC_ALL, "RUS");
	queue* numbers_head = NULL;
	queue* numbers_tail = NULL;
	int len;
	cout << "Введите кол-во элементов: " << endl;
	cin >> len;
	int x;
	cout << "Введите элементы: " << endl;
	int mmax, first_in;
	for (int i = 0; i < len; i++) {
		cin >> x;//ввели x
		if (i == 0) {
			mmax = x;//первый элемент изначально максимальный
			first_in = x;//первый введенный элемент 
		}
		if (x > mmax) {
			mmax = x;//если нашли больше, то новый максимум
		}
		push_back(numbers_head, numbers_tail, x);//добавили x в конец
	}
	//после всех чисел, равных первому числу, вставили максимальный элемент.
	change_2(numbers_head, numbers_tail, mmax, first_in, len);
	//вывод ответа
	cout << "Ответ:" << endl;
	for (int i = 0; i < len; i++) {
		cout << pop(numbers_head, numbers_tail) << " ";
	}
}


/*
test:
13

2 8 2 1 6 8 8 1 2 2 8 2 1
*/


int main() {
	task_2();
}