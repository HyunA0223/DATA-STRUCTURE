#include <stdio.h>
#include <stdlib.h>
#define MAX_CHAR_PER_LINE 100 

typedef struct {
	char line[MAX_CHAR_PER_LINE];
} element;
typedef struct ListNode {
	element data;
	struct ListNode* link;
} ListNode;

ListNode* insert_last(ListNode* head, element value)
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
element get_entry(ListNode* head, int pos)
{
	ListNode* p = head;
	int i;

	for (i = 0; i < pos - 1; i++)
		p = p->link;

	return p->data;
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

char askChoice(void) {
	char choice;
	printf("------------------------------\n");
	printf("a: �ؽ�Ʈ ���� ���� �߰�\n");
	printf("i: ���� ��ȣ�� ���� �߰�\n");
	printf("d: ���� ��ȣ�� ���� ����\n");
	printf("v: ���� ��ȣ�� �ش� ���� ���\n");
	printf("p: ��ü �ؽ�Ʈ ���\n");
	printf("q: ��\n");
	printf("�޴� ����:"); scanf("%c", &choice);
	return choice;
}

void display_te(ListNode* head)
{
	ListNode* p;
	int i = 0;

	printf("----------text edited---------\n");
	for (p = head; p != NULL; p = p->link) {
		printf("(%d) %s", ++i, p);
	}
}

int main(void) // 3)
{
	ListNode* list = NULL;
	char choice;
	int lineNb;
	element newElement;
	while ((choice = askChoice()) != 'q') {
		switch (choice) {
		case 'a':
			printf("�ؽ�Ʈ ���� ������ ����: ");
			getchar();
			fgets(newElement.line, MAX_CHAR_PER_LINE, stdin);

			list = insert_last(list, newElement);
			display_te(list);

			break;
		case 'i':
			printf("������ ���� ��ȣ: ");
			scanf("%d", &lineNb);
			printf("������ ����: ");
			getchar();
			fgets(newElement.line, MAX_CHAR_PER_LINE, stdin);

			list = insert_pos(list, lineNb, newElement);
			display_te(list);

			break;
		case 'd':
			printf("������ ���� ��ȣ: ");
			scanf("%d", &lineNb);

			getchar();
			list = delete_pos(list, lineNb);
			display_te(list);

			break;
		case 'v'://������� ���� �ٽ�
			printf("����� ���� ��ȣ: ");
			scanf("%d", &lineNb);

			getchar();
			printf("(%d) %s", lineNb, get_entry(list, lineNb).line);

			break;
		case 'p':
			getchar();
			display_te(list);
		}
		fflush(stdin);
	}
}