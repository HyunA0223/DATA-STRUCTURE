#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
#define MAX_STRING 100

//스택을 위한 타입 정의
typedef char element;

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

int palindrome(char str[])
{
	StackType s;
	int i;
	int stop = 1;

	//스택 초기화
	init(&s);

	//str의 문자들을 스택에 넣는다
	for (i = 0; i < strlen(str); i++)
		push(&s, str[i]);

	//스택에서 하나씩 빼면서 str의 문자들과 차례로 비교
	for (i = 0; i <= s.top; i++) {
		if (str[i] == s.data[s.top]) {
			pop(&s);
			return str[i] != s.data[s.top];
		}
		else {
			return str[i] == s.data[s.top];
			break;
		}
	}
}

void main()
{
	char word[MAX_STRING];

	printf("Enter a word to check palindrome: ");
	scanf("%s", word);

	if (palindrome(word))
		printf("palindrome 입니다.\n");
	else
		printf("palindrome이 아닙니다.\n");
}