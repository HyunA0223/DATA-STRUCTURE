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
	if (head == NULL) // 공백 리스트이면
		head = p;
	else {
		while (temp->link != 0)
			temp = temp->link;
		temp->link = p;
	}
	return head; // 변경된 헤드 포인터 반환
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

char askChoice(void) {
	char choice;
	printf("------------------------------\n");
	printf("a: 텍스트 끝에 라인 추가\n");
	printf("i: 라인 번호로 라인 추가\n");
	printf("d: 라인 번호로 라인 삭제\n");
	printf("v: 라인 번호로 해당 라인 출력\n");
	printf("p: 전체 텍스트 출력\n");
	printf("q: 끝\n");
	printf("메뉴 선택:"); scanf("%c", &choice);
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
			printf("텍스트 끝에 삽입할 라인: ");
			getchar();
			fgets(newElement.line, MAX_CHAR_PER_LINE, stdin);

			list = insert_last(list, newElement);
			display_te(list);

			break;
		case 'i':
			printf("삽입할 라인 번호: ");
			scanf("%d", &lineNb);
			printf("삽입할 라인: ");
			getchar();
			fgets(newElement.line, MAX_CHAR_PER_LINE, stdin);

			list = insert_pos(list, lineNb, newElement);
			display_te(list);

			break;
		case 'd':
			printf("삭제할 라인 번호: ");
			scanf("%d", &lineNb);

			getchar();
			list = delete_pos(list, lineNb);
			display_te(list);

			break;
		case 'v'://여기부터 수정 다시
			printf("출력할 라인 번호: ");
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