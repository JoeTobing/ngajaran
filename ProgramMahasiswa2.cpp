#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip> // Untuk manipulasi tampilan tabel
using namespace std;

// Fungsi untuk membaca isi file dan menampilkan dalam bentuk tabel
void bacaFile() {
    ifstream inputFile("mahasiswa.txt"); // Membuka file "mahasiswa.txt"
    string line; // Variabel untuk menyimpan setiap baris teks
    if (!inputFile.is_open()) { // Memeriksa apakah file berhasil dibuka
        cout << "Gagal membuka file!" << endl;
        return;
    }

    vector<vector<string>> dataMahasiswa; // Menyimpan data mahasiswa

    // Membaca data dari file
    while (getline(inputFile, line)) {
        if (line.find("Mahasiswa") != string::npos) { // Memeriksa kata "Mahasiswa"
            vector<string> row;
            row.push_back(line); // Nomor mahasiswa
            getline(inputFile, line); 
            row.push_back(line.substr(6)); // Nama (menghapus "Nama: ")
            getline(inputFile, line);
            row.push_back(line.substr(5)); // NIM (menghapus "NIM: ")
            getline(inputFile, line); // Abaikan garis pemisah
            dataMahasiswa.push_back(row); // Tambahkan ke data
        }
    }

    inputFile.close();

    // Tampilkan tabel
    cout << "\n--- Daftar Mahasiswa ---" << endl;
    cout << left << setw(15) << "No Mahasiswa" << setw(25) << "Nama" << setw(15) << "NIM" << endl;
    cout << string(55, '-') << endl; // Garis pemisah
    for (const auto& row : dataMahasiswa) {
        cout << left << setw(15) << row[0]
             << setw(25) << row[1]
             << setw(15) << row[2] << endl;
    }
}

// Fungsi untuk menambahkan data mahasiswa
void tambahData() {
    ofstream outputFile("mahasiswa.txt", ios::app); // Membuka file untuk ditulis
    if (!outputFile.is_open()) {
        cout << "Gagal membuka file!" << endl;
        return;
    }

    // Hitung jumlah mahasiswa saat ini
    int jumlahMahasiswa = 0;
    ifstream inputFile("mahasiswa.txt");
    string line;
    while (getline(inputFile, line)) {
        if (line.find("Mahasiswa") != string::npos) {
            jumlahMahasiswa++;
        }
    }
    inputFile.close();

    int jumlah;
    cout << "\nMasukkan jumlah mahasiswa yang ingin ditambahkan: ";
    cin >> jumlah;
    cin.ignore();

    for (int i = 0; i < jumlah; i++) {
        string nama, nim;
        cout << "Masukkan nama mahasiswa ke-" << i + 1 << ": ";
        getline(cin, nama);
        cout << "Masukkan NIM mahasiswa ke-" << i + 1 << ": ";
        getline(cin, nim);
        outputFile << "Mahasiswa " << (jumlahMahasiswa + i + 1) << ":" << endl;
        outputFile << "Nama: " << nama << endl;
        outputFile << "NIM: " << nim << endl;
        outputFile << "-------------------" << endl;
    }

    outputFile.close();
    cout << "\nData baru berhasil ditambahkan ke file mahasiswa.txt." << endl;
}

// Fungsi untuk menghapus data mahasiswa
void hapusData() {
    vector<string> data;
    ifstream inputFile("mahasiswa.txt");
    string line;
    int nomorHapus;

    if (!inputFile.is_open()) {
        cout << "File mahasiswa.txt tidak ditemukan!" << endl;
        return;
    }

    while (getline(inputFile, line)) {
        data.push_back(line);
    }
    inputFile.close();

    cout << "\nMasukkan nomor mahasiswa yang ingin dihapus: ";
    cin >> nomorHapus;
    cin.ignore();

    bool ditemukan = false;
    ofstream outputFile("mahasiswa.txt");
    int nomorBaru = 1;

    for (size_t i = 0; i < data.size(); i++) {
        if (data[i].find("Mahasiswa " + to_string(nomorHapus) + ":") != string::npos) {
            ditemukan = true;
            i += 3; // Lewati blok data mahasiswa yang dihapus
        } else if (data[i].find("Mahasiswa") != string::npos) {
            outputFile << "Mahasiswa " << nomorBaru++ << ":" << endl;
        } else {
            outputFile << data[i] << endl;
        }
    }

    outputFile.close();

    if (ditemukan) {
        cout << "Data mahasiswa nomor " << nomorHapus << " berhasil dihapus." << endl;
    } else {
        cout << "Mahasiswa dengan nomor " << nomorHapus << " tidak ditemukan." << endl;
    }
}

int main() {
    int pilihan;
    do {
        cout << "\n--- Menu ---" << endl;
        cout << "1. Baca file mahasiswa.txt" << endl;
        cout << "2. Tambah data baru ke mahasiswa.txt" << endl;
        cout << "3. Hapus data mahasiswa" << endl;
        cout << "4. Keluar" << endl;
        cout << "Pilihan Anda: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                bacaFile();
                break;
            case 2:
                tambahData();
                break;
            case 3:
                hapusData();
                break;
            case 4:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (pilihan != 4);

    return 0;
}