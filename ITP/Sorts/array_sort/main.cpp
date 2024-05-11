#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>


using namespace std;


void input_from_file(vector<vector<int>>& mas) {
	//создаем поток на чтение из файла 
	ifstream input;
	input.open("input.txt");
	//считываем размер матрицы
	int mas_size;
	input >> mas_size;
	//считываем матрицу в массив 
	for (int i = 0; i < mas_size; i++) {
		mas.push_back(vector<int>());
		for (int j = 0; j < mas_size; j++) {
			int value;
			input >> value;
			mas[i].push_back(value);
		}
	}
	//закрываем поток
	input.close();
}


void output_in_file(vector<vector<int>>& mas,int mas_size, string task_number) {
	//создаем поток на вывод матрицы в файл 
	ofstream output;
	output.open("output_" + task_number + ".txt");
	//выводим матрицу в файл
	for (int i = 0; i < mas_size; i++) {
		for (int j = 0; j < mas_size; j++) {
			output << mas[i][j] << " ";
		}
		output << endl;
	}
	//закрываем поток 
	output.close();
}


void reverse_mas(vector<vector<int>>& mas, int mas_size) {
	//функция располагающая столбцы матрицы как строки
	vector<vector<int>> mas1;
	for (int j = 0; j < mas_size; j++) {
		mas1.push_back(vector<int>());
		for (int i = 0; i < mas_size; i++) {
			mas1[j].push_back(mas[i][j]);
		}
	}
	mas = mas1;
}


void heap_sifting(vector<int>& s_mas, int index, int mas_size) {
	while (true) {
		int mmax = index;
		int left_i = 2 * index + 1;//индекс левого ребенка
		int right_i = 2 * index + 2;//индекс правого ребенка
		//если левый ребенок больше родителя, то mmax приравниваем к индексу ребенка 
		if (left_i < mas_size && s_mas[mmax] < s_mas[left_i]) {
			mmax = left_i;
		}
		//если правый ребенок больше родителя, то mmax приравниваем к индексу ребенка
		if (right_i < mas_size && s_mas[mmax] < s_mas[right_i]) {
			mmax = right_i;
		}
		//если mmax == индексу родителя, то завершаем цикл
		//иначе меняем родителя местами с ребенком 
		//и ребенок становится родителем 
		if (mmax == index) {
			break;
		}
		else {
			swap(s_mas[mmax], s_mas[index]);
			index = mmax;
		}
	}
}


void heap_sort(vector<vector<int>>& mas, int mas_size) {
	for (int i = 0; i < mas_size; i++) {
		//строим пирамиду через функцию просеивания - 
		//heap_sifting(массив, индекс родителя, размер массива)
		for (int j = (mas_size / 2) + 1; j >= 0; j--) {
			heap_sifting(mas[i], j, mas_size);
		}
		//так как в голове пирамиды находится максимальный элемент, меняем его с 
		//j - тым элементом массива(последним элементом из не отсортированной части массива)
		for (int j = mas_size - 1; j > 0; j--) {
			swap(mas[i][0], mas[i][j]);
			//перестраиваем пирамиду сначала не включая отсортированные элементы
			heap_sifting(mas[i], 0, j);
		}
	 }
}


void task_1() {
	//создаем массив под матрицу
	vector<vector<int>> mas;
	//заполняем массив из файла input.txt
	input_from_file(mas);
	//размер квадратной матрицы
	int mas_size = mas[0].size();
	
	reverse_mas(mas, mas_size);
	//сортируем столбцы по возрастанию пирамидальной сортировкой  
	heap_sort(mas, mas_size);
	reverse_mas(mas, mas_size);
	//выводим отсортированную матрицу в файл output_1.txt
	output_in_file(mas, mas_size, "1");
}



void merge(vector<int> &s_mas, int left_i, int right_i, int middle) {
	
	if (left_i >= right_i || middle < left_i || middle > right_i) {
		return;
	}
	//если массив состоит из двух элементов и они не отсортированы, 
	//то меняем местами и прекращаем работу алгоритма 
	if (right_i - left_i == 1 && (s_mas[left_i] > s_mas[right_i])) {
		swap(s_mas[left_i], s_mas[right_i]);
		return;
	}
	//создаем индексы для левого и правого массивов  
	int l_begin = left_i, r_begin = middle + 1;
	
	int flag = 0;
	
	vector<int> temp;
	while (right_i - left_i + 1 > flag) {
		//если все элементы из левого массива добавленны 
		//то добавляем оставшиеся из правого
		if (l_begin > middle) {
			for (int i = r_begin; i <= right_i; i++) {
				temp.push_back(s_mas[i]);
				flag++;
			}
		}
		//иначе если все элементы из правого массива добавленны
		//то добавляем оставшиеся из левого
		else if (r_begin > right_i) {
			for (int i = l_begin; i <= middle; i++) {
				temp.push_back(s_mas[i]);
				flag++;
			}
		}
		//иначе если элемент из левого массива больше элемента из правого массива,
		//то добавляем элемент из правого
		else if (s_mas[l_begin] > s_mas[r_begin]) {
			temp.push_back(s_mas[r_begin]);
			r_begin++;
			flag++;
		}
		//иначе добавляем элемент из левого
		else {
			temp.push_back(s_mas[l_begin]);
			l_begin++;
			flag++;
		}
		
	}
	//записываем отсортированный temp в основной массив начиная с индекса left_i
	flag = left_i;
	for (auto i = temp.begin(); i != temp.end(); i++) {
		s_mas[flag] = *i;
		flag++;
	}
}

void merge_sort(vector<int>& s_mas, int left_i, int right_i) {
	if (left_i >= right_i) {
		return;
	}
	//создаем индекс на центральный элемент
	int middle = left_i + ((right_i - left_i) / 2);
	//запускаем сортировку от левого края до центра
	merge_sort(s_mas, left_i, middle);
	//запускаем сортировку от центра до правого края 
	merge_sort(s_mas, middle + 1, right_i);
	//слияние получившихся массивов
	merge(s_mas, left_i, right_i, middle);
}


void task_2() {
	//создаем вектор под матрицу 
	vector<vector<int>> mas;
	//заполняем массив из файла input.txt
	input_from_file(mas);
	//размер квадратной матрицы
	int mas_size = mas[0].size();
	//сортируем через сортировку слиянием 
	//каждую третью строку матрицы по убыванию, остальные по возрастанию
	for (int i = 0; i < mas_size; i++) {
		//сортируем по возрастанию
		merge_sort(mas[i], 0, mas_size - 1);
		if ((i + 1) % 3 == 0) {
			//переворот отсортированной строки
			reverse(mas[i].begin(), mas[i].end());
		}
	}
	
	//выводим отсортированную матрицу в файл output_2.txt
	output_in_file(mas, mas_size, "2");
}


void selection_sort(vector<int>& s_mas, int mas_size) {
	//проходимся по массиву
	for (int index = 0; index < mas_size; index++) {
		//находим минимум от index до конца массива
		int min_index = index;
		for (int i = index + 1; i < mas_size; i++) {
			if (s_mas[i] < s_mas[min_index]) {
				min_index = i;
			}
		}
		//меняем местами элемент в index с минимальным
		swap(s_mas[index], s_mas[min_index]);
	}
}


void task_3() {
	//создаем массив под матрицу
	vector<vector<int>> mas;
	//заполняем массив из файла input.txt
	input_from_file(mas);
	//размер квадратной матрицы
	int mas_size = mas[0].size();
	//создаем массив из диагоналей
	vector <vector<int>> temp;
	//добавляем все диагонали от главной и выше(включительно)
	for (int i = 0; i < mas_size ; i++) {
		temp.push_back(vector<int>());
		for (int j = 0; j < mas_size; j++) {
			if (j + i < mas_size) {
				temp[i].push_back(mas[j][j + i]);
				
			}
		}
		
	}
	//добавляем все диагонали ниже главной 
	for (int i = 1; i < mas_size; i++) {
		temp.push_back(vector<int>());
		for (int j = 0; j < mas_size; j++) {
			if (j + i < mas_size) {
				temp[i + mas_size - 1].push_back(mas[j+i][j]);

			}
		}

	}
	//проходимся по массиву с диагоналями и сортируем диагонали
	for (auto temp_it = temp.begin(); temp_it != temp.end(); temp_it++) {
		selection_sort(*temp_it, (*temp_it).size());
	}
	//возвращаем отсортированные диагонали в изначальный массив
	//возвращаем все диагонали от главной и выше
	for (int i = 0; i < mas_size; i++) {
		for (int j = 0; j < mas_size; j++) {
			if (j + i < mas_size) {
				mas[j][j + i] = temp[i][j];

			}
		}

	}
	//возвращаем все диагонали ниже главной 
	for (int i = 1; i < mas_size; i++) {
		for (int j = 0; j < mas_size; j++) {
			if (j + i < mas_size) {
				mas[j + i][j] = temp[i + mas_size - 1][j];

			}
		}

	}
	//выводим матрицу в файл output_3.txt
	output_in_file(mas, mas_size, "3");
}

int main() {
	setlocale(LC_ALL, "RUS");
	cout << "Выбор задания:" << endl;
	cout << "Задание 1 пирамидальная сортировка : 1" << endl;
	cout << "Задание 2 сортировка слиянием : 2" << endl;
	cout << "Задание 3 сортировка выбором : 3" << endl;
	int choose_n;//выбор задания по номеру(1,2,3) через switch
	cin >> choose_n;
	switch (choose_n) {
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