#include <iostream>
#include <queue>
#include <cstdlib> // Untuk menggunakan fungsi rand()

using namespace std;

// Mendefinisikan struct Customer
struct Customer {
    int numberOfCustomers;
    int emotionalLevel;
};

// Fungsi untuk menghasilkan pelanggan secara acak
Customer generateCustomer() {
    Customer customer;

    // Menetapkan jumlah pelanggan dengan nilai acak antara 1 dan 5
    customer.numberOfCustomers = rand() % 5 + 1;

    // Menetapkan tingkat emosional dengan nilai acak antara 1 dan 5
    customer.emotionalLevel = rand() % 5 + 1;

    return customer;
}

// Fungsi untuk memasukkan pelanggan ke dalam antrian dengan batasan jumlah maksimum
void enqueueCustomer(queue<Customer>& customerQueue, const Customer& newCustomer, int maxQueueSize) {
    if (customerQueue.size() < maxQueueSize) {
        customerQueue.push(newCustomer);
        cout << "Pelanggan ditambahkan ke dalam antrian." << endl;
    } else {
        cout << "Antrian pelanggan penuh. Tidak dapat menambahkan lebih banyak pelanggan." << endl;
    }
}

// Fungsi untuk mengeluarkan pelanggan dari dalam antrian
void dequeueCustomer(queue<Customer>& customerQueue) {
    if (!customerQueue.empty()) {
        customerQueue.pop();
        cout << "Pelanggan dihapus dari antrian." << endl;
    } else {
        cout << "Antrian pelanggan kosong." << endl;
    }
}

int main() {
    // Inisialisasi seed untuk fungsi rand() agar menghasilkan nilai acak yang berbeda setiap kali program dijalankan
    srand(static_cast<unsigned>(time(0)));

    // Membuat antrian pelanggan
    queue<Customer> customerQueue;

    // Menggunakan fungsi generateCustomer() untuk membuat pelanggan baru
    Customer randomCustomer = generateCustomer();

    // Menampilkan informasi pelanggan yang dihasilkan
    cout << "Jumlah Pelanggan: " << randomCustomer.numberOfCustomers << endl;
    cout << "Tingkat Emosional: " << randomCustomer.emotionalLevel << endl;

    // Memasukkan pelanggan ke dalam antrian dengan batasan jumlah maksimum 4
    enqueueCustomer(customerQueue, randomCustomer, 4);

    // Menampilkan informasi pelanggan dalam antrian
    cout << "\nPelanggan dalam Antrian:" << endl;
    cout << "Jumlah Pelanggan: " << customerQueue.front().numberOfCustomers << endl;
    cout << "Tingkat Emosional: " << customerQueue.front().emotionalLevel << endl;

    // Mengeluarkan pelanggan dari dalam antrian
    dequeueCustomer(customerQueue);

    return 0;
}
