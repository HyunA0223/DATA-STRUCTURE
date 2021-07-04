#include <stdio.h>
#include <stdlib.h>
#include "queue.h"  // <------

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50

typedef struct GraphNode
{
	int vertex;
	struct GraphNode* link;
} GraphNode;

typedef struct GraphType {
	int n;	// 정점의 개수
	GraphNode* adj_list[MAX_VERTICES];
} GraphType;

// 그래프 초기화 
void graph_init(GraphType* g)
{
	int v;
	g->n = 0;
	for (v = 0; v < MAX_VERTICES; v++)
		g->adj_list[v] = NULL;
}
// 정점 삽입 연산
void insert_vertex(GraphType* g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;
}
// 간선 삽입 연산, v를 u의 인접 리스트에 삽입한다.
void insert_edge(GraphType* g, int u, int v)
{
	// 앞의 숙제코드에서
	GraphNode* node_u, * node_v;
	GraphNode* temp;
	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	node_u = (GraphNode*)malloc(sizeof(GraphNode));
	if (node_u == NULL) {
		fprintf(stderr, "메모리 할당 에러!\n"); return;
	}

	// 코드 삽입
	// u 에 v 를 매단다
	node_v = (GraphNode*)malloc(sizeof(GraphNode));
	node_v->vertex = v;
	node_v->link = g->adj_list[u];
	g->adj_list[u] = node_v;
	// v 에 u 를 매단다
	node_u = (GraphNode*)malloc(sizeof(GraphNode));
	node_u->vertex = u;
	node_u->link = g->adj_list[v];
	g->adj_list[v] = node_u;
}
int visited[MAX_VERTICES];


// 너비 우선 탐색(인접 리스트)
// 이 코드에 간선을 출력하기 위한 코드를 삽입하는 것이 HW6_2_2의 숙제이다
void bfs_list(GraphType* g, int v)
{
	GraphNode* w;
	QueueType q;
	init(&q);    				// 큐 초기 화 
	visited[v] = TRUE;      // 정점 v 방문 표시 
	enqueue(&q, v);			// 시작정점을 큐에 저장 
	while (!is_empty(&q)) {
		v = dequeue(&q);		// 큐에 저장된 정점 선택 
		for (w = g->adj_list[v]; w; w = w->link) //인접 정점 탐색
			if (!visited[w->vertex]) {	// 미방문 정점 탐색 
				printf("<%d %d>\n", v, w->vertex);//간선 출력
				visited[w->vertex] = TRUE;   // 방문 표시
				enqueue(&q, w->vertex);	//정점을 큐에 삽입
			}
	}
}

void read_graph(GraphType* g, char* filename)
{
	// 앞의 숙제 코드에서
	int number, u, v;
	GraphNode* node;
	FILE* fp;
	fp = fopen(filename, "rt");
	if (fp == NULL)
	{
		printf("file open error!\n");
		return;
	}

	// 코드 삽입
	node = (GraphNode*)malloc(sizeof(GraphNode));
	fscanf(fp, "%d\n", &g->n);
	while (fscanf(fp, "%d %d\n", &u, &v) != EOF)
		insert_edge(g, u, v);

	fclose(fp);
}
int main(void)
{
	GraphType graph;
	int u, v;

	graph_init(&graph);
	read_graph(&graph, "infile.txt");

	printf("Enter 정점:");
	scanf("%d", &v);

	bfs_list(&graph, v);
}