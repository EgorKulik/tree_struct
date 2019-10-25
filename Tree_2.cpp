#include <iostream>
using namespace std;

struct Node                         //����� ������
{
	int x;                           //��, ��� ���������� � ������
	Node *l, *r;                      //��� ��������� �� ����� ������
};

struct list
{
	int field; // ���� ������
	struct list *next; // ��������� �� ��������� �������
	struct list *prev; // ��������� �� ���������� �������
};

struct list * init(int a)  // �- �������� ������� ����
{
	struct list *lst;
	// ��������� ������ ��� ������ ������
	lst = (struct list*)malloc(sizeof(struct list));
	lst->field = a;
	lst->next = lst; // ��������� �� ��������� ����
	lst->prev = lst; // ��������� �� ���������� ����
	return(lst);
}

struct list * addelem(list *lst, int number)
{
	struct list *temp, *p;
	temp = (struct list*)malloc(sizeof(list));
	p = lst->next; // ���������� ��������� �� ��������� ����
	lst->next = temp; // ���������� ���� ��������� �� �����������
	temp->field = number; // ���������� ���� ������ ������������ ����
	temp->next = p; // ��������� ���� ��������� �� ��������� ����
	temp->prev = lst; // ��������� ���� ��������� �� ���������� ����
	p->prev = temp;
	return(temp);
}
void listprintr(list *lst)
{
	struct list *p;
	p = lst;
	do {
		p = p->prev;  // ������� � ����������� ����
		printf("%d ", p->field); // ����� �������� �������� p
	} while (p != lst); // ������� ��������� ������
}

void show(Node *&Tree)              //������� ������
{
	if (Tree != NULL)               //���� �� ���������� ������ �����
	{
		show(Tree->l);               //����������� ������� ��� ������ ������ ���������
		cout << Tree->x << '\t';               //���������� ������ ������
		show(Tree->r);               //����������� ������ ��� ������ ������� ���������
	}
}

/*�������� ������� ������*/
void del(Node *&Tree){
	if (Tree != NULL)                //���� �� ���������� ������ �����
	{
		del(Tree->l);                //����������� ������� ������� �� ������ ���������
		del(Tree->r);                //����������� ������ ��� ������� �� ������� ���������
		delete Tree;                 //������� �������� ������� ������
		Tree = NULL;                 //����� � �� �����������, �� ������� �� �����
	}

}

void add_node(int x, Node *&MyTree) //������ ���������� ����� � ������
{
	if (NULL == MyTree)             //��, � ��� � � ����� ������ �����. ���� ������ ���, �� ����� �������
	{
		MyTree = new Node;          //�������� ������ ��� ����� ������
		MyTree->x = x;              //���������� ������ � �����
		MyTree->l = MyTree->r = NULL; //��������� �������������� �������� �� ��������� ������
	}

	if (x < MyTree->x)   //���� ������������� ������� x ������ ��� ������� x �� ������� ������, ������ �����
	{
		if (MyTree->l != NULL) add_node(x, MyTree->l); //��� ������ �������� ����������� ������� �� ��������� �������
		else          //���� ������� ������� ���� �������, ��
		{
			MyTree->l = new Node;                 //�������� ������ ������ ��������. ������ ��������, � �� ������ �����
			MyTree->l->l = MyTree->l->r = NULL;   //� ������ �������� ����� ���� ����� � ������ ���������, �������������� �� ��������
			MyTree->l->x = x;                     //���������� � ����� �������� ������������ �������
		}
	}

	if (x > MyTree->x)              //���� ������������� ������� x ������ ��� ������� x �� ������� ������, ������ ������
	{
		if (MyTree->r != NULL) add_node(x, MyTree->r); //��� ������ �������� ����������� ������� �� ��������� �������
		else              //���� ������� ������� ���� �������, ��
		{
			MyTree->r = new Node;                 //�������� ������ ������� ��������. ������ ��������, � �� ������ �����
			MyTree->r->l = MyTree->r->r = NULL;   //� ������� �������� ����� ���� ����� � ������ ���������, �������������� �� ��������
			MyTree->r->x = x;                     //���������� � ������ �������� ������������ �������
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
		return NULL;  // �� ������
	}
	if ((Three->x >= dr) & (Three->x <= dl))
	{
		
		return Three; // �����!!!
	}

	if (dr >= Three->x)
	{
		// left
		if (Three->l != NULL)
			return find(Three->l, dr, dl); // ����������� ����� �����
		else
		{
			return NULL; // �� ������
		}
	}
	else
	{
		//right
		if (Three->r)
			return find(Three->r, dr, dl);// ����������� ����� ������
		else
		{
			return NULL; // �� ������
		}
	}
}

int main()
{
	Node *Tree = NULL;                   //������ ���������, ��� �������� = ����� ������ � ������������� ��� ��������
	for (int i = 5; i>0; i--) add_node(i, Tree);       //��� � ������� 5-4-3-2-1, � ����� ���� �������
	show(Tree);                        //����� �� ����� ������. ��� ������ ����� ������
	cout << '\n';
	DeleteNode(Tree, 0);
	show(Tree);

	if (find(Tree, 5, 6))
		cout << "Find" << endl;

	del(Tree);                        //������ ������! ��������� ������

}