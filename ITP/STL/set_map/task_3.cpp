#include <iostream>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

/*
Найти слова (без учета регистра), которые встречаются только в 
повествовательных предложениях.
*/

void task_3() {
	setlocale(LC_ALL, "RUS");
	string str;
	
	set<string> s_input;
	set<string> s_main;
	set<string> s_other;
	int number_word;
	cout << "Введите кол-во слов в тексте:" << endl;
	cin >> number_word;
	cout << "Введите текст:" << endl;
	for (int i = 0; i < number_word; i++) {
		cin >> str;//ввод слова
		int len = str.length() - 1;//индекс последнего символа в слове
		//первод слова в нижний регистр 
		for (int j = 0; j < len; j++) {
			str[j] = tolower(str[j]);
		}
		
		//проверка на конец предложения
		if (str[len] == '.') {//если повествовательное предложение 
			//то добовляем в s_input последнее слово без .
			s_input.insert(str.substr(0, len));
			//копируем все слова в s_main 
			s_main.insert(s_input.begin(), s_input.end());
			//очищаем s_input для следующих предложений 
			s_input.clear();
		}
		else if (str[len] == '?' || str[len] == '!') {//если не повествовательное предложение
			//то добавляем в s_input последнее слово без ! или ?
			s_input.insert(str.substr(0,len));
			//копируем все слова в s_other
			s_other.insert(s_input.begin(), s_input.end());
			//очищаем s_input для следующих предложений 
			s_input.clear();
		}
		else {//если предложение не закончилось
			//то добавляем в s_input слово
			s_input.insert(str);
		}
	}
	
	cout << endl;
	set <string> s_res;
	//через разность s_main и s_other оставляем только те 
	//элементы из s_main которых нет в s_other
	set_difference(s_main.begin(), s_main.end(), s_other.begin(), s_other.end(), inserter(s_res, s_res.end()));
	//вывод
	cout << "Ответ:" << endl;
	for (auto i : s_res) {
		cout << i << endl;
	}
}

/*
10
qqq QQq t. q. qq t? q tt! tt qq.

10
qqq QQq t. q. qq ttt? q tt! tt qq.
*/

int main() {
	task_3();
	
}