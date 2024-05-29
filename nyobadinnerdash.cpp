#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

// Struktur data untuk mewakili pesanan pelanggan
struct Order {
    string itemName;
    int preparationTime; // Waktu persiapan makanan dalam detik
};

// Struktur data untuk mewakili meja pelanggan
struct Table {
    int tableNumber;
    bool occupied; // Menandakan apakah meja ditempati atau tidak
    Order order;   // Pesanan dari pelanggan yang duduk di meja
};

// Fungsi untuk menyajikan pesanan
void serveOrder(Table& table) {
    cout << "Menghidangkan " << table.order.itemName << " untuk meja " << table.tableNumber << "..." << endl;
    // Simulasi persiapan makanan dengan menunggu waktu persiapan
    // Dalam kasus nyata, Anda akan memiliki logika yang lebih kompleks di sini
    for (int i = 0; i < table.order.preparationTime; ++i) {
        cout << ".";
        // Tunggu selama 1 detik
        this_thread::sleep_for(chrono::seconds(1));
    }
    cout << endl;
    cout << "Pesanan " << table.order.itemName << " untuk meja " << table.tableNumber << " siap untuk disajikan!" << endl;
}

int main() {
    // Inisialisasi meja-meja restoran
    vector<Table> tables = {
        {1, false, {"Spaghetti", 5}},
        {2, false, {"Burger", 3}},
        {3, false, {"Salad", 2}}
        // Anda bisa menambahkan lebih banyak meja di sini...
    };

    // Loop utama permainan
    bool gameRunning = true;
    while (gameRunning) {
        // Tampilkan status meja
        cout << "Status Meja:" << endl;
        for (const Table& table : tables) {
            cout << "Meja " << table.tableNumber << ": ";
            if (table.occupied) {
                cout << "Ditempati (Pesanan: " << table.order.itemName << ")" << endl;
            } else {
                cout << "Kosong" << endl;
            }
        }

        // Input dari pemain
        int tableChoice;
        cout << "Pilih nomor meja untuk dilayani (atau 0 untuk keluar): ";
        cin >> tableChoice;

        if (tableChoice == 0) {
            // Keluar dari permainan jika pemain memilih 0
            gameRunning = false;
            cout << "Terima kasih telah bermain!" << endl;
        } else if (tableChoice >= 1 && tableChoice <= tables.size()) {
            // Periksa apakah meja dipilih kosong
            Table& chosenTable = tables[tableChoice - 1];
            if (!chosenTable.occupied) {
                // Jika meja kosong, ambil pesanan dari pemain
                string item;
                int prepTime;
                cout << "Masukkan pesanan makanan untuk meja " << chosenTable.tableNumber << ": ";
                cin >> item;
                cout << "Masukkan waktu persiapan makanan (dalam detik) untuk meja " << chosenTable.tableNumber << ": ";
                cin >> prepTime;
                chosenTable.order = {item, prepTime};
                chosenTable.occupied = true;

                // Layani pesanan dalam thread terpisah
                thread serveThread(serveOrder, ref(chosenTable));
                serveThread.join(); // Tunggu hingga pesanan selesai disajikan
            } else {
                // Jika meja sudah ditempati, beri tahu pemain
                cout << "Meja " << chosenTable.tableNumber << " sudah ditempati. Pilih meja lain." << endl;
            }
        } else {
            // Jika pemain memilih nomor meja yang tidak valid
            cout << "Nomor meja tidak valid. Silakan pilih nomor meja yang sesuai." << endl;
        }
    }

    return 0;
}
