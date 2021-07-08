#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "minheap.h"
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000 /* 무한대 (연결이 없는 경우) */

typedef struct GraphType {
	int n; // 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES];/* 시작정점으로부터의 최단경로 거리 */
int found[MAX_VERTICES]; /* 방문한 정점 표시 */
int previous[MAX_VERTICES];

/*  */
void read_graph(GraphType* g, char* filename)
{
	// 구현
	int number, u, v, dist;
	element e;
	FILE* fp;
	fp = fopen(filename, "rt");
	if (fp == NULL)
	{
		printf("file %s open error!\n", filename);
		return;
	}

	// 코드 삽입
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
	// 구현
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

	// 코드 삽입
	fprintf(fp, "%d\n", g->n);
	for (i = 0; i < g->n; i++) {
		for (j = i; j < g->n; j++) {
			if (g->weight[i][j] != INF)
				fprintf(fp, "%d %d %d\n", i, j, g->weight[i][j]);
		}
	}

	if (filename != NULL) fclose(fp);
}

// 그래프 초기화 
void graph_init(GraphType* g)
{
	// 구현
	int i, j;

	g->n = 0;
	for (i = 0; i < MAX_VERTICES; i++)
		for (j = 0; j < MAX_VERTICES; j++)
			g->weight[i][j] = INF;
}

//선택되지 않은, 가장 작은 distance를 갖는 index를 반환
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

	for (i = 0; i < g->n; i++) /* 초기화 */
	{
		distance[i] = g->weight[start][i];
		found[i] = FALSE;
		previous[i] = start;
	}

	found[start] = TRUE; /* 시작 정점 방문 표시 */
	distance[start] = 0;

	for (i = 0; i < g->n - 1; i++) {
		u = choose(distance, g->n, found);
		found[u] = TRUE;

		print_path(start, u); // 경유 노드 출력
		printf(" (%d)\n", distance[u]); // 거리 출력

		for (w = 0; w < g->n; w++)
			if (!found[w])
				if (distance[u] + g->weight[u][w] < distance[w]) {
					distance[w] = distance[u] + g->weight[u][w];
					previous[w] = u; // 경유 노드 저장
				}
		print_path(start, u);
	}
}


main()
{
	GraphType g, t;		// 입력 그래프, 결과 트리

	graph_init(&g);
	read_graph(&g, "input.txt");

	shortest_path(&g, 0);

	printf("파일로 출력:\n");
	write_graph(&t, "output.txt");
	write_graph(&t, NULL);	// to stdout
}