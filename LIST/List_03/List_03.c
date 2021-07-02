#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode { // 노드 타입
	element data;
	struct ListNode* link;
} ListNode;

// 오류 처리 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	//exit(1);
}

// 노드 pre 뒤에 새로운 노드 삽입
ListNode* insert_next(ListNode* head, ListNode* pre, element value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode)); //(1)

	p->data = value; //(2)
	p->link = pre->link; //(3)
	pre->link = p; //(4)

	return head; //(5)
}

ListNode* insert_first(ListNode* head, int value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode)); //(1)

	p->data = value; // (2)
	p->link = head; // 헤드 포인터의 값을 복사 //(3)
	head = p; // 헤드 포인터 변경 //(4)

	return head; // 변경된 헤드 포인터 반환
}
ListNode* insert_last(ListNode* head, int value)
{
	ListNode* temp = head;
	ListNode* p = (ListNode*)malloc(sizeof(ListNode)); //(1)

	p->data = value;
	p->link = NULL;
	// (2)
	if (head == NULL) // 공백 리스트이면
		head = p;
	else {
		while (temp->link != 0)
			temp = temp->link;
		temp->link = p;
	}
	return head; // 변경된 헤드 포인터 반환
}
// pre가 가리키는 노드의 다음 노드를 삭제한다. ListNode* delete_next(ListNode *head, ListNode *pre)
ListNode* delete_next(ListNode* head, ListNode* pre)
{
	ListNode* removed;

	removed = pre->link;
	pre->link = removed->link; // (2)
	free(removed); // (3)

	return head; // (4)
}
ListNode* delete_first(ListNode* head)
{
	ListNode* removed;

	if (head == NULL)
		error("삭제할 항목이 없음");
	removed = head; // (1)
	head = removed->link; // (2)
	free(removed); // (3)

	return head; // (4)
}
ListNode* delete_last(ListNode* head)
{
	ListNode* temp = head;
	ListNode* prevTemp = NULL;
	ListNode* removed; //불필요

	if (head == NULL)
		error("삭제할 항목이 없음");
	if (head->link == NULL) { // 하나의 노드
		free(temp);
		head = NULL;
	}
	else { // 둘 이상의 노드
		while (temp->link != NULL) {
			prevTemp = temp;
			temp = temp->link;
		}
		prevTemp->link = NULL;
		free(temp);

		return head; // 그대로
	}
}
void print_list(ListNode* head)
{
	ListNode* p;
	for (p = head; p != NULL; p = p->link)
		printf("%d->", p->data);
	printf("NULL \n");
}
ListNode* search(ListNode* head, int x)
{
	ListNode* p;

	p = head;
	while (p != NULL) {
		if (p->data == x) return p; // 탐색 성공
		p = p->link;
	}

	return NULL; // 탐색 실패일 경우 NULL 반환
}
ListNode* concat(ListNode* head1, ListNode* head2)
{
	ListNode* p;

	if (head1 == NULL)
		return head2;
	else if (head2 == NULL)
		return head1;
	else {
		p = head1;
		while (p->link != NULL)
			p = p->link;
		p->link = head2;

		return head1;
	}
}
ListNode* reverse(ListNode* head)
{
	// 순회 포인터로 p, q, r을 사용
	ListNode* p, * q, * r;
	p = head; // p는 역순으로 만들 리스트
	q = NULL; // q는 역순으로 만들 노드

	while (p != NULL) {
		r = q; // r은 역순으로 된 리스트. r은 q, q는 p를 차례로 따라간다. 
		q = p;
		p = p->link;
		q->link = r; // q의 링크 방향을 바꾼다. 
	}
	return q; // q는 역순으로 된 리스트의 헤드 포인터
}
int is_in_list(ListNode* head, element item)
{
	ListNode* p = head;

	while (p != NULL) {
		if (p->data == item)
			return 1;
		p = p->link;
	}
	return 0;
}
int get_length(ListNode* head)
{
	ListNode* p = head;
	int i = 0;

	while (p != NULL) {
		p = p->link;
		i++;
	}

	return i;
}
int get_total(ListNode* head)
{
	ListNode* p;
	int sum = 0;

	for (p = head; p != NULL; p = p->link) {
		sum += p->data;
	}

	return sum;
}
element get_entry(ListNode* head, int pos)
{
	ListNode* p = head;
	int i;

	for (i = 0; i < pos; i++)
		p = p->link;

	return p->data;
}
ListNode* delete_by_key(ListNode* head, int key)
{
	ListNode* p = head;
	ListNode* pre = NULL;
	ListNode* removed;
	int isin = 0;

	if (is_in_list(head, key) == 0) {
		printf("아이템 %d는 보유하고 있지 않습니다.\n", key);
		return head;
	}

	if (p->data == key)
		return delete_first(head);
	else {
		while (p != NULL) {
			pre = p;
			p = p->link;
			if (p->data == key) {
				removed = p;
				pre->link = p->link;
				free(removed);

				break;
			}
		}
		return head;
	}


}
ListNode* insert_pos(ListNode* head, int pos, element value)
{
	ListNode* p = head;
	ListNode* put = (ListNode*)malloc(sizeof(ListNode));
	put->data = value;

	if (pos == 1) {//노드가 하나도 없을 경우, pos가 1일 경우 
		put->link = p;
		head = put;
	}
	else {//노드가 하나 이상, pos가 1이상일 경우
		for (int i = 0; i < pos - 2; i++) //pos - 2번 반복
			p = p->link;
		put->link = p->link;
		p->link = put;
	}
	return head;
}
ListNode* delete_pos(ListNode* head, int pos)
{
	ListNode* p = head;
	ListNode* pre = NULL;
	ListNode* removed;

	if (pos == 1) {
		head = p->link;
		removed = p;
		free(removed);
	}
	else {
		for (int i = 0; i < pos - 1; i++) {//pos - 1번 반복
			pre = p;
			p = p->link;
		}
		pre->link = p->link;
		removed = p;
		free(removed);
	}
	return head;
}
//아이템 추가 함수
void add_item(ListNode** phead, int new_item)
{
	if (get_total(*phead) + new_item > 100)
		printf("최대 무게<100kg> 초과로 아이템 %d를 추가할 수 없음\n", new_item);
	else
		*phead = insert_first(*phead, new_item);
}
void display(ListNode* head)
{
	ListNode* p;
	printf("< ");
	for (p = head; p != NULL; p = p->link)
		printf("%d ", p->data);
	printf(">\n");
}
int main(void)
{
	ListNode* list = NULL;
	char choice;
	int weight;

	printf("enter a(dd), d(elete) or q(uit): ");
	scanf(" %c", &choice);

	while (choice != 'q') {
		switch (choice) {
		case 'a':
			printf("enter the weight of the item: ");
			scanf("%d", &weight);

			add_item(&list, weight);
			display(list);

			break;
		case 'd':
			printf("enter the weight of the item: ");
			scanf("%d", &weight);

			list = delete_by_key(list, weight);
			display(list);
		}
		printf("enter a(dd), d(elete) or q(uit): ");
		scanf(" %c", &choice);

	}
}