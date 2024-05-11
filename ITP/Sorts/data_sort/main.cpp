#include <iostream>
#include <string>
#include <vector>
#include <fstream>
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


vector<people_info> create_vec_info() {//создание массива с входными данными
	vector<people_info> vec_info;
	//переменная структура для хранения данных на одного пользователя,
	//чтобы засунуть их в массив со всеми пользователями
	people_info temp;
	ifstream input;//создаем поток
	input.open("input.txt");//открываем файл на чтение
	//ввод данных
	while (input.peek() != EOF) {
		input >> temp.surname;//ввод фамилии
		input >> temp.post;//ввод должности
		string str;
		input >> str;//вводится дата рождения строкой
		temp.date = str_to_date(str);//преобразование строки с датой в структуру даты
		input >> temp.work_experience;//ввод стажа
		input >> temp.salary;//ввод зарплаты
		vec_info.push_back(temp);//добавляем данные человека в массив
	}
	input.close();//закрываем файл
	return vec_info;//возвращаем массив с данными о людях
}


void output_f(vector<people_info> vec_info,int number_task) {//вывод в файл
	people_info temp;
	ofstream output;
	output.open("output"+to_string(number_task)+".txt");
	for (int i = 0; i < vec_info.size(); i++) {
		//по левому краю 13 позиций на фамилию 
		//(чтобы у всех фамилий было одинаковое кол-во занимаемого места)
		output << setw(13) << left << vec_info[i].surname;
		//выводим должность
		output << setw(15) << left << vec_info[i].post;
		//выводим дату рождения
		//если дней меньше 10 то добавляем 0 перед цифрой 
		//и так же для месяца
		if (vec_info[i].date.day < 10) {
			output << left << '0' << vec_info[i].date.day << '.';
		}
		else {
			output << left << vec_info[i].date.day << '.';
		}
		if (vec_info[i].date.month < 10) {
			output << left << '0' << vec_info[i].date.month << '.';
		}
		else {
			output << left << vec_info[i].date.month << '.';
		}
		output << left << vec_info[i].date.year << ' ';
		//выводим стаж
		output << setw(2) << left << vec_info[i].work_experience << ' ';
		//выводим зарплату
		output << left << vec_info[i].salary << endl;
	}
}


void quicksort(vector<people_info> &vec_info, int left_i, int right_i) {
	int l = left_i, r = right_i;
	people_info middle = vec_info[(l + r) / 2];
	//пока левый указатель не ушел правее правого
	while (l <= r) {
		//пока значение в левом указателе меньше чем значение в середине 
		//двигаем левый указатель вправо
		while (vec_info[l].salary < middle.salary) {
			l++;
		}
		//пока значение в правом указателе больше чем значение в середине 
		//двигаем правый указатель влево
		while (vec_info[r].salary > middle.salary) {
			r--;
		}

		if (l <= r) {
			swap(vec_info[l], vec_info[r]);
			l++;
			r--;
		}
	}
	if (r > left_i) {//если правый указатель не дошел до левой границы, то сортируем еще
		quicksort(vec_info, left_i, r);
	}
	if (l < right_i) {//если левый указатель не дошел до правой границы, то сортруем еще
		quicksort(vec_info, l, right_i);
	}
}


void task_1() {
	//создание массива под данные о людях 
	vector<people_info> vec_info;
	//ввод данных в массив
	vec_info = create_vec_info();
	//быстрая сортировка по зарплате 
	quicksort(vec_info, 0, vec_info.size() - 1);
	//вывод данных в новый файл output1.txt
	output_f(vec_info, 1);
}


void gnome_sort(vector<people_info>& vec_info, int vec_size) {
	int i = 1;
	while (i < vec_size) {//пока не дошли до последнего
		if (i == 0) {//если дошли до первого элемента то i++
			i++;
		}
		//если предыдущий элемент меньше по должности или 
		//(равен по должности и меньше или равен по зарплате) то не меняя идем к следущей паре
		//тк эти два элемента отсортированы
		if (vec_info[i - 1].post < vec_info[i].post || 
			(vec_info[i - 1].post == vec_info[i].post &&
			vec_info[i - 1].salary <= vec_info[i].salary)) {
			i++;
		}
		else {//иначе меняем местами и идем к предыдущей паре
			swap(vec_info[i - 1], vec_info[i]);
			i--;
		}
	}
}


void task_2() {
	//создание массива под данные о людях 
	vector<people_info> vec_info;
	//ввод данных в массив
	vec_info = create_vec_info();
	//гномья сортировка сначала по должности, потом по зарплате
	gnome_sort(vec_info, vec_info.size());
	//вывод данных в новый файл output2.txt
	output_f(vec_info, 2);
}


void insert_sort(vector<people_info>& vec_info, int vec_size) {
	for (int i = 1; i < vec_size; i++) {//проходимся по массиву данными 
		int j = i;
		//пока j не вернулось в начало и проходит одно из условий показывающее, что 
		//эти два элемента не отсортированны
		//меняем их местами и идем к следующей паре элементов
		while (j > 0 && (vec_info[j].surname < vec_info[j - 1].surname ||
			(vec_info[j].surname == vec_info[j - 1].surname &&
				vec_info[j].work_experience < vec_info[j - 1].work_experience) ||
			(vec_info[j].surname == vec_info[j - 1].surname &&
				vec_info[j].work_experience == vec_info[j - 1].work_experience &&
				vec_info[j].date.year < vec_info[j - 1].date.year))) {
			swap(vec_info[j], vec_info[j - 1]);//замена
			j--;//шаг назад
		}
	}
}


void task_3() {
	//создание массива под данные о людях 
	vector<people_info> vec_info;
	//ввод данных в массив
	vec_info = create_vec_info();
	//сортировка вставками сначала по фамилии, потом по стажу работы, потом по году рождения
	insert_sort(vec_info, vec_info.size());
	//вывод данных в новый файл output2.txt
	output_f(vec_info, 3);

}


int main(){
	task_3();
}