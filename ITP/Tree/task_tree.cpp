#include <iostream>


using namespace std;

struct tree {
	int inf;//значение узла
	tree* left;//левый ребенок
	tree* right;//правый ребенок
	tree* parent;//родитель
};


tree* node(int value) {
	tree* new_node = new tree;//создаем новый узел
	new_node->inf = value;
	new_node->parent = NULL;//обнуляем указатели на родителя и на детей
	new_node->left = NULL;
	new_node->right = NULL;
	return new_node;//возвращаем указатель на новый узел
}



void insert(tree*& tr, int value) {
	tree* new_node = node(value);
	if (!tr) {//если дерево пустое
		tr = new_node;//то новый элемент корень
	}
	else {
		//создаем доп указатель на дерево
		tree* temp = tr;
		while (temp) {
			//если новый элемент больше чем элемент на который указывает temp
			if (new_node->inf > temp->inf){
				//если у temp есть правый ребенок 
				if (temp->right) {
					//то смещаем указатель temp на этого ребенка
					temp = temp->right;
				}
				//иначе новый элемент - это правый ребенок temp
				else {
					new_node->parent = temp;
					temp->right = new_node;
					break;
				}
			}
			//иначе если новый элемент меньше чем элемент на который указывает temp
			else if (new_node->inf < temp->inf) {
				//если у temp есть левый ребенок
				if (temp->left) {
					//то смещаем указатель temp на этого ребенка
					temp = temp->left;
				}
				//иначе новый элемент - это левый ребенок temp
				else {
					new_node->parent = temp;
					temp->left = new_node;
					break;
				}
			}

		}
	}
}

