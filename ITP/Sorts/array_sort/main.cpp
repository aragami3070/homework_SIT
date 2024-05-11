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

