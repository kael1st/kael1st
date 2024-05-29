#include <iostream>
using namespace std;

// Struct untuk customer
struct Customer {
    int numberOfCustomers;
    int emotionalLevel; // Berupa angka dengan maksimal 5
};

const int MAX_CUSTOMERS = 10; // Jumlah maksimum customer yang dapat ditangani

// Fungsi untuk membuat customer baru
Customer CreateCustomer(int numberOfCustomers, int emotionalLevel) {
    // Batasan jumlah pelanggan
    if (numberOfCustomers < 1 || numberOfCustomers > 5) {
        cout << "Error: Number of customers should be between 1 and 5." << endl;
        numberOfCustomers = 1; // Default ke 1 jika di luar batasan
    }

    // Batasan tingkat emosi
    if (emotionalLevel < 1 || emotionalLevel > 5) {
        cout << "Error: Emotional level should be between 1 and 5." << endl;
        emotionalLevel = 1; // Default ke 1 jika di luar batasan
    }

    Customer newCustomer;
    newCustomer.numberOfCustomers = numberOfCustomers;
    newCustomer.emotionalLevel = emotionalLevel;

    return newCustomer;
}

int main() {
    Customer customers[MAX_CUSTOMERS]; // Array untuk menyimpan data customer

    // Membuat customer baru
    customers[0] = CreateCustomer(3, 4); // Contoh customer dengan 3 pelanggan dan tingkat emosi 4
    customers[1] = CreateCustomer(5, 3); // Contoh customer dengan jumlah pelanggan maksimal (5) dan tingkat emosi 3
    customers[2] = CreateCustomer(2, 6); // Contoh customer dengan tingkat emosi yang melebihi batasan

    // Menampilkan data customer
    for (int i = 0; i < MAX_CUSTOMERS; ++i) {
        if (customers[i].numberOfCustomers > 0) {
            cout << "Customer " << i+1 << ":" << endl;
            cout << "Number of customers: " << customers[i].numberOfCustomers << endl;
            cout << "Emotional level: " << customers[i].emotionalLevel << endl;
            cout << endl;
        }
    }

    return 0;
}
