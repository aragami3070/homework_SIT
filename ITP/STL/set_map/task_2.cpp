#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

/*
Найти слова, встречающиеся ровно 𝑘 раз.
*/

void task_2() {
	setlocale(LC_ALL, "RUS");
	map<string, int> m_input;

	string x;
	ifstream input;
	input.open("input_task_2.txt");
	//ввод данных
	while (input.peek() != EOF) {
		x = " ";
		input >> x;
		++m_input[x];
	}
	input.close();

	multimap <int, string> m_main;
	//поменяли местами значения в паре для поиска по кол-во вводов слова
	//multimap, чтобы вывести все слова с одинаковым повоторением при вводе
	for (auto i : m_input) {
		m_main.insert(make_pair(i.second,i.first));
	}
	
	cout << "Ведите k:" << endl;
	int k;
	cin >> k;
	while (k < 1) {
		cout << "k должен быть больше 0, введите еще раз:" << endl;
		cin >> k;
	}
	cout << "Ответ:" << endl;
	auto result = m_main.find(k);
	if (result != m_main.end()) {
		//пока есть слова k раз введенные выводим слово и удаляем его
		while (result != m_main.end()){
			cout << (*result).second << endl;
			m_main.erase(result);
			result = m_main.find(k);
		}
	}
	else {
		cout << "нет элемента введенного k раз" << endl;
	}
}
/*
test
3

1

0
2
*/

int main(){
	task_2();
}