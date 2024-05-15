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


void insert_after(list*& head, list*& tail, list* after_this, int value) {
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


void del_list(list*& head, list*& tail) {
	//пока не дошли до конца
	while (head) {
		list* temp = head;//создали доп указатель на голову
		if (head != tail) {
			head = head->next;//двигаем голову на следующий элемент
			head->prev = NULL;//обнуляем указатель на предыдущий элемент
			delete temp;//удаляем элемент
		}
		else {
			head = tail = NULL;
			break;
		}
	}
}



/*
Создать список, содержащий целые числа.
После всех чисел, равных минимальному числу, вставить последний нечетный элемент.
Например, было  2 8 2 1 6 8 8 1 2 2 8 2 1 3
Стало  2 8 2 1 3 6 8 8 1 3 2 2 8 2 1 3
*/

void change_1(list*& head, list*& tail, int mmin, int last_odd) {
	list* temp = head;//создаем доп указатель на голову 
	while (temp != tail->next) {
		//если элемент на который указывает temp = mmin
		if (temp->inf == mmin) {
			//то добавляем last_odd (значение последнего нечетного элемента)
			insert_after(head, tail, temp, last_odd);
			temp = temp->next;//сдвигаем указатель
		}
		temp = temp->next;//сдвигаем указатель
	}
}


void task_1() {
	setlocale(LC_ALL, "RUS");
	list* mas_head = NULL;//создали два указателя для списка
	list* mas_tail = NULL;
	int len;
	cout << "Введите кол-во элементов списка:" << endl;
	cin >> len;
	int mmin, last_odd;
	cout << "Введите элементы списка:" << endl;
	//заполняем массив
	for (int i = 0; i < len; i++) {
		int temp;
		cin >> temp;//ввод элемента
		push_back(mas_head, mas_tail, temp);//добавляем элемент в массив
		//находим минимальный элемент
		if (i == 0) {
			mmin = temp;//ставим первый элемент как минимальный
		}
		if (mmin > temp) {
			mmin = temp;
		}
		//находим последний нечетный элемент
		if (temp % 2 != 0) {
			last_odd = temp;
		}
	}
	//после каждого mmin ставим last_odd
	change_1(mas_head, mas_tail, mmin, last_odd);
	//вывод 
	cout << "Ответ:" << endl;
	print(mas_head, mas_tail);
	//удаление всего массива
	del_list(mas_head, mas_tail);
}
/*
test
14
2 8 2 1 6 8 8 1 2 2 8 2 1 3
*/

int main(){
    task_1();
}