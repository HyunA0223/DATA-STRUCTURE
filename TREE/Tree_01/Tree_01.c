#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define TRUE 1
#define FALSE 0

typedef struct TreeNode {
	int key;
	struct TreeNode* left, * right;
} TreeNode;

TreeNode* new_node(int item)
{
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}
void inorder(TreeNode* root) { // ���� ��ȸ
	if (root) {
		inorder(root->left);// ���ʼ���Ʈ�� ��ȸ
		printf("[%d] ", root->key); // ��� �湮
		inorder(root->right);// �����ʼ���Ʈ�� ��ȸ
	}
}
//Ž��(��ȯ)
TreeNode* search(TreeNode* node, int key)
{
	if (node == NULL) return NULL;
	if (key == node->key) return node;
	else if (key < node->key)
		return search(node->left, key);
	else
		return search(node->right, key);
}
TreeNode* insert_node(TreeNode* root, int key)
{
	// Ʈ���� �����̸� ���ο� ��带 ��ȯ�Ѵ�.
	if (root == NULL) return new_node(key);
	// �׷��� ������ ��ȯ������ Ʈ���� ��������.
	if (key < root->key)
		root->left = insert_node(root->left, key);
	else if (key > root->key)
		root->right = insert_node(root->right, key);
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
TreeNode* delete_node(TreeNode* root, int key)
{
	TreeNode* temp;
	if (root == NULL) return root;
	// ���� Ű�� ��Ʈ���� ������ ���� ���� Ʈ���� �ִ� ����
	if (key < root->key)
		root->left = delete_node(root->left, key);
	// ���� Ű�� ��Ʈ���� ũ�� ������ ���� Ʈ���� �ִ� ����
	else if (key > root->key)
		root->right = delete_node(root->right, key);
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
		root->key = temp->key;
		// �߿� ��ȸ�� �İ� ��带 �����Ѵ�.
		root->right = delete_node(root->right, temp->key);
	}
	return root;
}
//������ȸ ���
void preorder(TreeNode* root)
{
	if (root != NULL) {
		printf("%d ", root->key);
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

	return node->key;
}
//���� ���� �� ���
int get_minimum(TreeNode* node)
{
	while (node->left != NULL)
		node = node->left;

	return node->key;
}

int main(void)
{
	TreeNode* root = NULL;
	TreeNode* tmp = NULL;
	char choice;
	int key;

	printf("Enter i(nsert), d(elete), s(earch), p(rint), h(eight), c(ount), m(ax), n(min), q(uit): ");
	scanf(" %c", &choice);

	while (choice != 'q') {
		switch (choice) {
		case 'i':
			printf("������ key�� �Է�: ");
			scanf("%d", &key);
			root = insert_node(root, key);
			break;
		case 'd':
			printf("������ key�� �Է�: ");
			scanf("%d", &key);
			root = delete_node(root, key);
			break;
		case 's':
			printf("Ž���� key�� �Է�: ");
			scanf("%d", &key);
			if (search(root, key) != NULL)
				printf("����\n");
			else
				printf("����\n");
			break;
		case 'p':
			preorder(root);
			printf("\n");
			break;
		case 'h':
			printf("Ʈ���� ���̴� %d\n", get_height(root));
			break;
		case 'c':
			printf("����� ������ %d\n", get_node_count(root));
			break;
		case 'm':
			printf("���� ū ���� %d\n", get_maximum(root));
			break;
		case 'n':
			printf("���� ���� ���� %d\n", get_minimum(root));
			break;
		}

		getchar();
		printf("Enter i(nsert), d(elete), s(earch), p(rint), h(eight), c(ount), m(ax), n(min), q(uit): ");
		scanf(" %c", &choice);
	}
}