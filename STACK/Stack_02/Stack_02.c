#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 3
#define MAX_STRING 100

typedef struct {
	int num;
	char word[MAX_STRING];
}element;

typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
}StackType;

//���� �ʱ�ȭ �Լ�
void init(StackType* s)
{
	s->top = -1;
}

//���� ���� ���� �Լ�
int is_empty(StackType* s)
{
	return s->top == -1;
}

//��ȭ ���� ���� �Լ�
int is_full(StackType* s)
{
	return s->top == MAX_STACK_SIZE - 1;
}

//���� �Լ�
void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else
		s->data[++(s->top)] = item;
}

//���� �Լ�
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else
		return s->data[(s->top)--];
}

//��ũ �Լ�
element peek(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else
		return s->data[s->top];
}

//���� ��� �Լ�
void stack_print(StackType* s)
{
	int i;

	if (s->top == -1)
		printf("<empty>\n");
	else {
		printf("[%d, %s] <- top\n", s->data[s->top].num, s->data[s->top].word);
		for (i = s->top - 1; i >= 0; i--)
			printf("[%d, %s]\n", s->data[i].num, s->data[i].word);
	}
	printf("--\n");
}

void main()
{
	StackType s;
	element e;

	init(&s);
	stack_print(&s, &e);
	//(10, ten)����
	e.num = 10; strcpy(e.word, "ten");
	push(&s, e);
	stack_print(&s);
	//(20, twenty)����
	e.num = 20; strcpy(e.word, "twenty");
	push(&s, e);
	stack_print(&s);
	//(30, thirty)����
	e.num = 30; strcpy(e.word, "thirty");
	push(&s, e);
	stack_print(&s);
	//(40, forty)����
	e.num = 40; strcpy(e.word, "forty");
	push(&s, e);
	stack_print(&s);
	//����
	pop(&s);
	stack_print(&s);
	//(50, fifty)����
	e.num = 50; strcpy(e.word, "fifty");
	push(&s, e);
	stack_print(&s);
	//����
	pop(&s);
	stack_print(&s);
	//����
	pop(&s);
	stack_print(&s);
	//����
	pop(&s);
	stack_print(&s);
}