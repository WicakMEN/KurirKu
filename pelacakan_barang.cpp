#include <iostream>
#include <cstring> // Untuk memset
#include <climits> // Untuk INT_MAX

using namespace std;

const int MAX_V = 100;
const int INF = INT_MAX;

int V; // Jumlah simpul
int adj[MAX_V][MAX_V]; // Matriks ketetanggaan
bool visited[MAX_V]; // Array untuk mengecek simpul yang sudah dikunjungi

void inisialisasiGraf(int simpul) {
    V = simpul;
    memset(adj, INF, sizeof(adj));
    for (int i = 0; i < V; ++i)
        adj[i][i] = 0; // Jarak ke diri sendiri adalah 0
}

void tambahEdge(int u, int v, int w) {
    adj[u][v] = w;
    adj[v][u] = w;
}

void bfs(int mulai) {
    bool queue[MAX_V];
    int depan = 0, belakang = 0;
    memset(queue, false, sizeof(queue));
    
    queue[belakang++] = mulai;
    visited[mulai] = true;

    while (depan < belakang) {
        int u = queue[depan++];
        for (int v = 0; v < V; ++v) {
            if (adj[u][v] != INF && !visited[v]) {
                visited[v] = true;
                queue[belakang++] = v;
            }
        }
    }
}

bool terhubung() {
    memset(visited, false, sizeof(visited));
    bfs(0);

    for (int i = 0; i < V; ++i) {
        if (!visited[i])
            return false;
    }

    return true;
}

int jarakMin(int dist[], bool sptSet[]) {
    int min = INF, min_index;
    for (int v = 0; v < V; v++)
        if (!sptSet[v] && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

void dijkstra(int src, int dest, int parent[]) {
    int dist[MAX_V];
    bool sptSet[MAX_V];

    for (int i = 0; i < V; i++)
        dist[i] = INF, sptSet[i] = false, parent[i] = -1;

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = jarakMin(dist, sptSet);
        sptSet[u] = true;

        for (int v = 0; v < V; v++)
            if (!sptSet[v] && adj[u][v] != INF && dist[u] != INF && dist[u] + adj[u][v] < dist[v]) {
                dist[v] = dist[u] + adj[u][v];
                parent[v] = u;
            }
    }
}

int lacakBarang(int src, int dest, int waktuBerlalu) {
    if (!terhubung()) {
        cout << "Graf tidak terhubung." << endl;
        return -1;
    }

    int parent[MAX_V];
    dijkstra(src, dest, parent);

    int path[MAX_V];
    int path_len = 0;
    for (int v = dest; v != -1; v = parent[v])
        path[path_len++] = v;
    
    int waktuTerpakai = 0;

    for (int i = path_len - 1; i > 0; --i) {
        int u = path[i];
        int v = path[i - 1];
        waktuTerpakai += adj[u][v];
        if (waktuTerpakai > waktuBerlalu) {
            return u;
        }
    }

    return dest; // Barang telah mencapai tujuan
}

int main() {
    inisialisasiGraf(9);

    tambahEdge(0, 1, 4);
    tambahEdge(0, 7, 8);
    tambahEdge(1, 2, 8);
    tambahEdge(1, 7, 11);
    tambahEdge(2, 3, 7);
    tambahEdge(2, 8, 2);
    tambahEdge(2, 5, 4);
    tambahEdge(3, 4, 9);
    tambahEdge(3, 5, 14);
    tambahEdge(4, 5, 10);
    tambahEdge(5, 6, 2);
    tambahEdge(6, 7, 1);
    tambahEdge(6, 8, 6);
    tambahEdge(7, 8, 7);

    int sumber = 0;
    int tujuan = 4;
    int waktuBerlalu = 10; // Waktu yang telah berlalu

    int lokasiSaatIni = lacakBarang(sumber, tujuan, waktuBerlalu);

    if (lokasiSaatIni != -1) {
        cout << "Barang saat ini berada di lokasi: " << lokasiSaatIni << endl;
    }

    return 0;
}
