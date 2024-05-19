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
