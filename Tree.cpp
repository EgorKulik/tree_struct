/*Написать программу, обеспечивающую работу с деревом поиска: добавление/удаление  элемента,
просмотр дерева,  очистка дерева, поиск элемента по ключу, а также копирование в однонаправленный
цикличский список элемента с заданным ключом, просмотр и очистку этого списка.
*/
#include<iostream>
#include<fstream>
#include <ctime>
using namespace std;
ifstream inf("input.txt");
int menu()
{
	int variantik;
	cout
		<< "1. Dobavit element: \n"
		<< "2. Ydalit element: .\n"
		<< "3. Pechat dereva: \n"
		<< "4. Ochistka dereva: \n"
		<< "5. Poisk po kluchy: \n"
		<< "6. Kopir v odnon cikl spisok elem s zadan kluchom: .\n"
		<< "7. Pechat spiska: \n"
		<< "8. Ochistka spiska: \n"
		<< "9. Vihod iz programma\n" << endl;
	cout << "Viberite variant\n" << endl;
	cin >> variantik;
	return variantik;
}
template <typename T>
struct Node {
	Node<T>*parent;
	T info;
	Node<T>*left;
	Node<T>*right;
};
template <typename T>
struct BinaryTree {
	Node<T>*root;

	void Init()
	{
		root = NULL;


	}
	Node<T>*newNode(const T& value, Node<T>*parent) {
		Node<T>*tmp = new Node<T>;
		tmp->info = value;
		tmp->parent = parent;
		tmp->left = tmp->right = NULL;
		return tmp;
	}
	void Insert(const T&value) {
		if (root == NULL) {
			root = newNode(value, NULL);
			return;
		}
		else {
			Node<T>*tmp = root;
			while (1) {
				if (tmp->info == value) {

					return;
				}
				else {
					if (tmp->info < value) {
						if (tmp->right != NULL)
							tmp = tmp->right;
						else {
							tmp->right = newNode(value, tmp);
							return;
						}
					}
					else {
						if (tmp->left != NULL)
							tmp = tmp->left;
						else {
							tmp->left = newNode(value, tmp);
							return;
						}
					}
				}
			}
		}
	}
	void PrintTreeSym(Node<T>* tmp) {
		if (tmp == NULL) return;
		if (tmp != NULL) {
			PrintTreeSym(tmp->left);
			cout << tmp->info/* <<" ("<< count <<") "*/;
			PrintTreeSym(tmp->right);
		}
	}
	void PrintTreePryam(Node<T>* tmp) {
		if (tmp == NULL) return;
		if (tmp != NULL) {
			cout << tmp->info << ' '/* << " (" << count << ") "*/;
			PrintTreePryam(tmp->left);
			PrintTreePryam(tmp->right);
		}
	}
	void PrintTreeObr(Node<T>* tmp) {
		if (tmp == NULL) return;
		if (tmp != NULL) {
			PrintTreeObr(tmp->left);
			PrintTreeObr(tmp->right);
			cout << tmp->info/* << " (" << count << ") "*/;
		}
	}
	void PrintBeautifulTree(Node<T>* tmp, int level = 0) {
		if (tmp == NULL)return;
		else {
			PrintBeautifulTree(tmp->right, level + 1);
			for (int i = 0; i < level; i++)
				cout << '\t';
			cout << tmp->info << endl;
			PrintBeautifulTree(tmp->left, level + 1);
		}
	}
	int delet(BinaryTree * search_node, int  item)
	{
		Node<T> ** q, *z, *x, *y;

		q = &search_node->root;
		z = search_node->root;
		//поиск удаляемого элемента
		while (1)
		{
			if (z == NULL) return 0;
			else if (item == z->info) break;
			else if (item > z->info)
			{
				q = &z->right;
				z = z->right;
			}
			else
			{
				q = &z->left;
				z = z->left;
			}
		}

		// непосредственное удаление элемента
		if (z->right == NULL) *q = z->left;
		else
		{
			y = z->right;
			if (y->left == NULL)
			{
				y->left = z->left;
				*q = y;
			}
			else
			{
				x = y->left;
				while (x->left != NULL)
				{
					y = x;
					x = y->left;
				}
				y->left = x->right;
				x->left = z->left;
				x->right = z->right;
				*q = x;
			}
		}

		//	search_node->count--;
		free(z);
		return 1;
	}
	//функция для удаления отдельного узла дерева и его потомков
	/*void destroy(Node<T> * search_node)
	{
	if (search_node == NULL) return;
	destroy(search_node->left);
	destroy(search_node->right);
	free(search_node);
	}*/
	//функция для полного удаления дерева
	//void destroy(BinaryTree<T> * search_tree)
	//{
	//	destroy(search_tree/*->root*/);
	//	free(search_tree);
	//}
	void destroy(Node<T>* &tmp) {
		if (tmp != NULL) {
			destroy(tmp->left);
			destroy(tmp->right);
			delete tmp;
			tmp = NULL;
		}
	}
	bool find(BinaryTree * search_node, const T& x) {
		Node<T> ** q, *z;

		q = &search_node->root;
		z = search_node->root;
		while (1)
		{
			if (z == NULL) return 0;
			else if (x == z->info) return 1;
			else if (x > z->info)
			{
				q = &z->right;
				z = z->right;
			}
			else
			{
				q = &z->left;
				z = z->left;
			}
		}
	}
	///////////////////////////////
	template <typename T>
	struct node {
		T key;
		node<T> *next;
	};
	template <typename T>
	struct List {
		node<T> *Head = NULL;
		node<T> *Tail = NULL;
		node<T>* temp;

		node<T>* newnode() {
			node<T>* tmp = new node<T>;
			return tmp;
		}
		void PushBack(const T& key) {
			if (Head == NULL) {
				Head = newnode();
				Tail = Head;
				Head->key = key;
				Head->next = Head;
			}
			else {
				temp = newnode();
				Tail->next = temp;
				temp->next = Head;
				temp->key = key;
				Tail = temp;
			}
		}
		//////////////////////////////////////////
		bool erase(List<T> *Li) {
			if (Li->Head == NULL)return false;
			node<T> * temp;
			temp = Li->Head;
			while (temp->next != Li->Head) {//Tail
				while (temp->next != Li->Head) { temp = temp->next; }//Tail
				temp->next = Li->Head->next;
				free(Li->Head);
				Li->Head = temp;
			}
			free(Li->Head);
			Li->Head = NULL;
			return true;
		}
		bool Print() {
			if (!Head) return false;
			node<T>* tmp = Head;
			while (1) {
				cout << tmp->key << " ";
				cout << endl;
				if (tmp->next == Head)break;
				tmp = tmp->next;
			}
			return true;
		}
	};


};

int main()

{
	int n, vibor, ii = 0, val, yz;
	BinaryTree<int>::List<int> L;
	BinaryTree <int>  tree;
	Node <int> * nd;
	tree.Init();

	//L.Init();
	while (inf >> val) {
		tree.Insert(val);
	}
	nd = tree.root;
	//cout << "Vedite 1 zapolnit text, 0 no zapolnit" << endl;
	//cin >> vibor;
	//if (vibor == 1) {
	//	ofstream outf("input.txt");
	//	cout << "Vedite kolichestvo uzlov" << endl;
	//	cin >> n;
	//	//srand(time(0));
	//	for (int i = 0; i < n; i++) {
	//		if (ii == 10) { outf << endl; ii = 0; }
	//		outf << 1 + rand() % n << ' ';
	//		ii++;
	//	}
	//}
	//inf >> val;
	while (1) {
		int variantik = menu();
		switch (variantik) {
		case 1:
			cout << "Vvedite element,kotorii hotite dobavit: ";
			cin >> yz;
			tree.Insert(yz);
			break;
		case 2:
			cout << "Vvedite element,kotorii hotite ydalit: ";
			cin >> yz;
			if (tree.find(&tree, yz))
			{
				tree.delet(&tree, yz);
				nd = tree.root;
			}
			else cout << "Takogo elementa ne nabludaetsya, proverte pravilnost vvoda.\n";
			cout << endl;
			break;
		case 3:
			nd = tree.root;//
			tree.PrintTreePryam(nd);
			cout << endl;
			tree.PrintBeautifulTree(nd);
			cout << endl;
			break;
		case 4:
			tree.destroy(nd);
			///////////////
			tree.Init();
			nd = tree.root;
			/////////////////
			cout << endl;
			break;
		case 5:
			cout << "Vvedite element,kotorii hotite naiti: ";
			cin >> yz;
			if (tree.find(&tree, yz)) cout << "Vse okei, element nahelsya.";
			else cout << "Vahi gelaniya ne sovpadaut s nahimi vozmognostyami."; cout << endl;
			break;
		case 6:
			cout << "Vvedite element,kotorii hotite skopirovat: ";
			cin >> yz;
			if (tree.find(&tree, yz))
				L.PushBack(yz);
			else cout << "Takogo elementa v dereve net!";
			cout << endl;
			break;
		case 7:
			if (!L.Print()) cout << "Spisok pust" << endl;
			cout << endl;
			break;
		case 8:
			L.erase(&L);
			cout << endl;
			break;
		case 9:
			cout << "Spasibo,chto ispolzovali moy programmy)))" << endl;
			exit(EXIT_SUCCESS);
			break;
		default:
			cerr << "Vi vibrali nevernui variant" << endl;
			exit(EXIT_FAILURE);
		}
	}
	//nd = tree.root;
	//tree.PrintTreeSym(nd);
	//cout << endl;
	//tree.PrintBeautifulTree(nd);
	//cout << endl;
	////tree.PrintTreePryam(nd);
	////cout << endl;
	//cout << "Vvedite yzel,kotorii neobhodimo ydalit" << endl;
	//cin >> yz;
	//tree.delet(&tree, yz);
	//cout << endl;
	//nd = tree.root;
	//tree.PrintTreeSym(nd);
	//cout << endl;
	//tree.PrintBeautifulTree(nd);
	//
	//cin>>
	////L.copy(&L, nd);
	//L.Print();

	return 0;
}

