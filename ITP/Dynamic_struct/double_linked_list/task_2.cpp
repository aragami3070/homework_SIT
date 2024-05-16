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