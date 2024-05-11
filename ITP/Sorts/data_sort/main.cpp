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