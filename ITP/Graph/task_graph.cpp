#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <vector>


using namespace std;



void add_edge(map<int, list<pair<int, double>>>& graph, int node1, int node2, double weight = 1.0, bool orient = false) {
	//ищем вершину node1
	auto it_node1 = graph.find(node1);
	bool flag = false;//флаг для проверки на существование введенного ребра
	//если вершина уже существует
	if (it_node1 != graph.end()) {
		for (auto it_node2 = it_node1->second.begin(); it_node2 != it_node1->second.end(); it_node2++) {
			//проверяем существует ли ребро node1 -> node2
			//и если существует, то 
			if (it_node2->first == node2) {
				//меняем флаг и прерываем цикл
				flag = true;
				break;
			}
		}
	}
	//если ребра нет, то добавляем его
	if (!flag) {
		//если граф ориетированный 
		if (orient) {
			//добавляем ребро node1 -> node2
			graph[node1].push_back(make_pair(node2, weight));
			//если вершины node2 нет
			if (graph.find(node2) == graph.end()) {
				//мнимое ребро node2 -> 0
				graph[node2].push_back(make_pair(0, 0));
				//находим node2
				auto it = graph.find(node2);
				//удаляем мнимое ребро (единственное)
				it->second.erase(it->second.begin());
			}
		}
		//если граф не ориентированный
		else {
			//добавляем ребро node1->node2
			graph[node1].push_back(make_pair(node2, weight));
			//добавляем ребро node2->node1
			graph[node2].push_back(make_pair(node1, weight));
		}
	}
}


void input_graph(map<int, list<pair<int, double>>>& graph, bool orient = false) {
	//создаем буфферные переменные для создания ребер
	int node1, node2;
	double weight;
	//создаем поток на ввод
	ifstream input;
	input.open("input.txt");
	//считывание из файла
	while (input.peek() != EOF) {
		input >> node1 >> node2 >> weight;
		//добавляем ребро в граф
		if (weight != 0) {
			add_edge(graph, node1, node2, weight, orient);
		}
		else {
			add_edge(graph, node1, node2, orient);
		}
	}
	input.close();
}


void output_graph(map<int, list<pair<int, double>>>& graph) {
	for (auto it_main_node = graph.begin(); it_main_node != graph.end(); it_main_node++) {
		//выводим вершину откуда выходят ребра
		cout << it_main_node->first << ": " << endl;
		//выводим список смежных вершин
		for (auto it_node = it_main_node->second.begin(); it_node != it_main_node->second.end(); it_node++) {
			cout << "{" << it_node->first << ", " << it_node->second << "}; ";
		}
		cout << endl;
	}
}



/*
Дан неориентированный граф. 
Вывести количество вершин, смежных с данной.
*/

void task_1() {
	//создаем граф
	map<int, list<pair<int, double>>> graph;
	//не ориетированный граф
	bool orient = false;
	//заполняем граф
	input_graph(graph, orient);
	cout << "Введите вершину:" << endl;
	int node;
	cin >> node;
	auto it = graph.find(node);
	cout << "Ответ:" << endl;
	for (auto it_res = it->second.begin(); it_res != it->second.end(); it_res++) {
		cout << it_res->first << " ";
	}
	cout << endl;
}
/*
test (ввод через файл)

1 2 1
2 3 1
3 4 1
4 1 1
5 6 1
*/


/*
Дан неориентированный граф. 
Вставить в граф ребро, соединяющее вершины A и B.
*/

void task_2() {
	//создаем граф
	map<int, list<pair<int, double>>> graph;
	//не ориетированный граф
	bool orient = false;
	//заполняем граф
	input_graph(graph, orient);
	cout << "Введите вершины:" << endl;
	int node1, node2;
	cin >> node1 >> node2;
	add_edge(graph, node1, node2, 1.0, orient);
	cout << "Ответ:" << endl;
	output_graph(graph);
}


/*
Дан неориентированный граф. 
Подсчитать степень каждой вершины.
*/

void task_3() {
	//создаем граф
	map<int, list<pair<int, double>>> graph;
	//не ориетированный граф
	bool orient = false;
	//заполняем граф
	input_graph(graph, orient);
	cout << "Ответ(вершина : степень):" << endl;
	for (auto it = graph.begin(); it != graph.end(); it++) {
		cout << it->first << ":" << it->second.size() << endl;
	}
	output_graph(graph);
}


int main(){
	task_3();
}