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