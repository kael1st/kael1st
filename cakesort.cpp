#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib> // untuk menggunakan fungsi rand()
#include <ctime>   // untuk menggunakan fungsi time()

using namespace std;

// Definisikan struktur untuk kue
struct Cake {
    int slices;
    string color;
};

// Fungsi untuk menghasilkan kue secara acak dengan jumlah slices antara 1 dan 6
Cake generateRandomCake() {
    Cake cake;
    cake.slices = rand() % 6 + 1; // jumlah slices kue antara 1 dan 6
    string colors[] = {"Red", "Blue", "Green", "Yellow", "Pink"}; // warna yang mungkin
    cake.color = colors[rand() % 5]; // warna kue dipilih secara acak
    return cake;
}

// Fungsi untuk mencetak kue ke layar
void printCake(const Cake& cake) {
    cout << "Slices: " << cake.slices << ", Color: " << cake.color << endl;
}

int main() {
    // Inisialisasi generator angka acak dengan waktu saat ini
    srand(time(0));

    // Menentukan jumlah baris dan kolom dalam plate
    int rows = 3; // jumlah baris
    int cols = 4; // jumlah kolom

    // Mendefinisikan plate sebagai vektor dalam vektor
    vector<vector<Cake>> plate(rows, vector<Cake>(cols));

    // Membuat antrian (queue) untuk menyimpan kue-kue yang telah dimasukkan ke dalam pring
    queue<Cake> queueOfCakes;

    // Mengisi antrian dengan kue-kue acak
    for (int i = 0; i < rows * cols; ++i) {
        queueOfCakes.push(generateRandomCake());
    }

    // Mengisi plate dengan kue-kue dari antrian
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // Mengambil kue dari antrian
            plate[i][j] = queueOfCakes.front();
            queueOfCakes.pop();
        }
    }

    // Mencetak plate ke layar
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << "Cake at row " << i+1 << ", col " << j+1 << ": ";
            printCake(plate[i][j]);
        }
    }

    return 0;
}
