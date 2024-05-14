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


void change_1(stack*& head) {
	stack* vowel = NULL;//буферный стек для гласных 
	stack* consonant = NULL;//буферный стек для согласных

	while (head) {
		//если гласная, то добавляем в vowel
		if (tolower((head->inf)[0]) == 'e' || tolower((head->inf)[0]) == 'y' ||
			tolower((head->inf)[0]) == 'u' || tolower((head->inf)[0]) == 'i' ||
			tolower((head->inf)[0]) == 'o' || tolower((head->inf)[0]) == 'a') {
			push_back(vowel, pop(head));//удаляем с головы head и добавляем в vowel
		}
		//иначе добавляем в consonat 
		else {
			push_back(consonant, pop(head));//удаляем с головы head и добавляем в consonant
		}
	}
	head = consonant;//переобозначили указатели
	reverse(vowel);//перевернули стек с гласными
	while (vowel) {//добавили 
		push_back(head, pop(vowel));
	}
}


void task_1() {
	setlocale(LC_ALL, "RUS");
	stack* numbers = NULL;
	int len;
	cout << "Введите кол-во элементов: " << endl;
	cin >> len;
	string x;
	cout << "Введите элементы: " << endl;
	for (int i = 0; i < len; i++) {
		cin >> x;//ввели x
		push_back(numbers, x);//добавили x в конец
	}
	//поставили гласные в начало, согласные в конец 
	//так чтобы порядок следования совпадал с первоначальным
	change_1(numbers);
	//вывод ответа
	cout << "Ответ:" << endl;
	for (int i = 0; i < len; i++) {
		cout << pop(numbers) << " ";
	}
}


/*
test:
12
q w e r t u i o p s d a

 e u i o a q w r t p s d.
*/


int main() {
	task_1();
}