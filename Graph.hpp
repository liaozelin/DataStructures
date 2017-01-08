#ifndef GRAPH_H_
#define GRAPH_H_
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;

const int MAXSIZE = 100;
typedef char vertexInfo;

// undirected graph realized by adjacency matrix
class Graph {
private:
	int n, e;  // n is the number of vertexes, e is the number of edges
	vertexInfo info[MAXSIZE];
	int edges[MAXSIZE][MAXSIZE];
public:
	Graph() {
		memset(edges, 0, sizeof(edges));
	}
	~Graph() {}

	void createGraph() {
		cout << "Please input vertex number and edges number:\n";
		cin >> n >> e;
		cout << "Please input infomation(char) of vertexes:\n";
		for (int i = 0; i < n; ++i) {
			cin >> info[i];
		}
		cout << "Please input two vertexes of each edge:\n";
		int i, j, k;
		for (k = 0; k < e; ++k) {
			cin >> i >> j;
			edges[i][j] = 1;
			edges[j][i] = 1;
		}
	}

	void dfs() {
		bool* visited = new bool[n];
		memset(visited, false, sizeof(visited));
		cout << "Please input the start vertex of dfs(start from 0):\n";
		int i;
		cin >> i;
		cout << "Graph dfs: ";
		dfs_driver(i, visited);
		delete [] visited;
	}
	void dfs_driver(int i, bool* visited) {
		cout << info[i] << ' ';
		visited[i] = 1;
		for (int j = 0; j < n; ++j) {
			if (visited[j] == 0 && edges[i][j] != 0) dfs_driver(j, visited);
		}
	}

	void bfs() {
		queue<int> que;
		bool* visited = new bool[n];
		memset(visited, false, sizeof(visited));
		cout << "Please input the start vertex of bfs(start from 0):\n";
		int i;
		cin >> i;
		que.push(i);
		cout << "Graph bfs: ";
		while (!que.empty()) {
			int t = que.front();
			que.pop();
			if (visited[t] == 0) {
				cout << info[t] << ' ';
				visited[t] = 1;
				for (int j = 0; j < n; ++j) {
					if (visited[j] == 0 && edges[t][j] != 0)
						que.push(j);
				}
			}
		}
		delete [] visited;
	}
};

// undirected graph realized by adjacency list
class Graph_List {
private:
	struct EdgeNode {
		int index;
	 	EdgeNode* next;
	 	EdgeNode(int i, EdgeNode* n = NULL) : index(i), next(n) {}
	};
	struct VertexNode {
		vertexInfo info;
		EdgeNode* edges;
		VertexNode(vertexInfo i = '#') : info(i) {
			edges = new EdgeNode(-1);
		}
		~VertexNode() {
			while (this->edges->next != NULL) {
				EdgeNode* t = this->edges->next;
				this->edges->next = this->edges->next->next;
				delete t;
			}
			delete this->edges;
		}
	};

	VertexNode vertexes[MAXSIZE];
	int n, e;  // n is the number of vertexes, e is the number of edges

public:
	Graph_List() {}
	~Graph_List() {}

	void createGraph() {
		cout << "Please input the number of vertexes and the number of edges:\n";
		cin >> n >> e;
		cout << "Please input infomation(char) of each vertex:\n";
		for (int i = 0; i < n; ++i) {
			cin >> vertexes[i].info;
		}
		cout << "Please input two vertexes of each edge:\n";
		int i, j, k;
		for (k = 0; k < e; ++k) {
			cin >> i >> j;
			EdgeNode* newNode = new EdgeNode(j, vertexes[i].edges->next);
			vertexes[i].edges->next = newNode;
			EdgeNode* newNode_2 = new EdgeNode(i, vertexes[j].edges->next);
			vertexes[j].edges->next = newNode_2;
		}
	}

	void dfs() {
		bool* visited = new bool[n];
		memset(visited, false, sizeof(visited));
		cout << "Please input the start vertex of dfs(start from 0):\n";
		int i;
		cin >> i;
		cout << "Graph_List dfs: ";
		dfs_driver(i, visited);
		delete [] visited;
	}
	void dfs_driver(int i, bool* visited) {
		cout << vertexes[i].info << ' ';
		visited[i] = 1;
		EdgeNode* t = vertexes[i].edges->next;
		while (t != NULL) {
			if (visited[t->index] == 0) dfs_driver(t->index, visited);
			t = t->next;
		}
	}

	void bfs() {
		queue<int> que;
		bool* visited = new bool[n];
		memset(visited, false, sizeof(visited));
		cout << "Please input the start vertex of bfs(start from 0):\n";
		int i;
		cin >> i;
		que.push(i);
		cout << "Graph_List bfs: ";
		while (!que.empty()) {
			int i = que.front();
			que.pop();
			if (visited[i] == 0) {
				cout << vertexes[i].info << ' ';
				visited[i] = 1;
				EdgeNode* t = vertexes[i].edges->next;
				while (t != NULL) {
					if (visited[t->index] == 0) que.push(t->index);
					t = t->next;
				}
			}
		}
		delete [] visited;
	}
};

/* 拓扑排序只适用于有向无圈图
 * 思路:先找出任意一个入度为0的顶点,显示该顶点并将它及它的边从图中删除
 *      继续同样的操作 */
/* void topsort() {
    // 用数组储存入度
    int* indegree = new int[n];
    memset(indegree, 0, sizeof(indegree));
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n; ++i) {
            if (edges[i][j] != 0) indegree[j]++;
        }
    }

    queue<int> res;
    queue<int> zeroIndegree; // 储存入度为0的顶点
    for (int i = 0; i < n; ++i) {
        if (indegree[i] == 0) {
            zeroIndegree.push(i);
        }
    }

    while (!zeroIndegree.empty()) {
        int t = zeroIndegree.front();
        zeroIndegree.pop();
        for (int j = 0; j < n; ++i) {
            if (edges[t][j] != 0) { // 删除边(t,j), j顶点入度减一
                indegree[j]--;
                if (indegree[j] == 0) zeroIndegree.push(j);
            }
        }
        res.push(t);
    }

    if (res.size() != n) {
        cout << "The graph has a loop!\n";
    } else {
        while (!res.empty()) {
            cout << res.front() << ' ';
            res.pop();
        }
        cout << endl;
    }
}  */


/* 最短路径算法 */
/* 无权最短路径直接用bfs即可 */
/* 赋权最短路径用Dijkstra算法 */
/* previoueVertex[i]标记在最短路径中i的前一个顶点.
 * distance[i]标记在最短路径中起始点start到i的距离. 
 * const int NotAVertex = -1;
 * const int Inifity = 9999; */

/* void Dijkstra(int start) {
    memset(previousVertex, NotAVertex, sizeof(previousVertex));
    memset(distance, Inifity, sizeof(distance));
    memset(visited, false, sizeof(visited));
    distance[start] = 0;
    while (true) {
        double min = Inifity;
        int minIndex = -1;
        int k;
        for (k = 0; k < n; ++k)
            if (visited[k] == 0 && min > distance[k]) {
                min = distance[k];
                minIndex = k;
            }
        // minIndex == -1说明每个节点都遍历过了(没有满足要求的节点)
        if (minIndex == -1) break;
        // 否则,找到路径最短节点
        visited[minIndex] = true;
        for (int j = 0; j < n; ++j) {
            if (edges[minIndex][j] != 0 && edges[minIndex][j] + distance[minIndex] < distance[j]) {
                distance[j] = edges[minIndex][j] + distance[minIndex];
                previousVertex[j] = minIndex;
            }
        }
    }
} */


/* 最小生成树算法 */

/* Prim算法与Dijkstra算法思路基本一致,
 * 区别在于: distance[i]标记i到已知顶点集的最短距离
 * 因此对于distance[i]的更新法则不同 */
/* 
void Prim(int start) {
    memset(visited, 0, sizeof(visited));
    distance[start] = 0;
    while (true) {
        int min = 9999;
        int minIndex = -1;
        for (int i = 0; i < n; ++i) {
            if (visited[i] == 0 && min > distance[i]) {
                min = distance[i];
                minIndex = i;
            }
        }
        if (minIndex == -1) break;
        visited[minIndex] = true;
        for (int i = 0; i < n; ++i) {
            if (edges[minIndex][i] != 0 && edges[minIndex][i] < distance[i] && visited[i] == 0) {
                distance[i] = edges[minIndex][i];
                previousVertex[i] = minIndex;
            }
        }
    }
}
 */

/* Kruskal算法 */
/* 
priority_queue<node, vector<node>, myCmp> Set;
int belongTo[501]; // 标记每个节点属于哪个集合
vector<node> minimumTree; // 构成最小生成树的边的集合
// 找到x节点属于的集合
int Find(int x) {
    return belongTo[x];
}
// 将两个集合合并
void Union(int u, int v) {
    int t = belongTo[v];
    for (int i = 0; i < n; ++i)
        if (belongTo[i] == t) belongTo[i] = belongTo[u];
}

void Kruskal() {
    for (int i = 0; i < n; ++i) belongTo[i] = i;  // 初始时每个节点各属于一个集合
    int count = 0;
    int u, v;
    node t;
    while (count < n - 1) {
        t = Set.top();
        Set.pop();
        u = Find(t.u);
        v = Find(t.v);
        if (u != v) {
            count++;
            Union(t.u, t.v);
            minimumTree.push_back(t);
        }
    }
}
 */


/* 求无向图割点: 双连通性 */
/* visited[], num[], low[], parent[], count为全局变量
每次调用算法前需指定根顶点rootVertex
res储存割点 */
/* 顶点v若有多于一个儿子且low[v] >= num[v](对根则是low[v] > num[v]),则v为割点 */
/* 版本一: */
/* 
void assignNum(int v) { // dfs
    num[v] = count++;
    visited[v] = true;
    for (int i = 0; i < n; ++i) {
        if (edges[v][i] != 0 && visited[i] == false) {
            parent[w] = v;
            assignNum(w);
        }
    }
}
void assignLow(int v) {
    low[v] = num[v];
    for (int i = 0; i < n; ++i) {
        if (edges[v][i] != 0) {
            if (num[w] > num[v]) {
                assignLow(w);
                if (low[w] > num[v] || (low[w] == num[v] && v != rootVertex))
                    res.push(v);
                low[w] = min(low[v], low[w]);
            } else {
                if (parent[v] != w)
                    low[v] = min[low[v], num[w]];
            }
        }
    }
}
 */
/* 版本二: 其实就是把版本一中的函数合二为一 */
/* 
void findArt(int v) {
    low[v] = num[v] = count++;
    visited[v] = true;
    for (int i = 0; i < n; ++i) {
        if (edges[v][i] != 0 && visited[i] == false) {
            parent[w] = v;
            findArt(w);
            if (low[w] > num[v] || (low[w] == num[v] && v != rootVertex))
                res.push(v);
            low[w] = min(low[v], low[w]);
        } else {
            if (parent[v] != w)
                low[v] = min[low[v], num[w]];
        }
    }
}
 */


#endif
