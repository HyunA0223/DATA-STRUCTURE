#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode { 	// ��� Ÿ��
	element data;
	struct ListNode* link;
} ListNode;

// ����Ʈ�� �׸� ���
void print_list(ListNode* head)
{
	ListNode* p;

	if (head == NULL) return;
	p = head->link;
	if (head->link == head) {
		printf("%d->����Ʈ�� ��", p->data);
	}
	else {
		do {
			printf("%d->", p->data);
			p = p->link;
		} while (p != head);
		printf("%d->����Ʈ�� ��", p->data); // ������ ��� ���
	}
	printf("\n");
}

ListNode* insert_first(ListNode* head, element data)
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->data = data;
	if (head == NULL) {
		head = node;
		node->link = head;
	}
	else {
		node->link = head->link;	// (1)
		head->link = node;		// (2)
	}
	return head;	// ����� ��� �����͸� ��ȯ�Ѵ�. 
}

ListNode* insert_last(ListNode* head, element data)
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->data = data;
	if (head == NULL) {
		head = node;
		node->link = head;
	}
	else {
		node->link = head->link;	// (1)
		head->link = node;		// (2)
		head = node;		// (3)
	}
	return head;	// ����� ��� �����͸� ��ȯ�Ѵ�. 
}

ListNode* delete_first(ListNode* head)
{
	ListNode* temp;
	if (head == NULL) {
		printf("����Ʈ�� ��� ������ ����\n");
		return NULL;
	}

	else if (head == head->link) {  // �� �ϳ��� ��尡 �������� 
		temp = head;
		head = NULL;
		free(temp);
	}
	else {
		temp = head->link;
		head->link = temp->link;
		free(temp);
	}
	return head;

}

ListNode* delete_last(ListNode* head)
{
	ListNode* p;
	ListNode* removed;

	if (head == NULL) {
		printf("����Ʈ�� ��� ������ ����\n");
		return NULL;
	}
	else if (head->link == head) {
		removed = head;
		head = NULL;
		free(removed);
	}
	else {
		removed = head;
		p = head->link;
		while (p->link != head)
			p = p->link;
		p->link = head->link;
		head = p;
		free(removed);
	}

	return head;
}

ListNode* search(ListNode* head, element data)
{
	ListNode* p;

	if (head == NULL) return NULL;
	p = head->link;
	do {
		if (p->data == data)
			return p;

		p = p->link;
	} while (p->link != head);

	return NULL;
}

int get_size(ListNode* head)
{
	ListNode* p = head->link;
	int size = 1;

	if (head == NULL) return 0;
	while (p != head) {
		p = p->link;
		size++;
	}
	return size;
}

// ���� ���� ����Ʈ �׽�Ʈ ���α׷�
int main(void)
{
	ListNode* head = NULL;

	// list = 10->20->30->40
	head = insert_last(head, 20);
	print_list(head);

	head = insert_last(head, 30);
	print_list(head);
	head = insert_last(head, 40);
	print_list(head);
	head = insert_first(head, 10);
	print_list(head);

	head = delete_first(head);
	print_list(head);

	head = delete_last(head);
	print_list(head);

	printf("data 30�� ���� ��� %d\n", search(head, 30)->data);

	printf("size == %d\n", get_size(head));

	return 0;
}