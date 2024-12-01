#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

// ͼ�����ݽṹ
class Graph {
private:
    int vertices; // ������
    vector<vector<pair<int, int>>> adjList; // �ڽӱ� (����, Ȩ��)

public:
    // ���캯��
    Graph(int v) : vertices(v) {
        adjList.resize(v);
    }

    // ��ӱ�
    void addEdge(int u, int v, int weight = 1) {
        adjList[u].emplace_back(v, weight);
        adjList[v].emplace_back(u, weight); // ����ͼ
    }

    // ����������� (BFS)
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

    // ����������� (DFS)
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

    // Dijkstra �㷨����Դ���·����
    void Dijkstra(int start) {
        vector<int> dist(vertices, numeric_limits<int>::max());
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq; // ��С��
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

    // Prim �㷨����С��������
    void Prim() {
        vector<bool> inMST(vertices, false); // ��ǽڵ��Ƿ��Ѱ����� MST ��
        vector<int> key(vertices, numeric_limits<int>::max()); // �洢��Ȩֵ
        vector<int> parent(vertices, -1); // ��¼ MST �ĸ��ڵ�
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq; // ��С��

        key[0] = 0; // �ӽڵ� 0 ��ʼ
        pq.push({ 0, 0 }); // {Ȩ��, �ڵ�}

        while (!pq.empty()) {
            int u = pq.top().second; // ��ǰѡ�е���С�ߵĽڵ�
            pq.pop();

            if (inMST[u]) continue; // ������� MST �У�����
            inMST[u] = true;

            for (auto it = adjList[u].begin(); it != adjList[u].end(); ++it) {
                int v = it->first;
                int weight = it->second;
                if (!inMST[v] && weight < key[v]) { // ��� v ���� MST ���и�С��Ȩֵ
                    key[v] = weight;
                    pq.push({ key[v], v });
                    parent[v] = u;
                }
            }
        }

        // ��� MST ���
        int mstWeight = 0;
        cout << "Prim MST edges: ";
        for (int i = 1; i < vertices; ++i) { // �� 1 ��ʼ����Ϊ 0 �����
            if (parent[i] != -1) {
                cout << "(" << parent[i] << "," << i << ") ";
                mstWeight += key[i];
            }
        }
        cout << "\nTotal MST Weight: " << mstWeight << endl;
    }
};

// ���Դ���
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
