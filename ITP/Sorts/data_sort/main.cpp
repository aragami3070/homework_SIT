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
