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


list* separation_by_last_element(list*& head, list*& tail, list* left_i, list* right_i) {
	int elem = right_i->inf;
	list* elem_it = left_i;//доп указатель на левую границу
	for (list* i = elem_it; i != right_i; i = i->next) {
		if (i->inf <= elem) {
			if(i!=elem_it){
				//меняем элементы местами через вставку в нужное место элемнта
				//и его удаление
				//вствили
				insert_after(head, tail, elem_it, i -> inf);
				insert_after(head, tail, i, elem_it -> inf);
				//предвинули указатель
				elem_it = elem_it -> next;
				i = i -> next;
				//доп указатель на элемнты которые надо удалить
				list* temp_el = elem_it -> prev;
				list* temp_i = i -> prev;
				//удалили
				del_elem(head, tail, temp_el);
				del_elem(head, tail, temp_i);
			}
			//сдвинули указатель
			elem_it = elem_it->next;
			
		}
	}
	
	if(elem_it!=right_i){
		//меняем элементы местами через вставку в нужное место элемнта
		//и его удаление
		//вствили
		insert_after(head, tail, elem_it, right_i -> inf);
		insert_after(head, tail, right_i, elem_it -> inf);
		//предвинули указатель
		elem_it = elem_it -> next;
		bool flag = false;
		if(right_i != tail){
			right_i = right_i -> next;
			flag = true;
		}
		
		//доп указатель на элемнты которые надо удалить
		list* temp_el = elem_it -> prev;
		list* temp_ri = right_i -> prev;
		//удалили
		del_elem(head, tail, temp_el);
		del_elem(head, tail, temp_ri);
		if (flag == true){
			right_i = right_i ->prev;
		}
	}
	return elem_it;
}


void quicksort(list*& head, list*& tail, list*& left_i, list*& right_i) {
	if (right_i != NULL && left_i != right_i && left_i != right_i->next){
		list * main_elem_it = separation_by_last_element(head, tail, left_i, right_i);
		quicksort(head, tail, left_i, main_elem_it->prev);
		quicksort(head, tail, main_elem_it->next, right_i);
	}
}