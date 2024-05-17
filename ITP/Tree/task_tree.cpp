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


tree* find(tree* tr, int value) {//поиск
	//если нашли или дошли до конца ветки
	if (tr->inf == value || !tr) {
		return tr;
	}
	//если элемент больше, то идем по правой ветке
	if (tr->inf < value) {
		return find(tr->right, value);
	}
	//иначе идем по левой ветке
	else {
		return find(tr->left, value);
	}
}


tree* Min(tree* tr) {//поиск минимального
	//чтобы получить минимальный элемент идем по левой ветке до конца
	//если последний элемент в ветке
	if (!tr->left) {
		return tr;
	}
	//иначе идем по ветке дальше 
	else {
		return Min(tr->left);
	}
}


tree* Max(tree* tr) {//поиск максимального
	//чтобы получить максимальный элемент идем по правой ветке до конца
	//если последний элемент в ветке
	if (!tr->right) {
		return tr;
	}
	//иначе идем по ветке дальше
	else {
		return Max(tr->right);
	}
}


tree* Next(tree* tr, int value) {//поиск следующего
	//создаем указатель на элемент value
	tree* elem = find(tr, value);
	if (elem == Max(tr)) {
		return NULL;
	}
	//если есть правый ребенок 
	if (elem->right) {
		return Min(elem->right);//min по правой ветке
	}
	tree* par_elem = elem->parent;//указатель на родителя
	//пока не дошли до корня или узел - правый ребенок
	while (par_elem && elem == par_elem->right) {
		//идем вверх по дереву
		elem = par_elem;
		par_elem = par_elem->parent;
	}
	return par_elem;
}


tree* Prev(tree* tr, int value) {//поиск предыдущего
	//создаем указатель на элемент value
	tree* elem = find(tr, value);
	if (elem == Min(tr)) {
		return NULL;
	}
	//если есть левый ребенок 
	if (elem->left) {
		return Max(elem->left);//max по левой ветке
	}
	tree* par_elem = elem->parent;//указатель на родителя 
	//пока не дошли до корня или узел - левый ребенок 
	while (par_elem && elem == par_elem->left) {
		//идем вверх по дереву
		elem = par_elem;
		par_elem = par_elem->parent;
	}
	return par_elem;
}


//симетричный обход
void inorder(tree* tr) {
	if (tr) {
		inorder(tr->left);
		cout << tr->inf << " ";
		inorder(tr->right);
	}
}


//прямой обход
void preorder(tree* tr) {
	if (tr) {
		cout << tr->inf << " ";
		preorder(tr->left);
		preorder(tr->right);
	}
}


//обратный обход
void postorder(tree* tr) {
	if (tr) {
		preorder(tr->left);
		preorder(tr->right);
		cout << tr->inf << " ";
	}
}


//заполнение дерева бинарного поиска
void input_bin_tree(tree*& tr) {
	cout << "Введите кол-во элементов дерева: ";
	int len, value;
	cin >> len;
	cout << "Введите элементы дерева:" << endl;
	for (int i = 0; i < len; i++) {
		cin >> value;
		insert(tr, value);//добавляем элемент в дерево
	}
}
