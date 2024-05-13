#include <iostream>
#include <string>


using namespace std;
/*
Создать стек, содержащий буквы латинского алфавита. 
В новый стек записать сначала гласные, потом согласные буквы. 
Порядок следования букв в новом стеке должен совпадать с первоначальным. 
Например, было q, w, e, r, t, u, i, o, p, s, d, a.  
Cтало  e, u, i, o, a, q, w, r, t, p, s, d.
*/

struct stack {
	string inf;
	stack* next;
};


void push_back(stack*& head, string value) {
	stack* new_cell = new stack;// создаем новый элемент
	new_cell->inf = value;//добавляем значение в поле нового элемента
	//делаем связь за новым элементом идет предыдущая голова
	//у новой головы следующим элементом идет предыдущая голова
	new_cell->next = head;
	head = new_cell;//делаем новый элемент головой
}


string pop(stack*& head) {
	string value;//переменная для вывода значения головы
	value = head->inf;//присваиваем значение головы
	stack* delete_cell;//создаем доп указатель
	delete_cell = head;//ставим этот указатель на голову
	head = head->next;//голову переносим на следующий элемент
	delete delete_cell;//удаляем первый элемент
	return value;//возвращаем значение удаленного элемента
}



void reverse(stack*& head) {
	stack* buffer = NULL;//буферный стек
	//пока стек не пуст (проходимся по стеку)
	while (head) {
		//перезаписываем из одного стека в другой
		push_back(buffer, pop(head));
	}
	head = buffer;//переобозначаем указатели
}

