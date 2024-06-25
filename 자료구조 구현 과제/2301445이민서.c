#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#define MAX_QUEUE_SIZE 5 //큐에서 사용
#define SIZE 100 //이진트리에서 사용
#define TRUE 1 //스레드
#define FALSE 0 //스레드
#define MAX_ELEMENT 200 //우선순위 큐


/////// 1. 순환
int fib(int n) {
	if (n == 0) return 0;
	if (n == 1) return 1;

	return (fib(n - 1) + fib(n - 2));
}

//////// 2. 스택
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
		printf("비어있음.\n");
		return -1; // 
	}

	stackNode* tmp = *t;

	int poppedData = tmp->data;
	*t = tmp->link;
	free(tmp);

	return poppedData;
}

/////// 3. 큐
typedef struct {
	int data[MAX_QUEUE_SIZE];  // 큐 데이터 배열
	int front, rear;  // 큐의 front와 rear 인덱스
} Queue;

// 큐 초기화 함수
void initQueue(Queue* q) {
	q->front = q->rear = -1;
}

//오류
void error(char* message) {
	fprintf(stderr,"%s\n", message);
	exit(1);
}

//출력
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

// 큐가 비어있는지 확인하는 함수
int isEmpty(Queue* q) {
	if (q->front == q->rear) {
		return 1;
	}
	else {
		return 0;
	}
}

// 큐가 꽉 찼는지 확인하는 함수
int isFull(Queue* q) {
	if (q->rear == MAX_QUEUE_SIZE - 1) {
		return 1;
	}
	else {
		return 0;
	}
}

// 큐에 데이터를 삽입하는 함수
void enqueue(Queue* q, int item) {
	if (isFull(q)) {
		error("큐가 포화상태입니다.");
		return;
	}
	q->data[++(q->rear)] = item;
}

// 큐에서 데이터를 삭제하는 함수
int dequeue(Queue* q) {
	if (isEmpty(q)) {
		error("큐가 공백상태입니다.");
		return -1;
	}
	int item = q->data[++(q->front)];
	return item;
}


/////// 4. 연결리스트

typedef struct Node { //단일, 원형
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

typedef struct Node2 { //이중연결리스트
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


/////// 5. 이진 트리
typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
}TreeNode;

int top = -1; 
TreeNode* stack[SIZE]; //트리의 노드를 저장할 스택배열

void Treepush(TreeNode* p) { //스택이 가득 차지 않았을 때 노드를 스택에 추가
	if (top < SIZE - 1) {
		stack[++top] = p;
	}
}

TreeNode* Treepop() { // 스택이 비어 있지 않을 때 스택에서 노드를 제거하고 반환
	TreeNode* p = NULL;
	if (top >= 0) {
		p = stack[top--];
	}
	return p;
}

void inorder_iter(TreeNode* root) { //중위

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

void preorder_iter(TreeNode* root) { //전위
	if (!root) return; // 루트가 NULL이면 함수 종료

	Treepush(root); // 루트를 스택에 추가

	while (top >= 0) {
		root = Treepop(); // 스택에서 노드를 꺼내고
		printf("[%d]", root->data); // 노드의 데이터를 출력

		// 오른쪽 자식을 먼저 스택에 추가 (스택은 후입선출 구조이므로 왼쪽 자식이 먼저 처리되도록)
		if (root->right) {
			Treepush(root->right);
		}
		// 왼쪽 자식을 스택에 추가
		if (root->left) {
			Treepush(root->left);
		}
	}
}

// 후위순회
int top1 = -1; // 스택1의 현재 위치
int top2 = -1; // 스택2의 현재 위치
TreeNode* stack1[SIZE]; // 트리의 노드를 저장할 첫 번째 스택 배열
TreeNode* stack2[SIZE]; // 결과 노드를 저장할 두 번째 스택 배열

void push1(TreeNode* p) { // 스택1에 노드를 추가
	if (top1 < SIZE - 1) {
		stack1[++top1] = p;
	}
}

TreeNode* pop1() { // 스택1에서 노드를 제거하고 반환
	TreeNode* p = NULL;
	if (top1 >= 0) {
		p = stack1[top1--];
	}
	return p;
}

void push2(TreeNode* p) { // 스택2에 노드를 추가
	if (top2 < SIZE - 1) {
		stack2[++top2] = p;
	}
}

TreeNode* pop2() { // 스택2에서 노드를 제거하고 반환
	TreeNode* p = NULL;
	if (top2 >= 0) {
		p = stack2[top2--];
	}
	return p;
}

void postorder_iter(TreeNode* root) {
	if (!root) return; // 루트가 NULL이면 함수 종료

	push1(root); // 루트를 첫 번째 스택에 추가

	while (top1 >= 0) {
		root = pop1(); // 스택1에서 노드를 꺼내고
		push2(root); // 스택2에 노드를 추가

		// 왼쪽 자식을 스택1에 추가
		if (root->left) {
			push1(root->left);
		}
		// 오른쪽 자식을 스택1에 추가
		if (root->right) {
			push1(root->right);
		}
	}

	// 스택2에서 노드를 꺼내며 출력 (후위순회 순서로 출력됨)
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

/////// 6. 스레드 이진 트리

typedef struct TTreeNode {
	int data;
	struct TTreeNode* left, * right;
	int is_thread; // 스레드면 TRUE
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


//////// 7. 스레드 이진 트리

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

/////// 8. 우선순위 큐(히프트리)
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
		printf("------------- 실행할 것을 선택하세요.(1 ~ 7) -------------\n");
		printf("1. 순환\n");
		printf("2. 스택\n");
		printf("3. 큐\n");
		printf("4. 연결리스트 (단순, 원형, 이중)\n");
		printf("5. 이진 트리 (전위순회, 중위순회, 후위순회)\n");
		printf("6. 스레드 이진 트리\n");
		printf("7. 이진 탐색 트리\n");
		printf("8. 우선순위 큐(히프트리)\n");
		printf("9. 종료\n");
		printf("----------------------------------------------------------\n");
		printf(">> 실행할 것을 선택하세요.(1 ~ 9) : ");
		scanf_s("%d", & x);
		printf("\n");
		if (x == 1) { //순환
			int n;
			printf(">> 피보나치 수열 값을 구할 수를 입력하세요. : ");
			scanf_s("%d", &n);
			int r = fib(n);
			printf("%d\n", r);
			printf("\n");
		}
		else if (x == 2) { // 스택
			stackNode* top = NULL;
			int n;
			printf(">> 1~n까지 쌓기! n을 입력하세요 :");
			scanf_s("%d", &n);
			printf("\n");
			for (int i = 1; i <= n; i++) {
				push(i, &top);
				printStack(&top);
			}
			printf("\n");
			int pdata; // 반환 값

			while (top != NULL) {
				pdata = pop(&top);

				if (pdata == -1)
				{
					printf("스택이 비었음\n\n");
					break;
				}
				else printf("%d 을/를 pop \n", pdata);

				printStack(&top);
			}
			printf("\n\n");

		}
		else if (x == 3) { //큐
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
		else if (x == 4) { //연결리스트(단순, 원형, 이중)
			int y=0;
			printf(">> 보고싶은 연결리스트 구조를 선택하시오 (1:단순 2:원형 3:이중) : ");
			scanf_s("%d", &y);
			printf("\n");
			if (y == 1) { //단순
				Node* head = NULL;
				Node* rear = NULL;
				int l;
				printf("만들 노드 개수 입력 : ");
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
			else if (y == 2) { //원형
				Node* head = NULL;
				Node* rear = NULL;
				int l;
				int ll=0;
				printf("만들 노드 개수 입력 : ");
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
				printf("출력할 횟수 : ");
				scanf_s("%d", &ll);
				printf("\n");
				for (int i = 0; i < ll; i++) {
					printf("%d ", o->num);
					o = o->link;
				}
				printf("\n\n");
			}
			else if (y == 3) { //이중
				Node2* head = NULL;
				Node2* rear = NULL;
				int ii=0;
				printf("만들 노드 개수 : ");
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
				printf(">> 선택할 수 없는 번호입니다.");
				printf("\n\n");
			}
		}
		else if (x == 5) { //이진 트리
			int y = 0;
			printf("\t\t15\n\n\t4\t\t20\n\n1\t\t     16\t   25\n\n");
			printf(">> 보고싶은 순회를 선택하시오 (1:중위 2:전위 3:후위) : ");
			scanf_s("%d", &y);
			printf("\n");
			if (y == 1) { //중위
				printf("중위순회=");
				inorder_iter(root);
				printf("\n\n");
			}
			else if (y == 2) { //전위
				printf("전위순회=");
				preorder_iter(root);
				printf("\n\n");
			}
			else if (y == 3) { //후위
				printf("후위순회=");
				postorder_iter(root);
				printf("\n\n");
			}
			else {
				printf(">> 선택할 수 없는 번호입니다.");
				printf("\n\n");
				continue;
			}
		}
		else if (x == 6) { //스레드 이진 트리
			//스레드 설정
			n11.right = &n33;
			n22.right = &n77;
			n44.right = &n66;
			//중위순회
			thread_inorder(exp);
			printf("\n\n");
		}
		else if (x == 7) { //이진 탐색 트리
			TTTreeNode* root1 = NULL;
			TTTreeNode* tmp = NULL;
			int a;
			root1 = insert_node(root1, 30);
			root1 = insert_node(root1, 20);
			root1 = insert_node(root1, 10);
			root1 = insert_node(root1, 40);
			root1 = insert_node(root1, 50);
			root1 = insert_node(root1, 60);
			printf(">> 탐색할 노드를 입력하세요.(10단위) : ");
			scanf_s("%d", &a);
			printf("\n");
			printf("이진 탐색 트리 중위 순회 결과 \n");
			inorder(root1);
			printf("\n\n");
			if (search(root1, a) != NULL)
				printf("이진 탐색 트리에서 %d을 발견함 \n",a);
			else
				printf("이진 탐색 트리에서 %d을 발견못함",a);
			printf("\n\n");

		}
		else if (x == 8) { //우선순위 큐 (히프트리)
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
				printf(">> 종료합니다.\n");
			}
			else {
				printf(">> 메뉴에 없는 숫자입니다.\n\n");
				continue;
			}
		}
	}
	return 0;
}
 
