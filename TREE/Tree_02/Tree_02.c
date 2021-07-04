#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define TRUE 1
#define FALSE 0
#define MAX_STRING 100

typedef struct {
	int id;
	char name[MAX_STRING];
	char tel[MAX_STRING];
	char dept[MAX_STRING];
} element;

typedef struct TreeNode {
	element data;
	struct TreeNode* left, * right;
} TreeNode;

TreeNode* new_node(element new)
{
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->data = new;
	temp->left = temp->right = NULL;
	return temp;
}
// 중위 순회
void inorder(TreeNode* root) {
	if (root) {
		inorder(root->left);// 왼쪽서브트리 순회
		printf("-------------------------------\n");
		printf("학번 : %d\n", root->data.id);
		printf("이름 : %s\n", root->data.name);
		printf("전화번호 : %s\n", root->data.tel);
		printf("학과 : %s\n", root->data.dept);
		inorder(root->right);// 오른쪽서브트리 순회
	}
}
//탐색(순환)
TreeNode* search(TreeNode* node, int id)
{
	if (node == NULL) return NULL;
	if (id == node->data.id) return node;
	else if (id < node->data.id)
		return search(node->left, id);
	else
		return search(node->right, id);
}
//삽입 함수
TreeNode* insert_node(TreeNode* root, element new)
{
	// 트리가 공백이면 새로운 노드를 반환한다.
	if (root == NULL) return new_node(new);
	// 그렇지 않으면 순환적으로 트리를 내려간다.
	if (new.id < root->data.id)
		root->left = insert_node(root->left, new);
	else if (new.id > root->data.id)
		root->right = insert_node(root->right, new);
	// 변경된 루트 포인터를 반환한다.
	return root;
}
TreeNode* min_value_node(TreeNode* node)
{
	TreeNode* current = node;
	while (current->left != NULL) // 맨 왼쪽 단말 노드를 찾으러 내려감
		current = current->left;
	return current;
}
// 삭제 함수
TreeNode* delete_node(TreeNode* root, int id)
{
	TreeNode* temp;
	if (root == NULL) return root;
	// 만약 키가 루트보다 작으면 왼쪽 서브 트리에 있는 것임
	if (id < root->data.id)
		root->left = delete_node(root->left, id);
	// 만약 키가 루트보다 크면 오른쪽 서브 트리에 있는 것임
	else if (id > root->data.id)
		root->right = delete_node(root->right, id);
	// 키가 루트와 같으면 이 노드를 삭제하면 됨
	else {
		// 첫 번째나 두 번째 경우
		if (root->left == NULL) {
			TreeNode* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			TreeNode* temp = root->left;
			free(root);
			return temp;
		}
		// 세 번째 경우
		temp = min_value_node(root->right);
		// 중외 순회시 후계 노드를 복사한다.
		root->data = temp->data;
		// 중외 순회시 후계 노드를 삭제한다.
		root->right = delete_node(root->right, temp->data.id);
	}
	return root;
}
//전위순회 출력
void preorder(TreeNode* root)
{
	if (root != NULL) {
		printf("-------------------------------\n");
		printf("학번 : %d\n", root->data.id);
		printf("이름 : %s\n", root->data.name);
		printf("전화번호 : %s\n", root->data.tel);
		printf("학과 : %s\n", root->data.dept);
		preorder(root->left);
		preorder(root->right);
	}
}
//트리의 높이 출력
int get_height(TreeNode* node)
{
	int left, right;

	if (node == NULL)
		return 0;

	left = get_height(node->left);
	right = get_height(node->right);

	if (left > right)
		return left + 1;
	else
		return right + 1;
}
//노드의 개수 반환
int get_node_count(TreeNode* node)
{
	int count = 0;

	if (node != NULL)
		count = 1 + get_node_count(node->left) + get_node_count(node->right);

	return count;
}
//가장 큰 값 출력
int get_maximum(TreeNode* node)
{
	while (node->right != NULL)
		node = node->right;

	return node->data.id;
}
//가장 작은 값 출력
int get_minimum(TreeNode* node)
{
	while (node->left != NULL)
		node = node->left;

	return node->data.id;
}

int main(void)
{
	TreeNode* root = NULL;
	TreeNode* searchNode = NULL;
	element newPerson;
	char choice;

	printf("Enter i(nsert), d(elete), s(earch), p(rint), h(eight), c(ount), q(uit): ");
	scanf(" %c", &choice);

	while (choice != 'q') {
		switch (choice) {
		case 'i':
			printf("학번 입력: ");
			scanf("%d", &newPerson.id);

			getchar();
			printf("이름 입력: ");
			scanf(" %s", newPerson.name);

			getchar();
			printf("전화번호 입력: ");
			scanf(" %s", newPerson.tel);

			getchar();
			printf("학과 입력: ");
			scanf(" %s", newPerson.dept);

			root = insert_node(root, newPerson);
			break;
		case 'd':
			printf("삭제할 학번 입력: ");
			scanf("%d", &newPerson.id);
			root = delete_node(root, newPerson.id);
			break;
		case 's':
			printf("탐색할 학번 입력: ");
			scanf("%d", &newPerson.id);
			if (search(root, newPerson.id) != NULL) {
				searchNode = search(root, newPerson.id);
				printf("-------------------------------\n");
				printf("학번 : %d\n", searchNode->data.id);
				printf("이름 : %s\n", searchNode->data.name);
				printf("전화번호 : %s\n", searchNode->data.tel);
				printf("학과 : %s\n", searchNode->data.dept);
			}
			else
				printf("id가 %d인 학생은 없습니다\n", newPerson.id);
			printf("\n");
			break;
		case 'p':
			printf("학생 정보 학번 순 출력\n");
			inorder(root);
			printf("\n");
			break;
		case 'h':
			printf("트리의 높이는 %d\n", get_height(root));
			break;
		case 'c':
			printf("현재 저장된 학생의 총 수는 %d\n", get_node_count(root));
			break;
		}

		getchar();
		printf("Enter i(nsert), d(elete), s(earch), p(rint), h(eight), c(ount), q(uit): ");
		scanf(" %c", &choice);
	}
}