#include <stdio.h>
#define MAX_VERTICES 50

typedef struct GraphType {
    int n;
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int visited[MAX_VERTICES] = { 0 };

// 그래프 초기화 
void graph_init(GraphType* g)
{
    int r, c;
    g->n = 0;
    for (r = 0; r < MAX_VERTICES; r++)
        for (c = 0; c < MAX_VERTICES; c++)
            g->adj_mat[r][c] = 0;
}

//
void read_graph(GraphType* g, char* filename)
{
    // 앞의 숙제코드에서
    int number, u, v;
    FILE* fp;
    fp = fopen(filename, "rt");
    if (fp == NULL)
    {
        printf("file %s open error!\n", filename);
        return;
    }

    // 코드 삽입
    fscanf(fp, "%d\n", &g->n);
    while (fscanf(fp, "%d %d\n", &u, &v) != EOF) {
        if (u >= g->n || v >= g->n) {
            fprintf(stderr, "그래프: 정점 번호 오류");
            return;
        }

        // 코드 삽입
        g->adj_mat[u][v] = 1;
        g->adj_mat[v][u] = 1;
    }

    fclose(fp);
}

// 이 함수에 간선을 출력하기위한 코드를 삽입하는 것이 HW6_2_1의 요구이다
void dfs_mat(GraphType* g, int v)
{
    int w;
    visited[v] = 1;
    for (w = 0; w < g->n; w++)
        if ((g->adj_mat[v][w] == 1) && (visited[w] == 0)) { // u가 인접한 정점이고 u가 아직 방문되지 않았으면
            printf("<%d %d>\n", v, w); //간선 출력
            dfs_mat(g, w);
        }

}
int main(void)
{
    GraphType graph;
    int u, v;

    graph_init(&graph);
    read_graph(&graph, "infile.txt");
    //read_graph(&graph, "infile2.txt");

    printf("Enter 정점:");
    scanf("%d", &v);

    dfs_mat(&graph, v);
}
