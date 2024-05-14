#include <iostream>


using namespace std;

/*
Создать очередь из целых чисел.
Удалить все повторяющиеся элементы, оставив только их первые вхождения.
Например, было 1 2 2 1 3 4 5 1 2 5 4 3 5.
Стало 1 2 3 4 5.
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


void change_3(queue*& head, queue*& tail, int& len) {
	queue* res_head = NULL;//очередь для результата(голова)
	queue* res_tail = NULL;//очередь для результата(хвост)
	len = 0;//сбрасываем длину очерди
	while (head) {
		queue* buffer_head = NULL;//буферная очередь(голова)
		queue* buffer_tail = NULL;//буферная очередь(хвост)
		//удаляем элемент и записываем его значение 
		int x = pop(head, tail);
		while (head) {
			//добавляем все элементы не равные x в буферную очередь
			int y = pop(head, tail);
			if (x != y) {
				push_back(buffer_head, buffer_tail, y);
			}
		}
		//переобозначаем указатели
		head = buffer_head;
		tail = buffer_tail;
		//добавляем не повторяющийся элемент в очередь для результата
		push_back(res_head, res_tail, x);
		//увеличиваем длину очереди
		len++;
	}
	//переобозначаем указатели
	head = res_head;
	tail = res_tail;
}


void task_3() {
	setlocale(LC_ALL, "RUS");
	queue* numbers_head = NULL;
	queue* numbers_tail = NULL;
	int len;
	cout << "Введите кол-во элементов: " << endl;
	cin >> len;
	int x;
	cout << "Введите элементы: " << endl;
	for (int i = 0; i < len; i++) {
		cin >> x;//ввели x
		push_back(numbers_head, numbers_tail, x);//добавили x в конец
	}
	//убрали все повторяющиеся, оставив только первое вхождение
	change_3(numbers_head, numbers_tail, len);
	//вывод ответа
	cout << "Ответ:" << endl;
	for (int i = 0; i < len; i++) {
		cout << pop(numbers_head, numbers_tail) << " ";
	}
}


/*
13

1 2 2 1 3 4 5 1 2 5 4 3 5
*/


int main() {
	task_3();

}