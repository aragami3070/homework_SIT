#include <iostream>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

/*
Найти все такие цифры, которые встречаются в трехзначных числах,
но не встречаются в двузначных.
*/

void task_1() {
	setlocale(LC_ALL, "RUS");
	cout << "Введите кол-во чисел:" << endl;
	int n;
	cin >> n;
	set<int> s;
	set<int> s_2;
	int x;
	cout << "Введите числа:" << endl;
	for (int i = 0; i < n; i++) {
		cin >> x;
		if (x > 99 && x < 1000) {//считывание трехзначных 
			//если трехзначное число, то запоминаем его цифры
			s.insert(x / 100);
			s.insert((x / 10) % 10);
			s.insert(x % 10);
		}
		if (x > 9 && x < 100) {//считывание двухзначных
			//если двухзначное число, то запоминаем его цифры
			s_2.insert(x % 10);
			s_2.insert(x / 10);
		}
	}

	cout << "Ответ:" << endl;
	
	set<int> s3;
	//если в s_2 двухзначных нет цифры из s трехзначных, то выводим цифру(вычитаем s_2 из s)
	set_difference(s.begin(), s.end(), s_2.begin(), s_2.end(), inserter(s3, s3.end()));
	for (auto i : s3) {
		cout << i << " ";
	}
	cout << endl;
}
/*
test's
10

100 101 102 103 301 30 1 2 3 0


10

56 585 46 125 712 898 127 994 67 948
*/

int main(){
	task_1();
}