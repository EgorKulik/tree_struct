#include <iostream>
using namespace std;

struct Node                         //Звено дерева
{
	int x;                           //То, что записываем в дерево
	Node *l, *r;                      //Это указатели на новые звенья
};

struct list
{
	int field; // поле данных
	struct list *next; // указатель на следующий элемент
	struct list *prev; // указатель на предыдущий элемент
};

struct list * init(int a)  // а- значение первого узла
{
	struct list *lst;
	// выделение памяти под корень списка
	lst = (struct list*)malloc(sizeof(struct list));
	lst->field = a;
	lst->next = lst; // указатель на следующий узел
	lst->prev = lst; // указатель на предыдущий узел
	return(lst);
}

struct list * addelem(list *lst, int number)
{
	struct list *temp, *p;
	temp = (struct list*)malloc(sizeof(list));
	p = lst->next; // сохранение указателя на следующий узел
	lst->next = temp; // предыдущий узел указывает на создаваемый
	temp->field = number; // сохранение поля данных добавляемого узла
	temp->next = p; // созданный узел указывает на следующий узел
	temp->prev = lst; // созданный узел указывает на предыдущий узел
	p->prev = temp;
	return(temp);
}
void listprintr(list *lst)
{
	struct list *p;
	p = lst;
	do {
		p = p->prev;  // переход к предыдущему узлу
		printf("%d ", p->field); // вывод значения элемента p
	} while (p != lst); // условие окончания обхода
}

void show(Node *&Tree)              //Функция обхода
{
	if (Tree != NULL)               //Пока не встретится пустое звено
	{
		show(Tree->l);               //Рекурсивная функция для вывода левого поддерева
		cout << Tree->x << '\t';               //Отображаем корень дерева
		show(Tree->r);               //Рекурсивная функци для вывода правого поддерева
	}
}

/*Добавили очистку памяти*/
void del(Node *&Tree){
	if (Tree != NULL)                //Пока не встретится пустое звено
	{
		del(Tree->l);                //Рекурсивная функция прохода по левому поддереву
		del(Tree->r);                //Рекурсивная функци для прохода по правому поддереву
		delete Tree;                 //Убиваем конечный элемент дерева
		Tree = NULL;                 //Может и не обязательно, но плохого не будет
	}

}

void add_node(int x, Node *&MyTree) //Фукция добавления звена в дерево
{
	if (NULL == MyTree)             //То, о чем я в самом начале писал. Если дерева нет, то ложим семечко
	{
		MyTree = new Node;          //Выделяем память под звено дерева
		MyTree->x = x;              //Записываем данные в звено
		MyTree->l = MyTree->r = NULL; //Подзвенья инициализируем пустотой во избежание ошибок
	}

	if (x < MyTree->x)   //Если нововведенный элемент x меньше чем элемент x из семечка дерева, уходим влево
	{
		if (MyTree->l != NULL) add_node(x, MyTree->l); //При помощи рекурсии заталкиваем элемент на свободный участок
		else          //Если элемент получил свой участок, то
		{
			MyTree->l = new Node;                 //Выделяем память левому подзвену. Именно подзвену, а не просто звену
			MyTree->l->l = MyTree->l->r = NULL;   //У левого подзвена будут свои левое и правое подзвенья, инициализируем их пустотой
			MyTree->l->x = x;                     //Записываем в левое подзвено записываемый элемент
		}
	}

	if (x > MyTree->x)              //Если нововведенный элемент x больше чем элемент x из семечка дерева, уходим вправо
	{
		if (MyTree->r != NULL) add_node(x, MyTree->r); //При помощи рекурсии заталкиваем элемент на свободный участок
		else              //Если элемент получил свой участок, то
		{
			MyTree->r = new Node;                 //Выделяем память правому подзвену. Именно подзвену, а не просто звену
			MyTree->r->l = MyTree->r->r = NULL;   //У правого подзвена будут свои левое и правое подзвенья, инициализируем их пустотой
			MyTree->r->x = x;                     //Записываем в правое подзвено записываемый элемент
		}
	}
}

Node* DeleteNode(Node* node, int x){
	if (node == NULL)
		return node;
	
	if (x == node->x){

		Node* tmp;
		if (node->r == NULL)
			tmp = node->l;
		else {

			Node* ptr = node->r;
			if (ptr->l == NULL){
				ptr->l = node->l;
				tmp = ptr;
			}
			else {

				Node* pmin = ptr->l;
				while (pmin->l != NULL){
					ptr = pmin;
					pmin = ptr->l;
				}
				ptr->l = pmin->r;
				pmin->l = node->l;
				pmin->r = node->r;
				tmp = pmin;
			}
		}

		delete node;
		return tmp;
	}
	else if (x < node->x)
		node->l = DeleteNode(node->l, x);
	else
		node->r = DeleteNode(node->r, x);
	return node;
}

Node* find(Node* Three, int dr, int dl)
{
	if (Three == NULL)
	{
		return NULL;  // не найден
	}
	if ((Three->x >= dr) & (Three->x <= dl))
	{
		
		return Three; // нашли!!!
	}

	if (dr >= Three->x)
	{
		// left
		if (Three->l != NULL)
			return find(Three->l, dr, dl); // рекурсивный поиск влево
		else
		{
			return NULL; // не найден
		}
	}
	else
	{
		//right
		if (Three->r)
			return find(Three->r, dr, dl);// рекурсивный поиск вправо
		else
		{
			return NULL; // не найден
		}
	}
}

int main()
{
	Node *Tree = NULL;                   //Создаю указатель, тип которого = звено дерева и инициализирую его пустотой
	for (int i = 5; i>0; i--) add_node(i, Tree);       //Это я забивал 5-4-3-2-1, а вывод сами увидите
	show(Tree);                        //Вывод на экран дерева. или просто обход дерева
	cout << '\n';
	DeleteNode(Tree, 0);
	show(Tree);

	if (find(Tree, 5, 6))
		cout << "Find" << endl;

	del(Tree);                        //Чистка памяти! Распилили дерево

}