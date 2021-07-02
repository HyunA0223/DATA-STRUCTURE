#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct DListNode {	// ���߿��� ��� Ÿ��
	element data;
	struct DListNode* llink;
	struct DListNode* rlink;
} DListNode;

// ���� ���� ����Ʈ�� �ʱ�ȭ
void init(DListNode* phead)
{
	phead->llink = phead;
	phead->rlink = phead;
}

// ���� ���� ����Ʈ�� ��带 ���
void print_dlist(DListNode* phead)
{
	DListNode* p;
	for (p = phead->rlink; p != phead; p = p->rlink) {
		printf("<-| |%d| |-> ", p->data);
	}
	printf("\n");
}
// ���ο� �����͸� ��� before�� �����ʿ� �����Ѵ�.
void dinsert(DListNode* before, element data)
{
	DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
	newnode->data = data;

	newnode->llink = before;
	newnode->rlink = before->rlink;
	before->rlink->llink = newnode;
	before->rlink = newnode;
}
// ��� removed�� �����Ѵ�.
void ddelete(DListNode* head, DListNode* removed)
{
	if (removed == head) return;

	removed->llink->rlink = removed->rlink;
	removed->rlink->llink = removed->llink;
	free(removed);
}
// ���� ���� ����Ʈ�� ��带 �������� ���
void print_reverse_dlist(DListNode* phead)
{
	DListNode* p;
	for (p = phead->llink; p != phead; p = p->llink) {
		printf("<-| |%d| |-> ", p->data);
	}
	printf("\n");
}
//data�� ���� ��带 ��ȯ
DListNode* search(DListNode* head, element data)
{
	DListNode* p = head->rlink;

	for (p = head->rlink; p != head; p = p->rlink) {
		if (p->data == data)
			return p;
	}

	return NULL;
}
// ���� ���� ����Ʈ �׽�Ʈ ���α׷�
int main(void)
{
	DListNode* head = (DListNode*)malloc(sizeof(DListNode));
	init(head);
	printf("�߰� �ܰ�\n");

	// ó���� ����
	dinsert(head, 10);
	print_dlist(head);
	dinsert(head, 20);
	print_dlist(head);
	dinsert(head, 30);
	print_dlist(head);

	// �ڿ� �����Ϸ���?
	dinsert(head->llink, 99);
	print_dlist(head);

	printf("\n���� �ܰ�\n");
	// �տ����� ���� 
	ddelete(head, head->rlink);
	print_dlist(head);

	// �ڿ����� ���� 
	ddelete(head, head->llink);
	print_dlist(head);

	printf("\n�������� ���\n");
	print_reverse_dlist(head);

	printf("\ndata ���� ���� ����� data ���\n");
	printf("data 20�� ���� ��� %d\n", search(head, 20)->data);

	free(head);
	return 0;
}