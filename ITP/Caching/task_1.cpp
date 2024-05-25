#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;



struct date_of_birth {//структура для данных даты рождения 
	int day, month, year;
};

//функция превода строки в дату
date_of_birth str_to_date(string str) {
	date_of_birth date;
	date.day = (str[0] - '0') * 10 + str[1] - '0';
	date.month = (str[3] - '0') * 10 + str[4] - '0';
	date.year = (str[6] - '0') * 1000 + (str[7] - '0') * 100 +
		(str[8] - '0') * 10 + str[9] - '0';
	return date;
}


struct people_info {//структура для всех данных считываемых из файла
	string surname, post;//фамилия, должность
	date_of_birth date;//дата рождения
	double work_experience;//опыт работы
	int salary;//зарплата
};


struct list {
	people_info inf;
	list* next = NULL;
	list* prev = NULL;
};


void push_back(list*& head, list*& tail, people_info value) {
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


void insert_after(list*& head, list*& tail, list* after_this, people_info value) {
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


//ввод из файла
people_info input_f(ifstream& input){
	people_info temp;
	string str;

	input >> temp.surname;//ввод фамилии
	input >> temp.post;//ввод должности
	input >> str;//вводится дата рождения строкой
	temp.date = str_to_date(str);//преобразование строки с датой в структуру даты
	input >> temp.work_experience;//ввод стажа
	input >> temp.salary;//ввод зарплаты

	return temp;
}


//ввод из терминала
people_info input_t(){
	people_info temp;
	string str;

	cin >> temp.surname;//ввод фамилии
	cin >> temp.post;//ввод должности
	cin >> str;//вводится дата рождения строкой
	temp.date = str_to_date(str);//преобразование строки с датой в структуру даты
	cin >> temp.work_experience;//ввод стажа
	cin >> temp.salary;//ввод зарплаты

	return temp;
}


//вывод в файл
void output_f(ofstream& output, list* temp) {//вывод в файл
	//по левому краю 13 позиций на фамилию 
	//(чтобы у всех фамилий было одинаковое кол-во занимаемого места)
	output << setw(13) << left << temp->inf.surname;
	//выводим должность
	output << setw(15) << left << temp->inf.post;
	//выводим дату рождения
	//если дней меньше 10 то добавляем 0 перед цифрой 
	//и так же для месяца
	if (temp->inf.date.day < 10) {
		output << left << '0' << temp->inf.date.day << '.';
	}
	else {
		output << left << temp->inf.date.day << '.';
	}
	if (temp->inf.date.month < 10) {
		output << left << '0' << temp->inf.date.month << '.';
	}
	else {
		output << left << temp->inf.date.month << '.';
	}
	output << left << temp->inf.date.year << ' ';
	//выводим стаж
	output << setw(2) << left << temp->inf.work_experience << ' ';
	//выводим зарплату
	output << left << temp->inf.salary << endl;
}


int cache_function(int salary, int size){
	return salary % size;
}


void create_cache_table(ifstream& input, vector<pair<list*,list*>>& cache_table, int size){
	while (input.peek() != EOF){
		//создаем буферную структуру для входных данных человека
		people_info temp;
		//считываем данные одного человека 
		temp = input_f(input);
		//определяем значение хеш функции
		int number = cache_function(temp.salary, size);
		//добавляем данные по человеку в список хеш таблицы под номером number
		push_back(cache_table[number].first, cache_table[number].second, temp);
	}
}


list* find_open_cache(vector<pair<list*, list*>> cache_table, people_info man, int size){
	//определяем значение хеш функции
	int number = cache_function(man.salary, size);
	//проходимся по списку хеш таблицы соответствующему значению хеш функции 
	for (auto it = cache_table[number].first; it != cache_table[number].second; it->next){
		//ищем нужного человека
		if ((it->inf).surname == man.surname){
			if((it->inf).post == man.post &&
				(it->inf).date.year == man.date.year &&
				(it->inf).work_experience == man.work_experience &&
				(it->inf).salary == man.salary){
				//возвращаем указатель на человека если нашли
				return it;
			}
		}
	}
	//если не нашли возвращаем NULL
	return NULL;
}


void open_cache(){
	setlocale(LC_ALL,"RUS");
	//создаем потоки на ввод и ввывод
	ifstream input;
	ofstream output;
	int size = 28;
	input.open("input.txt");
	output.open("output_1.txt");
	//создаем и заполняем хэш таблицу
	vector<pair<list*,list* >> cache_table(size);
	create_cache_table(input, cache_table, size);

	//вывод таблицы
	for (int i = 0; i < size; i++){
		output << i << ":" << endl;
		list* temp = cache_table[i].first;
		while (temp){
			output_f(output, temp);
			temp = temp->next;
		}
	}
	//закрываем поток
	input.close();
	output.close();

	//вводим данные человека, которого ходтим найти
	cout << "Введите данные человека, которого хотите найти:" << endl;
	people_info man;
	man = input_t();
	//поиск 
	list* man_f = find_open_cache(cache_table, man, size);
	//вывод указателя
	cout << man_f << endl;
}


int main(){
	open_cache();
}