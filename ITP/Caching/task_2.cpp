#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;



struct date_of_birth {//структура для данных даты рождения 
	int day = 0, month = 0, year = 0;
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
	string surname = " ", post = " ";//фамилия, должность
	date_of_birth date;//дата рождения
	double work_experience = 0.0;//опыт работы
	int salary = 0;//зарплата
};


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
void output_f(ofstream& output, people_info temp) {//вывод в файл
	//по левому краю 13 позиций на фамилию 
	//(чтобы у всех фамилий было одинаковое кол-во занимаемого места)
	output << setw(13) << left << temp.surname;
	//выводим должность
	output << setw(15) << left << temp.post;
	//выводим дату рождения
	//если дней меньше 10 то добавляем 0 перед цифрой 
	//и так же для месяца
	if (temp.date.day < 10) {
		output << left << '0' << temp.date.day << '.';
	}
	else {
		output << left << temp.date.day << '.';
	}
	if (temp.date.month < 10) {
		output << left << '0' << temp.date.month << '.';
	}
	else {
		output << left << temp.date.month << '.';
	}
	output << left << temp.date.year << ' ';
	//выводим стаж
	output << setw(2) << left << temp.work_experience << ' ';
	//выводим зарплату
	output << left << temp.salary << endl;
}


int cache_function(int year, int size){
	double coefficient = 0.61803;
    int c = (year * coefficient);
    double d = (year * coefficient);
    int res = size * (d - c);
	return res;
}

void create_cache_table(ifstream& input, vector<people_info>& cache_table, int size){
	while (input.peek() != EOF){
		//создаем буферную структуру для входных данных человека
		people_info temp;
		//считываем данные одного человека 
		temp = input_f(input);
		//определяем значение хеш функции
		int number = cache_function(temp.date.year, size);
		//добавляем данные по человеку в свободную ячейку хеш таблицы под номером number
		for (int i = 0; i < size; i++){
			int n = cache_function(number + i, size);
			if (cache_table[n].surname == " "){
				cache_table[n] = temp;
				break;
			}
		}
	}
}



void close_cache(){
	setlocale(LC_ALL,"RUS");
	//создаем потоки на ввод и ввывод
	ifstream input;
	ofstream output;
	int size = 28;
	input.open("input.txt");
	output.open("output_2.txt");
	//создаем и заполняем хэш таблицу
	vector<people_info> cache_table(size);
	create_cache_table(input, cache_table, size);

	//вывод таблицы
	for (int i = 0; i < size; i++){
		output << i << ":" << endl;
		people_info temp = cache_table[i];
		output_f(output, temp);
	}
	//закрываем поток
	input.close();
	output.close();
}


int main(){
	close_cache();
}