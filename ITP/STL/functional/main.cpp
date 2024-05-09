#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cmath>


using namespace std;


void input_mas(int len, vector<int>& mas) {
	cout << "Введите числа массива: ";
	for (int i = 0; i < len; i++) {
		cin >> mas[i];
	}
	cout << endl;
}


void task_1() {
	setlocale(LC_ALL, "RUS");
	cout << "Введите кол-во чисел в массиве: ";
	int len;
	cin >> len;
	vector<int> mas(len);
	//вводим элементы массива
	input_mas(len, mas);
	//находим адресс минимального элемента
	auto it = min_element(mas.begin(), mas.end());

	cout << "Ответ: " << endl;
	//выводим кол-во минимальных элементов
	cout << count(mas.begin(), mas.end(), *it) << endl;;
}


void task_2(){
	setlocale(LC_ALL, "RUS");
	cout << "Введите кол-во чисел в массиве: ";
	int len1;
	cin >> len1;
	vector<int> mas1(len1);
	input_mas(len1, mas1);//вводим элементы массива

	//удаляем все нечетные из первого массива
	auto chek1 = [](int i) {return i % 2 != 0; };
	auto new_end = remove_if(mas1.begin(), mas1.end(), chek1);
	mas1.erase(new_end, mas1.end());//удаляем все после нового конца
	len1 = mas1.size();
	sort(mas1.begin(), mas1.end());//сортируем массив

	cout << "Измененный первый массив: " << endl;
	for (auto i = mas1.begin(); i < mas1.end(); i++) {
		cout << *i << " ";
	}
	cout << endl << endl;


	cout << "Введите кол-во чисел в массиве: ";
	int len2;
	cin >> len2;
	vector<int> mas2(len2);
	input_mas(len2, mas2);//вводим элементы массива 
	int x;
	cout << "x = ";
	cin >> x;
	cout << endl;
	auto it = max_element(mas2.begin(), mas2.end());//находим адресс минимального элемента

	//меняем все кратные х на макс элемент во втором массиве
	auto chek2 = [&x](int i) {return i % x == 0; };
	replace_if(mas2.begin(), mas2.end(), chek2, *it);
	sort(mas2.begin(), mas2.end());//сортируем массив

	cout << "Измененный второй массив: " << endl;
	for (auto i = mas2.begin(); i < mas2.end(); i++) {
		cout << *i << " ";
	}
	cout << endl << endl;

}


void task_3(){
	
}


int main(){
	cout << "Выберете номер задания:" << endl;
	cout << "1: Дан набор целых чисел. Найти количество минимальных чисел." << endl;

	cout << "2: Даны 2 последовательности целых чисел." << endl <<
	"Удалить из первой последовательности все нечетные числа. " << endl <<
	"Заменить во второй последовательности все числа, кратные Х, максимальным числом. " << endl <<
	"Отсортировать обе последовательности. " << endl <<
	"Соединить их в одну отсортированную последовательность (оптимальным способом) " << endl <<
	"Добавить новый элемент так, чтобы последовательность осталась отсортированной. (оптимальным способом)" << endl <<
	"Добавить  в конец и потом отсортировать - не является оптимальным способом)." << endl;

	cout << "3: Дан список точек в пространстве (например, vector<vector<double>> a, " << endl <<
	"где внутренний вектор - это координаты точки в пространстве.). Дана точка  Х в пространстве." << endl <<
	"Используя библиотеки numeric и functional, найти сумму расстояний от точки X до остальных" << "" <<
	" точек в пространстве." << endl;
	int number;
	cin >> number;

	switch(number){
	case 1: 
		task_1();
		break;
	case 2: 
		task_2();
		break;
	case 3: 
		task_3();
		break;
	}
}