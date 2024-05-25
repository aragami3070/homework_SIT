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

