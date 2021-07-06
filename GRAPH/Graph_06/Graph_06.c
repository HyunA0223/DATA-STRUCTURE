#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L

typedef struct GraphType {
	int n;	// 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int selected[MAX_VERTICES]; // 신장트리집합
int distance[MAX_VERTICES]; // 신장트리집합에서 u까지의 최소 거리
int connectedVertex[MAX_VERTICES]; // 다른쪽 정점 저장

// 최소신장트리에서 가장 가까운 정점  반환
int get_min_vertex(int n)
{
	int v, i;

	// 선택되지 않은 정점 중 첫번째를 v
	for (i = 0; i < n; i++)
		if (!selected[i]) {
			v = i;
			break;
		}

	// i가 선택되지 않았고, v보다 dist값이 작으면 v = i
	for (i = 0; i < n; i++)
		if (!selected[i] && (distance[i] < distance[v])) v = i;

	return v;
}

//
void prim(GraphType* g, int s)
{
	int i, j, u, v;

	// 거리를 큰 값(INF)로 초기화
	for (u = 0; u < g->n; u++) {
		distance[u] = INF;
		connectedVertex[u] = s;
	}

	// 시작 정점의 dist 값을 0으로 초기화
	distance[s] = 0;

	for (i = 0; i < g->n; i++) { // 정점의 수만큼 반복
		u = get_min_vertex(g->n); // 가장 작은 dist값을 갖는 정점을 u
		selected[u] = TRUE; // u를 최소신장트리에 넣음

		if (distance[u] == INF) return; // 비연결 그래프일 때(없어도 됨)

		for (v = 0; v < g->n; v++)
			if (g->weight[u][v] != INF) // u와 v가 연결되어있다면
				// 사이클이 아니고, u와 v간의 거리가 v의 dist 값보다 작을 경우
				if (!selected[v] && g->weight[u][v] < distance[v]) {
					distance[v] = g->weight[u][v]; // v의 dist값 변경
					connectedVertex[v] = u; // 반대쪽 정점
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