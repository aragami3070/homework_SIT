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
