#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
#define MAX_STRING 100

//������ ���� Ÿ�� ����
typedef char element;

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

int palindrome(char str[])
{
	StackType s;
	int i;
	int stop = 1;

	//���� �ʱ�ȭ
	init(&s);

	//str�� ���ڵ��� ���ÿ� �ִ´�
	for (i = 0; i < strlen(str); i++)
		push(&s, str[i]);

	//���ÿ��� �ϳ��� ���鼭 str�� ���ڵ�� ���ʷ� ��
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
		printf("palindrome �Դϴ�.\n");
	else
		printf("palindrome�� �ƴմϴ�.\n");
}