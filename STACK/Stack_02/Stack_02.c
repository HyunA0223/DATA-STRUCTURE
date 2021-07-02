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

//스택 초기화 함수
void init(StackType* s)
{
	s->top = -1;
}

//공백 상태 검출 함수
int is_empty(StackType* s)
{
	return s->top == -1;
}

//포화 상태 검출 함수
int is_full(StackType* s)
{
	return s->top == MAX_STACK_SIZE - 1;
}

//삽입 함수
void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else
		s->data[++(s->top)] = item;
}

//삭제 함수
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else
		return s->data[(s->top)--];
}

//피크 함수
element peek(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else
		return s->data[s->top];
}

//스택 출력 함수
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
	//(10, ten)삽입
	e.num = 10; strcpy(e.word, "ten");
	push(&s, e);
	stack_print(&s);
	//(20, twenty)삽입
	e.num = 20; strcpy(e.word, "twenty");
	push(&s, e);
	stack_print(&s);
	//(30, thirty)삽입
	e.num = 30; strcpy(e.word, "thirty");
	push(&s, e);
	stack_print(&s);
	//(40, forty)삽입
	e.num = 40; strcpy(e.word, "forty");
	push(&s, e);
	stack_print(&s);
	//삭제
	pop(&s);
	stack_print(&s);
	//(50, fifty)삽입
	e.num = 50; strcpy(e.word, "fifty");
	push(&s, e);
	stack_print(&s);
	//삭제
	pop(&s);
	stack_print(&s);
	//삭제
	pop(&s);
	stack_print(&s);
	//삭제
	pop(&s);
	stack_print(&s);
}