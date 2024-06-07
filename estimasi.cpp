#include <iostream>
#include <vector>
using namespace std;

// Struktur node untuk tree
struct Node {
    string lokasi;
    int waktu; // waktu dalam menit
    vector<Node*> children;
};

// untuk membuat node baru
Node* createNode(string lokasi, int waktu) {
    Node* newNode = new Node;
    newNode->lokasi = lokasi;
    newNode->waktu = waktu;
    return newNode;
}

// untuk menambahkan anak ke node
void tambahAnak(Node* parent, Node* child) {
    parent->children.push_back(child);
}

// untuk menampilkan estimasi waktu
void estimasi (Node* node, int accumulatedTime, int& counter) {
    accumulatedTime += node->waktu;
    cout << counter++ << ". Lokasi: " << node->lokasi << ", Estimasi Waktu: " << accumulatedTime << " menit" << endl;
    
    for (Node* child : node->children) {
        estimasi (child, accumulatedTime, counter);
    }
}

int main() {
    // Membuat node untuk setiap lokasi
    Node* cibiru = createNode("UPI Cibiru", 0);
    Node* bumsil = createNode("UPI BUMSIL", 30); // waktu tempuh 30 menit dari UPI Cibiru ke UPI BUMSIL

    // Tempat di UPI BUMSIL
    Node* rektorat = createNode("Gedung Rektorat", 10);
    Node* akmawa = createNode("Akademik Mahasiswa", 5);
    Node* sdti = createNode("SDTI", 8);
    Node* keuangan = createNode("Direktorat Keuangan", 7);
    Node* ahsun = createNode("Gedung Ahmad Sanusi", 12);

    // Membuat struktur tree
    tambahAnak(cibiru, bumsil);
    tambahAnak(bumsil, rektorat);
    tambahAnak(bumsil, akmawa);
    tambahAnak(bumsil, sdti);
    tambahAnak(bumsil, keuangan);
    tambahAnak(bumsil, ahsun);

    // Menampilkan estimasi waktu dari UPI Cibiru
    cout << "Estimasi waktu pengiriman dari UPI Cibiru:" << endl;
    int counter = 1;
    estimasi (bumsil, 0, counter);

    return 0;
}
