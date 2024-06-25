#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#define MAX_QUEUE_SIZE 5 //ť���� ���
#define SIZE 100 //����Ʈ������ ���
#define TRUE 1 //������
#define FALSE 0 //������
#define MAX_ELEMENT 200 //�켱���� ť


/////// 1. ��ȯ
int fib(int n) {
	if (n == 0) return 0;
	if (n == 1) return 1;

	return (fib(n - 1) + fib(n - 2));
}

//////// 2. ����
typedef struct stackNode {
	int data;
	struct stackNode* link;
}stackNode;

stackNode* createstackNode(int i) {
	stackNode* p = (stackNode*)malloc(sizeof(stackNode));
	p->data = i;
	p->link = NULL;
	return p;
}
void push(int i, stackNode** t) {
	stackNode* p = createstackNode(i);
	p->link = *t;
	*t = p;
}

void printStack(stackNode** t) {
	stackNode* top = (*t);

	for (; top != NULL;) {
		printf("%d-> ", top->data);
		top = top->link;
	}
	printf("NULL \n\n");
}


int pop(stackNode** t) {
	if (*t == NULL) {
		printf("�������.\n");
		return -1; // 
	}

	stackNode* tmp = *t;

	int poppedData = tmp->data;
	*t = tmp->link;
	free(tmp);

	return poppedData;
}

/////// 3. ť
typedef struct {
	int data[MAX_QUEUE_SIZE];  // ť ������ �迭
	int front, rear;  // ť�� front�� rear �ε���
} Queue;

// ť �ʱ�ȭ �Լ�
void initQueue(Queue* q) {
	q->front = q->rear = -1;
}

//����
void error(char* message) {
	fprintf(stderr,"%s\n", message);
	exit(1);
}

//���
void queue_print(Queue* q) {
	for (int i = 0; i < MAX_QUEUE_SIZE; i++) {
		if (i <= q->front || i > q->rear) {
			printf("  |  ");
		}
		else {
			printf("%d | ", q->data[i]);
		}
	}
	printf("\n");
}

// ť�� ����ִ��� Ȯ���ϴ� �Լ�
int isEmpty(Queue* q) {
	if (q->front == q->rear) {
		return 1;
	}
	else {
		return 0;
	}
}

// ť�� �� á���� Ȯ���ϴ� �Լ�
int isFull(Queue* q) {
	if (q->rear == MAX_QUEUE_SIZE - 1) {
		return 1;
	}
	else {
		return 0;
	}
}

// ť�� �����͸� �����ϴ� �Լ�
void enqueue(Queue* q, int item) {
	if (isFull(q)) {
		error("ť�� ��ȭ�����Դϴ�.");
		return;
	}
	q->data[++(q->rear)] = item;
}

// ť���� �����͸� �����ϴ� �Լ�
int dequeue(Queue* q) {
	if (isEmpty(q)) {
		error("ť�� ��������Դϴ�.");
		return -1;
	}
	int item = q->data[++(q->front)];
	return item;
}


/////// 4. ���Ḯ��Ʈ

typedef struct Node { //����, ����
	int num;
	struct Node* link;
}Node;

Node* firstNode(int i) {
	Node* p = (Node*)malloc(sizeof(Node));
	p->num = i;
	p->link = NULL;

	return p;
}

Node* createNode(int i, Node* rear) {
	Node* p = (Node*)malloc(sizeof(Node));
	p->num = i;
	p->link = NULL;
	rear->link = p;

	return p;
}

typedef struct Node2 { //���߿��Ḯ��Ʈ
	int num;
	struct Node2* link1;
	struct Node2* link2;
}Node2;

Node2* firstNode1(int i) 
{
	Node2* p = (Node2*)malloc(sizeof(Node2));
	p->num = i;
	p->link1 = NULL;
	p->link2 = NULL;
	return p;
}

Node2* createNode2(int i, Node2* rear) {
	Node2* p = (Node2*)malloc(sizeof(Node2));
	p->num = i;
	p->link1 = NULL;
	p->link2 = rear;
	rear->link1 = p;
	return p;
}


/////// 5. ���� Ʈ��
typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
}TreeNode;

int top = -1; 
TreeNode* stack[SIZE]; //Ʈ���� ��带 ������ ���ù迭

void Treepush(TreeNode* p) { //������ ���� ���� �ʾ��� �� ��带 ���ÿ� �߰�
	if (top < SIZE - 1) {
		stack[++top] = p;
	}
}

TreeNode* Treepop() { // ������ ��� ���� ���� �� ���ÿ��� ��带 �����ϰ� ��ȯ
	TreeNode* p = NULL;
	if (top >= 0) {
		p = stack[top--];
	}
	return p;
}

void inorder_iter(TreeNode* root) { //����

	while (1) {
		for (; root; root = root->left) {
			Treepush(root);
		}
		root = Treepop();
		if (!root) break;
		printf("[%d]", root->data);
		root = root->right;
	}
}

void preorder_iter(TreeNode* root) { //����
	if (!root) return; // ��Ʈ�� NULL�̸� �Լ� ����

	Treepush(root); // ��Ʈ�� ���ÿ� �߰�

	while (top >= 0) {
		root = Treepop(); // ���ÿ��� ��带 ������
		printf("[%d]", root->data); // ����� �����͸� ���

		// ������ �ڽ��� ���� ���ÿ� �߰� (������ ���Լ��� �����̹Ƿ� ���� �ڽ��� ���� ó���ǵ���)
		if (root->right) {
			Treepush(root->right);
		}
		// ���� �ڽ��� ���ÿ� �߰�
		if (root->left) {
			Treepush(root->left);
		}
	}
}

// ������ȸ
int top1 = -1; // ����1�� ���� ��ġ
int top2 = -1; // ����2�� ���� ��ġ
TreeNode* stack1[SIZE]; // Ʈ���� ��带 ������ ù ��° ���� �迭
TreeNode* stack2[SIZE]; // ��� ��带 ������ �� ��° ���� �迭

void push1(TreeNode* p) { // ����1�� ��带 �߰�
	if (top1 < SIZE - 1) {
		stack1[++top1] = p;
	}
}

TreeNode* pop1() { // ����1���� ��带 �����ϰ� ��ȯ
	TreeNode* p = NULL;
	if (top1 >= 0) {
		p = stack1[top1--];
	}
	return p;
}

void push2(TreeNode* p) { // ����2�� ��带 �߰�
	if (top2 < SIZE - 1) {
		stack2[++top2] = p;
	}
}

TreeNode* pop2() { // ����2���� ��带 �����ϰ� ��ȯ
	TreeNode* p = NULL;
	if (top2 >= 0) {
		p = stack2[top2--];
	}
	return p;
}

void postorder_iter(TreeNode* root) {
	if (!root) return; // ��Ʈ�� NULL�̸� �Լ� ����

	push1(root); // ��Ʈ�� ù ��° ���ÿ� �߰�

	while (top1 >= 0) {
		root = pop1(); // ����1���� ��带 ������
		push2(root); // ����2�� ��带 �߰�

		// ���� �ڽ��� ����1�� �߰�
		if (root->left) {
			push1(root->left);
		}
		// ������ �ڽ��� ����1�� �߰�
		if (root->right) {
			push1(root->right);
		}
	}

	// ����2���� ��带 ������ ��� (������ȸ ������ ��µ�)
	while (top2 >= 0) {
		root = pop2();
		printf("[%d]", root->data);
	}
}

TreeNode n1 = { 1,NULL,NULL };
TreeNode n2 = { 4,&n1,NULL };
TreeNode n3 = { 16,NULL,NULL };
TreeNode n4 = { 25,NULL,NULL };
TreeNode n5 = { 20,&n3,&n4 };
TreeNode n6 = { 15,&n2, &n5 };
TreeNode* root = &n6;

/////// 6. ������ ���� Ʈ��

typedef struct TTreeNode {
	int data;
	struct TTreeNode* left, * right;
	int is_thread; // ������� TRUE
}TTreeNode;

TTreeNode n11 = { 'A',NULL,NULL,1 };
TTreeNode n22 = { 'B',NULL,NULL,1 };
TTreeNode n33 = { 'C',&n11,&n22,0 };
TTreeNode n44 = { 'D',NULL,NULL,1 };
TTreeNode n55 = { 'E',NULL,NULL,0 };
TTreeNode n66 = { 'F',&n44,&n55,0 };
TTreeNode n77 = { 'G',&n33,&n66,0 };
TTreeNode* exp = &n77;

TTreeNode* find_successor(TTreeNode* p) {
	TTreeNode* q = p->right;

	if (q == NULL || p->is_thread == TRUE) {
		return q;
	}
	while (q->left != NULL) q = q->left;
	return q;
}

void thread_inorder(TTreeNode* t) {
	TTreeNode* q;
	q = t;
	while (q->left) q = q->left;
	do {
		printf("%c -> ", q->data);
		q = find_successor(q);
	} while (q);
}


//////// 7. ������ ���� Ʈ��

typedef struct TTTreeNode {
	int key;
	struct TTTreeNode* left, * right;
}TTTreeNode;

TTTreeNode* search(TTTreeNode* node, int key) {
	if (node == NULL) return NULL;
	if (key == node->key) return node;
	else if (key < node->key)
		return search(node->left, key);
	else
		return search(node->right, key);
}

TTTreeNode* new_node(int item) {
	TTTreeNode* temp = (TTTreeNode*)malloc(sizeof(TTTreeNode));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}

TTTreeNode* insert_node(TTTreeNode* node, int key) {
	if (node == NULL) return new_node(key);
	if (key < node->key)
		node->left = insert_node(node->left, key);
	else if (key > node->key)
		node->right = insert_node(node->right, key);

	return node;
}

TTTreeNode* min_value_node(TTTreeNode* node) {
	TTTreeNode* current = node;
	while (current->left != NULL)
		current = current->left;
	
	return current;
}

TTTreeNode* delete_node(TTTreeNode* root1, int key) {
	if (root1 == NULL) return root1;
	if (key < root1->key)
		root1->left = delete_node(root1->left, key);
	else if (key > root1->key)
		root1->right = delete_node(root1->right, key);
	else {
		if (root1->left == NULL) {
			TTTreeNode* temp = root1->right;
			free(root1);
			return temp;
		}
		else if (root1->right == NULL) {
			TTTreeNode* temp = root1->left;
			free(root1);
			return temp;
		}

		TTTreeNode* temp = min_value_node(root1->right);

		root1->key = temp->key;
		root1->right = delete_node(root1->right, temp->key);
	}
	return root1;
}

void inorder(TTTreeNode* root1) {
	if (root1) {
		inorder(root1->left);
		printf("[%d] ", root1->key);
		inorder(root1->right);
	}
}

/////// 8. �켱���� ť(����Ʈ��)
typedef struct {
	int key;
}element;

typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;


HeapType* create() {
	return (HeapType*)malloc(sizeof(HeapType));
}

void init(HeapType* h) {
	h->heap_size = 0;
}

void insert_max_heap(HeapType* h, element item) {
	int i;
	i = ++(h->heap_size);

	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}

element delete_max_heap(HeapType* h) {
	int parent, child;
	element item,temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;

	while (child <= h->heap_size) {
		if ((child < h->heap_size) && (h->heap[child].key < h->heap[child + 1].key))
			child++;
		if (temp.key >= h->heap[child].key) break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

int main() {
	int x = 0;

	while (x != 9) {
		printf("------------- ������ ���� �����ϼ���.(1 ~ 7) -------------\n");
		printf("1. ��ȯ\n");
		printf("2. ����\n");
		printf("3. ť\n");
		printf("4. ���Ḯ��Ʈ (�ܼ�, ����, ����)\n");
		printf("5. ���� Ʈ�� (������ȸ, ������ȸ, ������ȸ)\n");
		printf("6. ������ ���� Ʈ��\n");
		printf("7. ���� Ž�� Ʈ��\n");
		printf("8. �켱���� ť(����Ʈ��)\n");
		printf("9. ����\n");
		printf("----------------------------------------------------------\n");
		printf(">> ������ ���� �����ϼ���.(1 ~ 9) : ");
		scanf_s("%d", & x);
		printf("\n");
		if (x == 1) { //��ȯ
			int n;
			printf(">> �Ǻ���ġ ���� ���� ���� ���� �Է��ϼ���. : ");
			scanf_s("%d", &n);
			int r = fib(n);
			printf("%d\n", r);
			printf("\n");
		}
		else if (x == 2) { // ����
			stackNode* top = NULL;
			int n;
			printf(">> 1~n���� �ױ�! n�� �Է��ϼ��� :");
			scanf_s("%d", &n);
			printf("\n");
			for (int i = 1; i <= n; i++) {
				push(i, &top);
				printStack(&top);
			}
			printf("\n");
			int pdata; // ��ȯ ��

			while (top != NULL) {
				pdata = pop(&top);

				if (pdata == -1)
				{
					printf("������ �����\n\n");
					break;
				}
				else printf("%d ��/�� pop \n", pdata);

				printStack(&top);
			}
			printf("\n\n");

		}
		else if (x == 3) { //ť
			int item = 0;
			Queue q;
			initQueue(&q);

			enqueue(&q, 10); queue_print(&q);
			enqueue(&q, 20); queue_print(&q);
			enqueue(&q, 30); queue_print(&q);
			enqueue(&q, 40); queue_print(&q);
			enqueue(&q, 50); queue_print(&q);
			printf("\n");
			item = dequeue(&q); queue_print(&q);
			item = dequeue(&q); queue_print(&q);
			item = dequeue(&q); queue_print(&q);
			item = dequeue(&q); queue_print(&q);
			item = dequeue(&q); queue_print(&q);
			printf("\n");
		}
		else if (x == 4) { //���Ḯ��Ʈ(�ܼ�, ����, ����)
			int y=0;
			printf(">> ������� ���Ḯ��Ʈ ������ �����Ͻÿ� (1:�ܼ� 2:���� 3:����) : ");
			scanf_s("%d", &y);
			printf("\n");
			if (y == 1) { //�ܼ�
				Node* head = NULL;
				Node* rear = NULL;
				int l;
				printf("���� ��� ���� �Է� : ");
				scanf_s("%d", & l);
				printf("\n");

				for (int i = 1; i <= l; i++) {
					if (head == NULL) {
						head = firstNode(i);
						rear = head;
					}
					else {
						rear = createNode(i, rear);
					}
				}
				Node* o = head;
				for (int i = 0; i < l; i++){
					printf("%d ", o->num);
					o = o->link;
				}
				printf("\n\n");
			}
			else if (y == 2) { //����
				Node* head = NULL;
				Node* rear = NULL;
				int l;
				int ll=0;
				printf("���� ��� ���� �Է� : ");
				scanf_s("%d", &l);
				printf("\n");

				for (int i = 1; i <= l; i++) {
					if (head == NULL) {
						head = firstNode(i);
						rear = head;
					}
					else {
						rear = createNode(i, rear);
					}
				}
				rear->link = head;
				Node* o = head;
				printf("����� Ƚ�� : ");
				scanf_s("%d", &ll);
				printf("\n");
				for (int i = 0; i < ll; i++) {
					printf("%d ", o->num);
					o = o->link;
				}
				printf("\n\n");
			}
			else if (y == 3) { //����
				Node2* head = NULL;
				Node2* rear = NULL;
				int ii=0;
				printf("���� ��� ���� : ");
				scanf_s("%d", &ii);
				printf("\n");
				for (int i = 1; i <= ii; i++) {
					if (head == NULL) {
						head = firstNode1(i);
						rear = head;
					}
					else {
						rear = createNode2(i,rear);
					}
				}
				Node2* o = head;
				for (int i = 0; i < ii; i++) {
					printf("%d ", o->num);
					o = o->link1;
				}
				o = rear;
				for (int i = 0; i < ii-1; i++) {
					o = o->link2;
					printf("%d ", o->num);
				}
				printf("\n\n");
			}
			else {
				printf(">> ������ �� ���� ��ȣ�Դϴ�.");
				printf("\n\n");
			}
		}
		else if (x == 5) { //���� Ʈ��
			int y = 0;
			printf("\t\t15\n\n\t4\t\t20\n\n1\t\t     16\t   25\n\n");
			printf(">> ������� ��ȸ�� �����Ͻÿ� (1:���� 2:���� 3:����) : ");
			scanf_s("%d", &y);
			printf("\n");
			if (y == 1) { //����
				printf("������ȸ=");
				inorder_iter(root);
				printf("\n\n");
			}
			else if (y == 2) { //����
				printf("������ȸ=");
				preorder_iter(root);
				printf("\n\n");
			}
			else if (y == 3) { //����
				printf("������ȸ=");
				postorder_iter(root);
				printf("\n\n");
			}
			else {
				printf(">> ������ �� ���� ��ȣ�Դϴ�.");
				printf("\n\n");
				continue;
			}
		}
		else if (x == 6) { //������ ���� Ʈ��
			//������ ����
			n11.right = &n33;
			n22.right = &n77;
			n44.right = &n66;
			//������ȸ
			thread_inorder(exp);
			printf("\n\n");
		}
		else if (x == 7) { //���� Ž�� Ʈ��
			TTTreeNode* root1 = NULL;
			TTTreeNode* tmp = NULL;
			int a;
			root1 = insert_node(root1, 30);
			root1 = insert_node(root1, 20);
			root1 = insert_node(root1, 10);
			root1 = insert_node(root1, 40);
			root1 = insert_node(root1, 50);
			root1 = insert_node(root1, 60);
			printf(">> Ž���� ��带 �Է��ϼ���.(10����) : ");
			scanf_s("%d", &a);
			printf("\n");
			printf("���� Ž�� Ʈ�� ���� ��ȸ ��� \n");
			inorder(root1);
			printf("\n\n");
			if (search(root1, a) != NULL)
				printf("���� Ž�� Ʈ������ %d�� �߰��� \n",a);
			else
				printf("���� Ž�� Ʈ������ %d�� �߰߸���",a);
			printf("\n\n");

		}
		else if (x == 8) { //�켱���� ť (����Ʈ��)
			element e1 = { 10 }, e2 = { 5 }, e3 = { 30 };
			element e4, e5, e6;
			HeapType* heap;

			heap = create();
			init(heap);

			insert_max_heap(heap, e1);
			insert_max_heap(heap, e2);
			insert_max_heap(heap, e3);

			e4 = delete_max_heap(heap);
			printf("< %d > ", e4.key);
			e5 = delete_max_heap(heap);
			printf("< %d > ", e5.key);
			e6 = delete_max_heap(heap);
			printf("< %d > ", e6.key);
			printf("\n\n");
			free(heap);
		}
		else {
			if (x == 9) {
				printf(">> �����մϴ�.\n");
			}
			else {
				printf(">> �޴��� ���� �����Դϴ�.\n\n");
				continue;
			}
		}
	}
	return 0;
}
 
