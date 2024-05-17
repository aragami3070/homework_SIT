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


