#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "minheap.h"
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000 /* ���Ѵ� (������ ���� ���) */

typedef struct GraphType {
	int n; // ������ ����
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES];/* �����������κ����� �ִܰ�� �Ÿ� */
int found[MAX_VERTICES]; /* �湮�� ���� ǥ�� */
int previous[MAX_VERTICES];

/*  */
void read_graph(GraphType* g, char* filename)
{
	// ����
	int number, u, v, dist;
	element e;
	FILE* fp;
	fp = fopen(filename, "rt");
	if (fp == NULL)
	{
		printf("file %s open error!\n", filename);
		return;
	}

	// �ڵ� ����
	fscanf(fp, "%d\n", &number);
	g->n = number;
	while (fscanf(fp, "%d %d %d\n", &u, &v, &dist) != EOF) {
		g->weight[u][v] = dist;
		g->weight[v][u] = dist;
	}

	fclose(fp);
}

/*  */
void write_graph(GraphType* g, char* filename)
{
	// ����
	int i, j;
	FILE* fp;

	if (filename == NULL) fp = stdout;
	else {
		fp = fopen(filename, "wt");
		if (fp == NULL)
		{
			printf("file %s open error!\n", filename);
			return;
		}
	}

	// �ڵ� ����
	fprintf(fp, "%d\n", g->n);
	for (i = 0; i < g->n; i++) {
		for (j = i; j < g->n; j++) {
			if (g->weight[i][j] != INF)
				fprintf(fp, "%d %d %d\n", i, j, g->weight[i][j]);
		}
	}

	if (filename != NULL) fclose(fp);
}

// �׷��� �ʱ�ȭ 
void graph_init(GraphType* g)
{
	// ����
	int i, j;

	g->n = 0;
	for (i = 0; i < MAX_VERTICES; i++)
		for (j = 0; j < MAX_VERTICES; j++)
			g->weight[i][j] = INF;
}

//���õ��� ����, ���� ���� distance�� ���� index�� ��ȯ
int choose(int distance[], int n, int found[])
{
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;

	for (i = 0; i < n; i++)
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}

	return minpos;
}

void print_path(int start, int end)
{
	if (start == end)
		printf("%d ", start);
	else {
		print_path(start, previous[end]);
		printf("-> %d ", end);
	}
}
void shortest_path(GraphType* g, int start)
{
	int i, u, w;

	for (i = 0; i < g->n; i++) /* �ʱ�ȭ */
	{
		distance[i] = g->weight[start][i];
		found[i] = FALSE;
		previous[i] = start;
	}

	found[start] = TRUE; /* ���� ���� �湮 ǥ�� */
	distance[start] = 0;

	for (i = 0; i < g->n - 1; i++) {
		u = choose(distance, g->n, found);
		found[u] = TRUE;

		print_path(start, u); // ���� ��� ���
		printf(" (%d)\n", distance[u]); // �Ÿ� ���

		for (w = 0; w < g->n; w++)
			if (!found[w])
				if (distance[u] + g->weight[u][w] < distance[w]) {
					distance[w] = distance[u] + g->weight[u][w];
					previous[w] = u; // ���� ��� ����
				}
		print_path(start, u);
	}
}


main()
{
	GraphType g, t;		// �Է� �׷���, ��� Ʈ��

	graph_init(&g);
	read_graph(&g, "input.txt");

	shortest_path(&g, 0);

	printf("���Ϸ� ���:\n");
	write_graph(&t, "output.txt");
	write_graph(&t, NULL);	// to stdout
}