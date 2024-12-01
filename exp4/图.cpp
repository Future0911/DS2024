#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

// 图的数据结构
class Graph {
private:
    int vertices; // 顶点数
    vector<vector<pair<int, int>>> adjList; // 邻接表 (顶点, 权重)

public:
    // 构造函数
    Graph(int v) : vertices(v) {
        adjList.resize(v);
    }

    // 添加边
    void addEdge(int u, int v, int weight = 1) {
        adjList[u].emplace_back(v, weight);
        adjList[v].emplace_back(u, weight); // 无向图
    }

    // 广度优先搜索 (BFS)
    void BFS(int start) {
        vector<bool> visited(vertices, false);
        queue<int> q;
        visited[start] = true;
        q.push(start);

        cout << "BFS: ";
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";

            for (auto& neighbor : adjList[node]) {
                int next = neighbor.first;
                if (!visited[next]) {
                    visited[next] = true;
                    q.push(next);
                }
            }
        }
        cout << endl;
    }

    // 深度优先搜索 (DFS)
    void DFS(int start) {
        vector<bool> visited(vertices, false);
        cout << "DFS: ";
        DFSUtil(start, visited);
        cout << endl;
    }

    void DFSUtil(int node, vector<bool>& visited) {
        visited[node] = true;
        cout << node << " ";
        for (auto& neighbor : adjList[node]) {
            int next = neighbor.first;
            if (!visited[next]) {
                DFSUtil(next, visited);
            }
        }
    }

    // Dijkstra 算法（单源最短路径）
    void Dijkstra(int start) {
        vector<int> dist(vertices, numeric_limits<int>::max());
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq; // 最小堆
        dist[start] = 0;
        pq.push({ 0, start });

        while (!pq.empty()) {
            int currentDist = pq.top().first;
            int currentNode = pq.top().second;
            pq.pop();

            if (currentDist > dist[currentNode]) continue;

            for (auto& neighbor : adjList[currentNode]) {
                int nextNode = neighbor.first;
                int weight = neighbor.second;
                if (dist[currentNode] + weight < dist[nextNode]) {
                    dist[nextNode] = dist[currentNode] + weight;
                    pq.push({ dist[nextNode], nextNode });
                }
            }
        }

        cout << "Dijkstra (from " << start << "): ";
        for (int i = 0; i < vertices; ++i) {
            cout << i << "->" << dist[i] << " ";
        }
        cout << endl;
    }

    // Prim 算法（最小生成树）
    void Prim() {
        vector<bool> inMST(vertices, false); // 标记节点是否已包含在 MST 中
        vector<int> key(vertices, numeric_limits<int>::max()); // 存储边权值
        vector<int> parent(vertices, -1); // 记录 MST 的父节点
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq; // 最小堆

        key[0] = 0; // 从节点 0 开始
        pq.push({ 0, 0 }); // {权重, 节点}

        while (!pq.empty()) {
            int u = pq.top().second; // 当前选中的最小边的节点
            pq.pop();

            if (inMST[u]) continue; // 如果已在 MST 中，跳过
            inMST[u] = true;

            for (auto it = adjList[u].begin(); it != adjList[u].end(); ++it) {
                int v = it->first;
                int weight = it->second;
                if (!inMST[v] && weight < key[v]) { // 如果 v 不在 MST 且有更小的权值
                    key[v] = weight;
                    pq.push({ key[v], v });
                    parent[v] = u;
                }
            }
        }

        // 输出 MST 结果
        int mstWeight = 0;
        cout << "Prim MST edges: ";
        for (int i = 1; i < vertices; ++i) { // 从 1 开始，因为 0 是起点
            if (parent[i] != -1) {
                cout << "(" << parent[i] << "," << i << ") ";
                mstWeight += key[i];
            }
        }
        cout << "\nTotal MST Weight: " << mstWeight << endl;
    }
};

// 测试代码
int main() {
    Graph g(6);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 3, 4);
    g.addEdge(3, 4, 2);
    g.addEdge(4, 5, 6);

    g.BFS(0);
    g.DFS(0);
    g.Dijkstra(0);
    g.Prim();

    return 0;
}
