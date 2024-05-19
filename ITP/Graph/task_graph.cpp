#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <vector>


using namespace std;


struct queue {
	int inf;
	queue* next;
};


void push_back(queue*& head, queue*& tail, int value) {
	queue* new_cell = new queue;// создаем новый элемент
	new_cell->inf = value;//добавляем значение в поле нового элемента
	new_cell->next = NULL;//новый элемент всегда последний
	if (!head && !tail) {//если очередь пуста, то 
		//новый элемент и голова и хвост
		head = tail = new_cell;
	}
	else {
		tail->next = new_cell;//новый элемент следующий для хвоста
		tail = new_cell;//теперь новый элемент это хвост
	}
}


int pop(queue*& head, queue*& tail) {
	int value;//переменная для вывода значения головы
	value = head->inf;//присваиваем значение головы
	queue* delete_cell;//создаем доп указатель 
	delete_cell = head;//ставим этот указатель на голову
	head = head->next;//голову переносим на следующий элемент
	if (!head) {//если удаляем последний элемент из очереди
		tail = NULL;
	}
	delete delete_cell;//удаляем первый элемент
	return value;//возвращаем значение удаленного элемента
}

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


void d_f_s(map<int, list<pair<int, double>>>& graph, map<int, int>& visited_node, int first_node) {
	//помечаем вершину как посещенную
	visited_node[first_node] = 1;
	//создаем указательна эту вершину
	auto it = graph.find(first_node);
	//проходимся по всем смежным вершинам
	for (auto it_n = it->second.begin(); it_n != it->second.end(); it_n++) {
		//если it_n вершина еще не была посещена
		if (!visited_node.count(it_n->first)) {
			//то вызываем этот обход от вершины it_n
			d_f_s(graph, visited_node, it_n->first);
		}
	}
}

/*
Дан неориентированный граф. 
Выяснить, является ли граф связным.
*/

void task_4() {
	//создаем граф
	map<int, list<pair<int, double>>> graph;
	//не ориетированный граф
	bool orient = false;
	//заполняем граф
	input_graph(graph, orient);
	map<int, int> visited_node;
	//проходимся по всем вершинам смежным с первой и записываем их в visited_node
	d_f_s(graph, visited_node, graph.begin()->first);
	//если флаг останется true, то граф связный, иначе несвязный
	bool flag = true;
	for (auto it = graph.begin(); it != graph.end(); it++) {
		//если вершина не нашлась в словаре, значит граф несвязный
		if (!visited_node.count(it->first)) {
			flag = false;
			break;
		}
	}
	if (flag) {
		cout << "Граф связный" << endl;
	}
	else {
		cout << "Граф несвязный" << endl;
	}
}


void b_f_s(map<int, list<pair<int, double>>>& graph, map<int, int>& visited_node, int first_node) {
	visited_node[first_node] = 1;
	queue* head = NULL;
	queue* tail = NULL;
	push_back(head, tail, first_node);
	while (head) {
		int node = pop(head, tail);
		auto it = graph.find(node);
		for (auto it_n = it->second.begin(); it_n != it->second.end(); it_n++) {
			if (!visited_node[it_n->first]) {
				visited_node[it_n->first] = 1;
				push_back(head, tail, it_n->first);
			}
		}
	}
}



int main(){
	setlocale(LC_ALL, "RUS");
	task_4();
}