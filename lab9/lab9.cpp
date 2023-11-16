#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <locale.h>
#include <queue>

using namespace std;
queue<int>Q;

void DFSD(vector < vector < int>>G, int s, vector<int>& dist, int d, int n = 0) {
	clock_t start = clock();
	dist[s] = n;

	for (int i = 1; i <= G.size() - 1; ++i) {
		if (G[s][i] == 1 and dist[i] == -1) {
			DFSD(G, i, dist, n + 1);
		}
	}
	clock_t end = clock();
	if (dist[d] == -1) {
		printf("======================\n");
		printf("Пути отсутствуют!\n");
		printf("======================\n");
	}

	else {
		printf("========================================\n");
		printf("Путь %d-> %d по МАТРИЦЕ(обход в глубину): %d\n",s, d, dist[d]);
		printf("========================================\n");

	}
	printf("Время работы алгоритма: ");
	printf("%f\n", (double)(end - start) / CLOCKS_PER_SEC);
	printf("\n\n");
}

void DFSD_List(vector < vector < int>>G, int s, vector<int>& dist,int d, int n = 0) {
	clock_t start = clock();
	dist[s] = n;

	for (int neighbor : G[s]) {
		if (dist[neighbor] == -1) {
			DFSD_List(G, neighbor, dist, n + 1);
		}
	}
	clock_t end = clock();
	if (dist[d] == -1) {
		printf("======================\n");
		printf("Пути отсутствуют!\n");
		printf("======================\n");
	}

	else {
		printf("========================================\n");
		printf("Путь %d-> %d по СПИСКУ(обход в глубину): %d\n", s, d, dist[d]);
		printf("========================================\n");

	}
	printf("Время работы алгоритма: ");
	printf("%f\n", (double)(end - start) / CLOCKS_PER_SEC);
	printf("\n\n");
}

void list_BFS(int s, vector < vector < int>>adjacency_list, vector<int>& dist, int d) {
	clock_t start = clock();
	dist[s] = 0;
	int c = s;
	Q.push(s);
	while (!Q.empty()) {
		s = Q.front();
		Q.pop();
		s + 1;
		for (int i : adjacency_list[s]) { //добавляем всех непосещённых соседей.
			if (dist[i] != 1) {
				Q.push(i);
				dist[i] = dist[s] + 1;
			}

		}
	}
	clock_t end = clock();
	if (dist[d] == -1) {
		printf("======================\n");
		printf("Пути отсутствуют!\n");
		printf("======================\n");
	}

	else {
		printf("========================================\n");
		printf("Путь %d-> %d по СПИСКУ(обход в ширину): %d\n", c, d, dist[d]);
		printf("========================================\n");

	}
	printf("Время работы алгоритма: ");
	printf("%f\n", (double)(end - start) / CLOCKS_PER_SEC);
	printf("\n\n");
}

void BFSD1(const vector < vector < int>> G, int s, vector<int>& dist, int d ) {
	clock_t start = clock();
	int c = s;
	Q.push(s);
	dist[s] = 0;

	while (!Q.empty()) {
		s = Q.front();
		Q.pop();

		for (int i = 0; i < G.size(); ++i) {
			if (G[s][i] == 1 and dist[i] == -1) {
				Q.push(i);
				dist[i] = dist[s] + 1;
			}
		}
	}
	clock_t end = clock();
	if (dist[d] == -1) {
		printf("======================\n");
		printf("Пути отсутствуют!\n");
		printf("======================\n");
	}

	else {
		printf("========================================\n");
		printf("Путь %d-> %d по МАТРИЦЕ(обход в ширину): %d\n", c, d, dist[d]);
		printf("========================================\n");

	}
	printf("Время работы алгоритма: ");
	printf("%f\n", (double)(end - start) / CLOCKS_PER_SEC);
	printf("\n\n");
}


int swt = 0;
vector<vector<int>> cmej_mat(int num_vertices, double veroj) {
	vector<vector<int>> cmej_mat(num_vertices + 1, vector<int>(num_vertices + 1, 0));
	int cont = 0;
	for (int i = 1; i <= num_vertices; ++i) {
		for (int j = i + 1; j <= num_vertices; ++j) {
			if (static_cast<double>(rand()) / RAND_MAX < veroj) {
				cmej_mat[i][j] = 1;
				cmej_mat[j][i] = 1;
				cont++;
			}
		}
	}

	if (cont == 0) {
		swt = 1;
	}
	printf("Матрица смежности:\n");
	printf("-------------------\n");
	for (int i = 1; i <= num_vertices; ++i) {
		for (int j = 1; j <= num_vertices; ++j) {
			printf("%d ", cmej_mat[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	return cmej_mat;
}

	vector<vector<int>> list_cmej(vector<vector<int>> G) {
		int num_vertices = G.size() - 1;
		vector<vector<int>> adjacency_list(num_vertices + 1);
		for (int i = 1; i <= num_vertices; ++i) {
			for (int j = 1; j <= num_vertices; ++j) {
				if (G[i][j] == 1) {
					adjacency_list[i].push_back(j);
				}
			}
		}
		return adjacency_list;
	}

	void printList(vector<vector<int>>list) {
		printf("Список смежности:\n");
		printf("-------------------\n");
		for (int i = 1; i < list.size(); ++i) {
			printf("%d: ", i);
			for (int j : list[i]) {
				printf("%d ", j);
			}
			printf("\n");
		}
	}


int main() {
	setlocale(LC_ALL, "RUS");
	int num_vertices;
	double veroj = 0.5;
	int s,d;
	printf("Введите количество вершин: ");
	scanf("%d", &num_vertices);
	auto G = cmej_mat(num_vertices, veroj);
	auto list = list_cmej(G);
	printList(list);
	printf("\n\n");
	printf("\n\n");
	printf("Введите номер вершины из которой хотите попасть в другую ");
	scanf("%d", &s);
	printf("Введите номер вершины, в которую хотите попасть  ");
	scanf("%d", &d);
	printf("\n\n");
	srand(static_cast<unsigned int>(time(0)));
	
	vector<int> dist(G.size(),-1);
	if (swt == 1) {
		printf("\n Обход произвести нельзя!\n");
	}
	else {
		
		BFSD1(G,s,dist,d);
		list_BFS(s,G, dist, d);
		DFSD(G, s, dist, d);
		DFSD_List(G, s, dist, d);
	}

	return 0;


}
