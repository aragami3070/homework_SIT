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

	vector<int> mas_sort(len1 + len2);
	//слияние двух массивов в один сортировкой слиянием
	merge(mas1.begin(), mas1.end(), mas2.begin(), mas2.end(), mas_sort.begin());
	cout << "Слияние двух массивов в один отсортированный: " << endl;
	for (auto i = mas_sort.begin(); i < mas_sort.end(); i++) {
		cout << *i << " ";
	}
	cout << endl << endl;

	//создаем массив для числа, чтобы вставить его в конечный массив сортировкой слиянием
	cout << "Введите число, которое нужно добавить в массив: " << endl;
	vector<int> mas3(1);
	cin >> mas3[0];
	cout << endl;

	//массив для результата
	vector<int> mas_res(len1 + len2 + 1);
	merge(mas_sort.begin(), mas_sort.end(), mas3.begin(), mas3.end(), mas_res.begin());

	//вывод ответа
	cout << "Ответ: " << endl;
	for (auto i = mas_res.begin(); i < mas_res.end(); i++) {
		cout << *i << " ";
	}
	cout << endl;
}


void task_3(){
	setlocale(LC_ALL, "RUS");
	cout << "Введите кол-во точек в массиве: ";
	int len;
	cin >> len;
	vector<vector<double>> mas_main(len, vector<double>(3));
	vector<double> mas_p(3);
	//ввод координат точек
	cout << "Введите координаты точек: " << endl;
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> mas_main[i][j];
		}
	}
	//ввод координат исходной точки
	cout << "Введите координаты исходной точки: ";
	for (int i = 0; i < 3; i++) {
		cin >> mas_p[i];
	}
	vector<double> mas_res;//массив для результатов
	for (int i = 0; i < len; i++) {
		//нахождение растояния между главной точкой и i-ой точкой массива
		//lambda функция для нахождения для нахождения квадрата разности координат точек
		auto func = [](int a, int b) {return (a - b) * (a - b); };
		//сумма квадратов разности координат (x координат, y координат, z координат)
		double length = inner_product(mas_main[i].begin(), mas_main[i].end(), mas_p.begin(), 0, plus<double>(), func);
		//берем корень для получения расстояния между точками и добавляем в массив
		mas_res.push_back(sqrt(length));
	}
	//вывод
	cout << "Ответ: " << endl;
	for (auto it = mas_res.begin(); it != mas_res.end(); ++it) {
		cout << *it << endl;
	}
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