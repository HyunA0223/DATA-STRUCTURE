#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode { // ��� Ÿ��
	element data;
	struct ListNode* link;
} ListNode;

// ���� ó�� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	//exit(1);
}

// ��� pre �ڿ� ���ο� ��� ����
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
	p->link = head; // ��� �������� ���� ���� //(3)
	head = p; // ��� ������ ���� //(4)

	return head; // ����� ��� ������ ��ȯ
}
ListNode* insert_last(ListNode* head, int value)
{
	ListNode* temp = head;
	ListNode* p = (ListNode*)malloc(sizeof(ListNode)); //(1)

	p->data = value;
	p->link = NULL;
	// (2)
	if (head == NULL) // ���� ����Ʈ�̸�
		head = p;
	else {
		while (temp->link != 0)
			temp = temp->link;
		temp->link = p;
	}
	return head; // ����� ��� ������ ��ȯ
}
// pre�� ����Ű�� ����� ���� ��带 �����Ѵ�. ListNode* delete_next(ListNode *head, ListNode *pre)
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
		error("������ �׸��� ����");
	removed = head; // (1)
	head = removed->link; // (2)
	free(removed); // (3)

	return head; // (4)
}
ListNode* delete_last(ListNode* head)
{
	ListNode* temp = head;
	ListNode* prevTemp = NULL;
	ListNode* removed; //���ʿ�

	if (head == NULL)
		error("������ �׸��� ����");
	if (head->link == NULL) { // �ϳ��� ���
		free(temp);
		head = NULL;
	}
	else { // �� �̻��� ���
		while (temp->link != NULL) {
			prevTemp = temp;
			temp = temp->link;
		}
		prevTemp->link = NULL;
		free(temp);

		return head; // �״��
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
		if (p->data == x) return p; // Ž�� ����
		p = p->link;
	}

	return NULL; // Ž�� ������ ��� NULL ��ȯ
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
	// ��ȸ �����ͷ� p, q, r�� ���
	ListNode* p, * q, * r;
	p = head; // p�� �������� ���� ����Ʈ
	q = NULL; // q�� �������� ���� ���

	while (p != NULL) {
		r = q; // r�� �������� �� ����Ʈ. r�� q, q�� p�� ���ʷ� ���󰣴�. 
		q = p;
		p = p->link;
		q->link = r; // q�� ��ũ ������ �ٲ۴�. 
	}
	return q; // q�� �������� �� ����Ʈ�� ��� ������
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
		printf("������ %d�� �����ϰ� ���� �ʽ��ϴ�.\n", key);
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

	if (pos == 1) {//��尡 �ϳ��� ���� ���, pos�� 1�� ��� 
		put->link = p;
		head = put;
	}
	else {//��尡 �ϳ� �̻�, pos�� 1�̻��� ���
		for (int i = 0; i < pos - 2; i++) //pos - 2�� �ݺ�
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
		for (int i = 0; i < pos - 1; i++) {//pos - 1�� �ݺ�
			pre = p;
			p = p->link;
		}
		pre->link = p->link;
		removed = p;
		free(removed);
	}
	return head;
}
//������ �߰� �Լ�
void add_item(ListNode** phead, int new_item)
{
	if (get_total(*phead) + new_item > 100)
		printf("�ִ� ����<100kg> �ʰ��� ������ %d�� �߰��� �� ����\n", new_item);
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