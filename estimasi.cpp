#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>


using namespace std;

// Kelas untuk menyimpan data setiap node
class Node {
public:
    string nama;
    vector<Node*> anak;
    string status;

    Node(string nama_node) {
        nama = nama_node;
    }

    void tambahAnak(Node* anak_baru) {
        anak.push_back(anak_baru);
    }
};

// Kelas untuk membuat struktur pohon
class Pohon {
public:
    Node* akar;
    int waktu_perjalanan = 30; // Dalam menit

private:
    chrono::steady_clock::time_point waktu_mulai;

public:
    Pohon() {
        akar = new Node("UPI Cibiru");
    }

    void buatPohon() {
        Node* upi_bumsil = new Node("UPI Bumi Siliwangi");
        akar->tambahAnak(upi_bumsil);

        Node* rektorat = new Node("Gedung Rektorat");
        Node* akademik = new Node("Akademik Mahasiswa");
        Node* keuangan = new Node("Direktorat Keuangan");
        Node* sisti = new Node("Direktorat Sistem dan Teknologi Informasi UPI");
        Node* ahmad_sanusi = new Node("Gedung Ahmad Sanusi");

        upi_bumsil->tambahAnak(rektorat);
        upi_bumsil->tambahAnak(akademik);
        upi_bumsil->tambahAnak(keuangan);
        upi_bumsil->tambahAnak(sisti);
        upi_bumsil->tambahAnak(ahmad_sanusi);
    }

    void aturWaktu(Node* sumber, string tujuan, int nomor_barang) {
        if (sumber == akar) {
            waktu_mulai = chrono::steady_clock::now();
            akar->status = "Barang " + to_string(nomor_barang) + " sedang berjalan dari UPI Cibiru menuju UPI Bumi Siliwangi";
            for (Node* anak : akar->anak) {
                anak->status = "";
            }
        } else {
            for (Node* anak : sumber->anak) {
                if (anak->nama == tujuan) {
                    anak->status = "Barang " + to_string(nomor_barang) + " sudah berada di " + tujuan + ". Barang akan diantar oleh petugas.";
                } else {
                    anak->status = "";
                }
            }
        }
    }

    void cetakTujuan(string tujuan, int nomor_barang) {
        cout << "Status Pengiriman Barang " << nomor_barang << ":" << endl;
        cout << "------------------------------" << endl;
        cetakNode(akar, tujuan, 0, nomor_barang);
        cout << "------------------------------" << endl;
    }

void cetakNode(Node* node, string tujuan, int level, int nomor_barang) {
    if (node->nama == "UPI Cibiru") {
        auto waktu_sekarang = chrono::steady_clock::now();
        auto waktu_berlalu = waktu_sekarang - waktu_mulai;
        int menit_berlalu = chrono::duration_cast<chrono::minutes>(waktu_berlalu).count();

        if (menit_berlalu > 7 * 24 * 60) { // Jika lebih dari 7 hari, batasi ke 7 hari
            menit_berlalu = 7 * 24 * 60;
        }

        time_t waktu_sampai = chrono::system_clock::to_time_t(chrono::system_clock::now() + chrono::minutes(menit_berlalu));
        tm* waktu_lokal = localtime(&waktu_sampai);

        // Mendefinisikan string format waktu dalam bahasa Indonesia
        const char* hari[] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};
        const char* bulan[] = {"Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"};

        cout << ">>> " << node->nama << endl;
        cout << node->status << " (" << hari[waktu_lokal->tm_wday] << ", "
             << waktu_lokal->tm_mday << " " << bulan[waktu_lokal->tm_mon] << " "
             << waktu_lokal->tm_year + 1900 << ", "
             << setfill('0') << setw(2) << waktu_lokal->tm_hour << ":"
             << setfill('0') << setw(2) << waktu_lokal->tm_min << ")" << endl;
        cout << "Tekan Enter untuk melanjutkan...";
        cin.ignore();
        cin.get();
        
        } else if (node->nama == tujuan) {
            cout << ">>> " << node->nama << endl;
            if (!node->status.empty()) {
                cout << node->status << endl;
                cout << "Tekan Enter untuk melanjutkan...";
                cin.ignore();
                cin.get();
            }
        } else {
            for (Node* anak : node->anak) {
                cetakNode(anak, tujuan, level + 1, nomor_barang);
            }
        }
    }

    vector<string> ambilTujuan() {
        vector<string> tujuan;
        for (Node* anak : akar->anak[0]->anak) {
            tujuan.push_back(anak->nama);
        }
        return tujuan;
    }
};

int main() {
    Pohon pohon;
    pohon.buatPohon();

    char pilihan;
    do {
        cout << "Pilih barang:" << endl;
        cout << "1. Barang 1" << endl;
        cout << "2. Barang 2" << endl;
        cout << "0. Kembali ke halaman utama" << endl;
        cout << "Masukkan pilihan (0-2): ";
        int nomor_barang;
        cin >> nomor_barang;

        if (nomor_barang == 0) {
            continue;
        } else if (nomor_barang == 1 || nomor_barang == 2) {
            cout << "Pilih tujuan:" << endl;
            vector<string> tujuan = pohon.ambilTujuan();
            for (int i = 0; i < tujuan.size(); i++) {
                cout << i + 1 << ". " << tujuan[i] << endl;
            }
            cout << "Masukkan pilihan (1-" << tujuan.size() << "): ";
            int indeks;
            cin >> indeks;

            if (indeks > 0 && indeks <= tujuan.size()) {
                string tujuan_pilihan = tujuan[indeks - 1];
                pohon.aturWaktu(pohon.akar->anak[0], tujuan_pilihan, nomor_barang);
                pohon.cetakTujuan(tujuan_pilihan, nomor_barang);

                time_t waktu_sekarang = time(0);
                tm* waktu_lokal = localtime(&waktu_sekarang);
                int jam_sekarang = waktu_lokal->tm_hour;
                int menit_sekarang = waktu_lokal->tm_min;
                int estimasi_jam = jam_sekarang + (menit_sekarang + pohon.waktu_perjalanan) / 60;
                int estimasi_menit = (menit_sekarang + pohon.waktu_perjalanan) % 60;

                cout << ">>> Barang " << nomor_barang << " sedang diantar oleh petugas, estimasi sampai pukul " << estimasi_jam << ":" << setfill('0') << setw(2) << estimasi_menit << endl;
                cout << "Tekan Enter untuk melanjutkan...";
                cin.ignore();
                cin.get();
            } else {
                cout << "Pilihan tidak valid!" << endl;
            }
        } else {
            cout << "Pilihan tidak valid!" << endl;
        }

        cout << "Tekan 'y' untuk kembali ke halaman utama, atau lainnya untuk keluar: ";
        cin >> pilihan;
    } while (pilihan == 'y' || pilihan == 'Y');

    return 0;
}
