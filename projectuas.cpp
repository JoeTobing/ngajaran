#include <iostream>
#include <limits> 
#include <cstdlib>
#include <ctime>

using namespace std;

// Deklarasi fungsi untuk Tic Tac Toe
void gambarpapan(); // Menampilkan papan permainan
void giliranpemain(int nomorpetak); // Mengubah giliran pemain dan memperbarui papan
bool cekmenang(); // Mengecek apakah ada pemain yang menang
bool cekseri(); // Mengecek apakah permainan berakhir seri
void Blackjack(); // Permainan Blackjack
void resetpapan(); // Mengatur ulang papan permainan

// Variabel global untuk Tic Tac Toe
char papan[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
bool pemainpertama = true; // Menentukan giliran pemain pertama
bool running = true; // Status permainan Tic Tac Toe

int main() {
    srand(time(0)); // Inisialisasi seed untuk pengacakan

    int pilihan = 0;
    while (true) {
        // Menu utama
        cout << endl;
        cout << "Pilih permainan yang ingin Anda mainkan\n";
        cout << "1. Tic Tac Toe\n";
        cout << "2. Blackjack\n";
        cout << "3. Keluar\n";

        // Input pilihan permainan dengan validasi
        while (true) {
            cout << "Masukkan pilihan Anda: ";
            cin >> pilihan;

            if (cin.fail()) {
                cin.clear(); // Membersihkan kesalahan input
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan input invalid
                cout << "Input tidak valid, masukkan angka antara 1-3.\n";
                continue;
            }

            if (pilihan < 1 || pilihan > 3) {
                cout << "Pilihan tidak valid, coba lagi.\n";
            } else {
                break;
            }
        }

        if (pilihan == 1) {
            // Memulai permainan Tic Tac Toe
            resetpapan();
            gambarpapan();
            running = true;
            while (running) {
                // Giliran pemain
                cout << "Giliran pemain: " << (pemainpertama ? "X" : "O") << endl;
                cout << "Pilih petak (1-9): ";
                int nomorpetak;
                cin >> nomorpetak;

                // Validasi input petak
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Input tidak valid, masukkan angka antara 1-9.\n";
                    continue;
                }

                if (nomorpetak < 1 || nomorpetak > 9) {
                    cout << "Nomor petak harus antara 1-9. Coba lagi.\n";
                    continue;
                }

                if (papan[nomorpetak - 1] != ' ') {
                    cout << "Petak ini sudah diisi, pilih petak lain.\n";
                    continue;
                }

                // Pemain memilih petak
                giliranpemain(nomorpetak);

                // Mengecek kondisi menang atau seri
                if (cekmenang()) {
                    running = false;
                    cout << (!pemainpertama ? "X" : "O") << " menang! Selamat!\n";
                } else if (cekseri()) {
                    running = false;
                    cout << "Seri!\n";
                }
            }
        } else if (pilihan == 2) {
            // Memulai permainan Blackjack
            Blackjack();
        } else if (pilihan == 3) {
            // Keluar dari program
            cout << "Terima kasih telah bermain! Sampai jumpa lagi!\n";
            break;
        }
    }

    return 0;
}

void gambarpapan() {
    // Menampilkan papan Tic Tac Toe
    cout << endl;
    cout << "     |     |     " << endl;
    cout << "  " << papan[0] << "  |  " << papan[1] << "  |  " << papan[2] << endl;
    cout << "-----|-----|-----" << endl;
    cout << "     |     |     " << endl;
    cout << "  " << papan[3] << "  |  " << papan[4] << "  |  " << papan[5] << endl;
    cout << "-----|-----|-----" << endl;
    cout << "     |     |     " << endl;
    cout << "  " << papan[6] << "  |  " << papan[7] << "  |  " << papan[8] << endl;
    cout << "     |     |     " << endl;
    cout << endl;
}

void giliranpemain(int nomorpetak) {
    // Memperbarui papan berdasarkan giliran pemain
    nomorpetak = nomorpetak - 1;
    papan[nomorpetak] = pemainpertama ? 'X' : 'O';
    pemainpertama = !pemainpertama;

    gambarpapan(); // Menampilkan papan setelah giliran
}

bool cekmenang() {
    // Mengecek kemenangan vertikal dan horizontal
    for (int i = 0; i < 3; i++) {
        if ((papan[i * 3] == papan[i * 3 + 1] && papan[i * 3 + 1] == papan[i * 3 + 2] && papan[i * 3] != ' ') ||
            (papan[i] == papan[i + 3] && papan[i + 3] == papan[i + 6] && papan[i] != ' ')) {
            return true;
        }
    }

    if ((papan[0] == papan[4] && papan[4] == papan[8] && papan[0] != ' ') ||
        (papan[2] == papan[4] && papan[4] == papan[6] && papan[2] != ' ')) {
        return true;
    }

    return false;
}

bool cekseri() {
    // Mengecek apakah papan penuh (seri)
    for (int i = 0; i < 9; i++) {
        if (papan[i] == ' ') {
            return false;
        }
    }
    return true;
}

void resetpapan() {
    // Mengatur ulang papan permainan dan giliran pertama
    for (int i = 0; i < 9; i++) {
        papan[i] = ' ';
    }
    pemainpertama = true;
}

int acakkartu() {
    // Menghasilkan nilai kartu secara acak antara 1-10
    return rand() % 10 + 1;
}

void Blackjack() {
    // Permainan Blackjack sederhana
    int playerScore = 0, dealerScore = 0;
    char choice;
    cout << endl;
    cout << "Selamat datang di permainan Blackjack sederhana!\n";

    // Menarik dua kartu awal untuk pemain
    playerScore += acakkartu();
    playerScore += acakkartu();
    cout << "Skor awal Anda: " << playerScore << endl;

    // Dealer menarik kartu pertama
    dealerScore += acakkartu();
    cout << "Dealer memiliki kartu tersembunyi + 1 kartu terlihat.\n";

    // Giliran pemain
    while (true) {
        cout << "Apakah Anda ingin menarik kartu lagi? (y/n): ";
        cin >> choice;

        if (cin.fail() || (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N')) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid. Masukkan 'y' untuk ya atau 'n' untuk tidak.\n";
            continue;
        }

        if (choice == 'y' || choice == 'Y') {
            int newCard = acakkartu();
            playerScore += newCard;
            cout << "Anda menarik kartu bernilai " << newCard << ".\n";
            cout << "Skor Anda sekarang: " << playerScore << "\n";

            if (playerScore > 21) {
                cout << "Skor Anda melebihi 21. Anda kalah!\n";
                return;
            }
        } else {
            break;
        }
    }

    // Giliran dealer
    while (dealerScore < 17) {
        int newCard = acakkartu();
        dealerScore += newCard;
    }

    // Menentukan hasil permainan
    cout << "Dealer selesai bermain. Skor dealer: " << dealerScore << endl;

    if (dealerScore > 21 || playerScore > dealerScore) {
        cout << "Selamat! Anda menang!\n";
    } else if (playerScore == dealerScore) {
        cout << "Permainan berakhir seri!\n";
    } else {
        cout << "Anda kalah! Dealer menang!\n";
    }
}
