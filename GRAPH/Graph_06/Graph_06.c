#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L

typedef struct GraphType {
	int n;	// ������ ����
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int selected[MAX_VERTICES]; // ����Ʈ������
int distance[MAX_VERTICES]; // ����Ʈ�����տ��� u������ �ּ� �Ÿ�
int connectedVertex[MAX_VERTICES]; // �ٸ��� ���� ����

// �ּҽ���Ʈ������ ���� ����� ����  ��ȯ
int get_min_vertex(int n)
{
	int v, i;

	// ���õ��� ���� ���� �� ù��°�� v
	for (i = 0; i < n; i++)
		if (!selected[i]) {
			v = i;
			break;
		}

	// i�� ���õ��� �ʾҰ�, v���� dist���� ������ v = i
	for (i = 0; i < n; i++)
		if (!selected[i] && (distance[i] < distance[v])) v = i;

	return v;
}

//
void prim(GraphType* g, int s)
{
	int i, j, u, v;

	// �Ÿ��� ū ��(INF)�� �ʱ�ȭ
	for (u = 0; u < g->n; u++) {
		distance[u] = INF;
		connectedVertex[u] = s;
	}

	// ���� ������ dist ���� 0���� �ʱ�ȭ
	distance[s] = 0;

	for (i = 0; i < g->n; i++) { // ������ ����ŭ �ݺ�
		u = get_min_vertex(g->n); // ���� ���� dist���� ���� ������ u
		selected[u] = TRUE; // u�� �ּҽ���Ʈ���� ����

		if (distance[u] == INF) return; // �񿬰� �׷����� ��(��� ��)

		for (v = 0; v < g->n; v++)
			if (g->weight[u][v] != INF) // u�� v�� ����Ǿ��ִٸ�
				// ����Ŭ�� �ƴϰ�, u�� v���� �Ÿ��� v�� dist ������ ���� ���
				if (!selected[v] && g->weight[u][v] < distance[v]) {
					distance[v] = g->weight[u][v]; // v�� dist�� ����
					connectedVertex[v] = u; // �ݴ��� ����
				}

		printf("\n(%d, %d) %d\n", connectedVertex[u], u, distance[u]);

		printf("selected[ ] = \t\t");
		for (j = 0; j < g->n; j++)
			printf("%d\t", selected[j]);

		printf("\ndistance[ ] = \t\t");
		for (j = 0; j < g->n; j++)
			printf("%d\t", distance[j]);
		printf("\n");
	}
}

int main(void)
{
	GraphType g = { 7,
	{{ 0, 29, INF, INF, INF, 10, INF },
	{ 29,  0, 16, INF, INF, INF, 15 },
	{ INF, 16, 0, 12, INF, INF, INF },
	{ INF, INF, 12, 0, 22, INF, 18 },
	{ INF, INF, INF, 22, 0, 27, 25 },
	{ 10, INF, INF, INF, 27, 0, INF },
	{ INF, 15, INF, 18, 25, INF, 0 } }
	};

	prim(&g, 0);
	return 0;
}