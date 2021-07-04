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
// ���� ��ȸ
void inorder(TreeNode* root) {
	if (root) {
		inorder(root->left);// ���ʼ���Ʈ�� ��ȸ
		printf("-------------------------------\n");
		printf("�й� : %d\n", root->data.id);
		printf("�̸� : %s\n", root->data.name);
		printf("��ȭ��ȣ : %s\n", root->data.tel);
		printf("�а� : %s\n", root->data.dept);
		inorder(root->right);// �����ʼ���Ʈ�� ��ȸ
	}
}
//Ž��(��ȯ)
TreeNode* search(TreeNode* node, int id)
{
	if (node == NULL) return NULL;
	if (id == node->data.id) return node;
	else if (id < node->data.id)
		return search(node->left, id);
	else
		return search(node->right, id);
}
//���� �Լ�
TreeNode* insert_node(TreeNode* root, element new)
{
	// Ʈ���� �����̸� ���ο� ��带 ��ȯ�Ѵ�.
	if (root == NULL) return new_node(new);
	// �׷��� ������ ��ȯ������ Ʈ���� ��������.
	if (new.id < root->data.id)
		root->left = insert_node(root->left, new);
	else if (new.id > root->data.id)
		root->right = insert_node(root->right, new);
	// ����� ��Ʈ �����͸� ��ȯ�Ѵ�.
	return root;
}
TreeNode* min_value_node(TreeNode* node)
{
	TreeNode* current = node;
	while (current->left != NULL) // �� ���� �ܸ� ��带 ã���� ������
		current = current->left;
	return current;
}
// ���� �Լ�
TreeNode* delete_node(TreeNode* root, int id)
{
	TreeNode* temp;
	if (root == NULL) return root;
	// ���� Ű�� ��Ʈ���� ������ ���� ���� Ʈ���� �ִ� ����
	if (id < root->data.id)
		root->left = delete_node(root->left, id);
	// ���� Ű�� ��Ʈ���� ũ�� ������ ���� Ʈ���� �ִ� ����
	else if (id > root->data.id)
		root->right = delete_node(root->right, id);
	// Ű�� ��Ʈ�� ������ �� ��带 �����ϸ� ��
	else {
		// ù ��°�� �� ��° ���
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
		// �� ��° ���
		temp = min_value_node(root->right);
		// �߿� ��ȸ�� �İ� ��带 �����Ѵ�.
		root->data = temp->data;
		// �߿� ��ȸ�� �İ� ��带 �����Ѵ�.
		root->right = delete_node(root->right, temp->data.id);
	}
	return root;
}
//������ȸ ���
void preorder(TreeNode* root)
{
	if (root != NULL) {
		printf("-------------------------------\n");
		printf("�й� : %d\n", root->data.id);
		printf("�̸� : %s\n", root->data.name);
		printf("��ȭ��ȣ : %s\n", root->data.tel);
		printf("�а� : %s\n", root->data.dept);
		preorder(root->left);
		preorder(root->right);
	}
}
//Ʈ���� ���� ���
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
//����� ���� ��ȯ
int get_node_count(TreeNode* node)
{
	int count = 0;

	if (node != NULL)
		count = 1 + get_node_count(node->left) + get_node_count(node->right);

	return count;
}
//���� ū �� ���
int get_maximum(TreeNode* node)
{
	while (node->right != NULL)
		node = node->right;

	return node->data.id;
}
//���� ���� �� ���
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
			printf("�й� �Է�: ");
			scanf("%d", &newPerson.id);

			getchar();
			printf("�̸� �Է�: ");
			scanf(" %s", newPerson.name);

			getchar();
			printf("��ȭ��ȣ �Է�: ");
			scanf(" %s", newPerson.tel);

			getchar();
			printf("�а� �Է�: ");
			scanf(" %s", newPerson.dept);

			root = insert_node(root, newPerson);
			break;
		case 'd':
			printf("������ �й� �Է�: ");
			scanf("%d", &newPerson.id);
			root = delete_node(root, newPerson.id);
			break;
		case 's':
			printf("Ž���� �й� �Է�: ");
			scanf("%d", &newPerson.id);
			if (search(root, newPerson.id) != NULL) {
				searchNode = search(root, newPerson.id);
				printf("-------------------------------\n");
				printf("�й� : %d\n", searchNode->data.id);
				printf("�̸� : %s\n", searchNode->data.name);
				printf("��ȭ��ȣ : %s\n", searchNode->data.tel);
				printf("�а� : %s\n", searchNode->data.dept);
			}
			else
				printf("id�� %d�� �л��� �����ϴ�\n", newPerson.id);
			printf("\n");
			break;
		case 'p':
			printf("�л� ���� �й� �� ���\n");
			inorder(root);
			printf("\n");
			break;
		case 'h':
			printf("Ʈ���� ���̴� %d\n", get_height(root));
			break;
		case 'c':
			printf("���� ����� �л��� �� ���� %d\n", get_node_count(root));
			break;
		}

		getchar();
		printf("Enter i(nsert), d(elete), s(earch), p(rint), h(eight), c(ount), q(uit): ");
		scanf(" %c", &choice);
	}
}