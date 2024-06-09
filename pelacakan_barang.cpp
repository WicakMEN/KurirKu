#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>

using namespace std;

typedef pair<int, int> iPair;

class Graph {
    int V;
    vector<vector<iPair>> adj;

public:
    Graph(int V);

    void addEdge(int u, int v, int w);
    vector<int> dijkstra(int src, int dest);
    int trackItem(int src, int dest, int timeElapsed); // Fungsi pelacakan
    bool isConnected();
};

Graph::Graph(int V) {
    this->V = V;
    adj.resize(V);
}

void Graph::addEdge(int u, int v, int w) {
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}

bool Graph::isConnected() {
    vector<bool> visited(V, false);
    queue<int> q;

    visited[0] = true;
    q.push(0);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto &x : adj[u]) {
            int v = x.first;
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }

    for (int i = 0; i < V; ++i) {
        if (!visited[i]) {
            return false;
        }
    }

    return true;
}

vector<int> Graph::dijkstra(int src, int dest) {
    priority_queue<iPair, vector<iPair>, greater<iPair>> pq;
    vector<int> dist(V, numeric_limits<int>::max());
    vector<int> parent(V, -1);
    pq.push(make_pair(0, src));
    dist[src] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (auto &x : adj[u]) {
            int v = x.first;
            int weight = x.second;

            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
                parent[v] = u;
            }
        }
    }

    // Membangun jalur dari parent array
    vector<int> path;
    for (int v = dest; v != -1; v = parent[v])
        path.push_back(v);
    
    (path.begin(), path.end());
    return path;
}

int Graph::trackItem(int src, int dest, int timeElapsed) {
    if (!isConnected()) {
        cout << "Graf tidak terhubung." << endl;
        return -1;
    }

    vector<int> path = dijkstra(src, dest);
    int timeSpent = 0;

    for (size_t i = 0; i < path.size() - 1; ++i) {
        int u = path[i];
        int v = path[i + 1];
        for (auto &x : adj[u]) {
            if (x.first == v) {
                timeSpent += x.second;
                if (timeSpent > timeElapsed) {
                    return u;
                }
                break;
            }
        }
    }

    return dest; // Barang telah mencapai tujuan
}

int main() {
    int V = 9;
    Graph g(V);

    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);

    int source = 0;
    int destination = 4;
    int timeElapsed = 10; // Waktu yang telah berlalu

    int currentLocation = g.trackItem(source, destination, timeElapsed);

    if (currentLocation != -1) {
        cout << "Barang saat ini berada di lokasi: " << currentLocation << endl;
    }

    return 0;
}

