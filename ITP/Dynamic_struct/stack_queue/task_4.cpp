#include <iostream>
#include <cmath>

using namespace std;


/*
Создать стек, содержащий целые числа.
Удалить все числа с максимальным количеством делителей.
Порядок следования в результате должен совпадать с порядком следования ввода.
Например, было 1 2 3 4 5 6 7 8 9.
Стало 1 2 3 4 5 7 8
(не понял почему удалилось 9 тк у них делителей меньше чем у 8)
*/

struct stack {
	int inf;
	stack* next;
};


void push_back(stack*& head, int value) {
	stack* new_cell = new stack;// создаем новый элемент
	new_cell->inf = value;//добавляем значение в поле нового элемента
	//делаем связь за новым элементом идет предыдущая голова
	//у новой головы следующим элементом идет предыдущая голова
	new_cell->next = head;
	head = new_cell;//делаем новый элемент головой
}


int pop(stack*& head) {
	int value;//переменная для вывода значения головы
	value = head->inf;//присваиваем значение головы
	stack* delete_cell;//создаем доп указатель
	delete_cell = head;//ставим этот указатель на голову
	head = head->next;//голову переносим на следующий элемент
	delete delete_cell;//удаляем первый элемент
	return value;//возвращаем значение удаленного элемента
}

//функция для нахождение кол-ва делителей числа 
int all_divisors(int number) {
	int sqrt_ = int(sqrt(number)) + 1;
	int counter = 0;

	for (int i = 1; i < sqrt_; i++) {
		if (number % i == 0) {
			counter++;
			if (i * i != number) {
				counter++;
			}
		}
	}

	return counter;
}


void change_4(stack*& head, int mmax, int& len) {
	stack* buffer_ = NULL;//создаем буферный стек
	len = 0;
	while (head) {
		//удаляем элемент и записываем его значение 
		int x = pop(head);
		//если кол-во делителей x меньше максимального кол-ва, то
		//добавляем элемент в буферный стек
		if (all_divisors(x) < mmax) {
			push_back(buffer_, x);
			len++;
		}
	}
	//переобозначение указателей
	head = buffer_;
}


void task_4() {
	setlocale(LC_ALL, "RUS");
	stack* numbers = NULL;
	int len;
	cout << "Введите кол-во элементов: " << endl;
	cin >> len;
	int x, mmax = 0;
	cout << "Введите элементы: " << endl;
	for (int i = 0; i < len; i++) {
		cin >> x;//ввели x
		//находим кол-во делителей x
		int divisors = all_divisors(x);
		//находим максимальное кол-во делителей элемнтов стека
		if (divisors > mmax) {
			mmax = divisors;
		}
		push_back(numbers, x);//добавили x в конец
	}

	change_4(numbers, mmax, len);
	//вывод ответа
	cout << "Ответ:" << endl;
	for (int i = 0; i < len; i++) {
		cout << pop(numbers) << " ";
	}
}


/*
9

1 2 3 4 5 6 7 8 9
*/


int main() {
	task_4();
}