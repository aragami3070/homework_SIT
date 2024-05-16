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


void del_elem(list*& head, list*& tail, list* del_this) {
	//если один элемент в списке то 
	if (head == tail) {
		//head и tail обнуляем
		head = tail = NULL;
	}
	//если удаляем голову  
	else if (head == del_this) {
		//то сдвигаем указатель на голову на следующий элемент
		head = head->next;
		//обнуляем указатель на предыдущий
		head->prev = NULL;
	}
	//если удаляем хвост
	else if (tail == del_this) {
		//то сдвигаем указатель на хвост на предыдущий элемент
		tail = tail->prev;
		//обнуляем указатель на следующий элемент
		tail->next = NULL;
	}
	//удаляем из середины
	else {
		//у элемента после удаляемого предыдущий = элементу перед удалемым
		(del_this->next)->prev = del_this->prev;
		//у элемента перед удаляемым следующий = элементу после удалемого
		(del_this->prev)->next = del_this->next;
	}

	delete del_this;
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
Создать двусвязный список, содержащий целые числа.
Перенести в начало списка числа, меньшие Х.
Например, было 8 2 1 6 3 5 4 2 1 8 9 7 и Х = 5
стало 2 1 3 4 2 1 8 6 5 8 9 7
*/

void change_2(list*& head, list*& tail, int x) {
	list* temp = head;//создаем два доп указателя
	list* l_end = tail;
	//пока не дошли до конца 
	while (temp) {
		//если элемент на который указывает temp >= x 
		if (temp->inf >= x) {
			//добавляем в конец temp и удаляем  элемент на который указывает temp
			push_back(head, tail, temp->inf);//добавляем в конец
			list* temp1 = temp;//доп указатель на temp
			temp = temp->next;//передвигаем основной temp
			//если это последний элемент изначального массива, то удалить элемент и прервать цикл
			if (temp1 == l_end) {
				del_elem(head, tail, temp1);
				break;
			}
			//иначе только удалить 
			else {
				del_elem(head, tail, temp1);
			}
		}
		else {
			//если это последний элемент изначального массива, то прервать цикл
			if (temp == l_end) {
				break;
			}
			temp = temp->next;//передвигаем указатель
		}
	}
}


void task_2() {
	setlocale(LC_ALL, "RUS");
	list* mas_head = NULL;//создали два указателя для списка
	list* mas_tail = NULL;
	int len;
	cout << "Введите кол-во элементов списка:" << endl;
	cin >> len;
	cout << "Введите элементы списка:" << endl;
	//заполняем массив
	for (int i = 0; i < len; i++) {
		int temp;
		cin >> temp;//ввод элемента
		push_back(mas_head, mas_tail, temp);//добавляем элемент в массив
	}
	int x;
	cout << "Введите x:" << endl;
	cin >> x;
	//все что меньше x оставляем слева, остальное переносим вправо
	change_2(mas_head, mas_tail, x);
	//вывод 
	cout << "Ответ:" << endl;
	print(mas_head, mas_tail);
	//удаление всего массива
	del_list(mas_head, mas_tail);
}

/*
test
12

8 2 1 6 3 5 4 2 1 8 9 7

5
*/

int main(){
    task_2();
}