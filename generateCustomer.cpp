#include <iostream>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <queue>

using namespace std;

// Struktur untuk merepresentasikan pelanggan
struct Customer {
    int id;
    string color;
    int lives;

    Customer(int _id, string _color, int _lives) : id(_id), color(_color), lives(_lives) {}
};

// Struktur node untuk linked list pelanggan
struct Node {
    Customer data;
    Node* next;

    Node(Customer _data) : data(_data), next(nullptr) {}
};

// Kelas untuk mengelola generator pelanggan
class CustomerGenerator {
private:
    Node* head;  // Kepala linked list pelanggan di restoran
    queue<Customer> customerQueue;  // Antrian pelanggan di pintu masuk
    int customerCount;  // Jumlah total pelanggan di restoran
    int maxCustomersPerGroup;  // Maksimal pelanggan dalam satu kelompok
    int maxCustomersPerSpawn;  // Maksimal pelanggan yang di-generate setiap 30 detik

public:
    // Konstruktor
    CustomerGenerator() : head(nullptr), customerCount(0), maxCustomersPerGroup(4), maxCustomersPerSpawn(3) {
        srand(static_cast<unsigned>(time(nullptr)));
    }

    // Fungsi untuk meng-generate pelanggan dengan warna acak dan nyawa 3
    void generateCustomer() {
        string colors[] = {"blue", "red"};
        string randomColor = colors[rand() % (sizeof(colors) / sizeof(colors[0]))];

        Customer newCustomer(customerCount + 1, randomColor, 3);
        Node* newNode = new Node(newCustomer);
        newNode->next = head;
        head = newNode;

        customerCount++;
    }

    // Fungsi untuk meng-generate kelompok pelanggan dengan jumlah acak
    void generateCustomerGroup() {
        int groupSize = rand() % maxCustomersPerGroup + 1;
        for (int i = 0; i < groupSize; ++i) {
            if (customerCount < maxCustomersPerSpawn) {
                generateCustomer();
            }
        }
    }

    // Fungsi untuk memasukkan kelompok pelanggan ke dalam antrian
    void enqueueCustomerGroup() {
        generateCustomerGroup();
        while (head != nullptr) {
            Customer customer = head->data;
            customerQueue.push(customer);

            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Fungsi untuk meng-update nyawa pelanggan (berkurang setiap 10 detik)
    void updateCustomerLives() {
        Node* current = head;
        while (current != nullptr) {
            // Kurangi nyawa setiap 10 detik
            if (customerCount > 0 && customerCount <= maxCustomersPerSpawn) {
                if (current->data.lives > 0 && current->data.lives % 2 == 0) {
                    current->data.lives = max(0, current->data.lives / 2);
                }
            }
            current = current->next;
        }
    }

    // Fungsi untuk menghapus pelanggan yang nyawanya habis
    void removeExpiredCustomers() {
        Node* current = head;
        Node* prev = nullptr;

        while (current != nullptr) {
            if (current->data.lives <= 0) {
                if (prev == nullptr) {
                    head = current->next;
                    delete current;
                    current = head;
                } else {
                    prev->next = current->next;
                    delete current;
                    current = prev->next;
                }
                customerCount--;
            } else {
                prev = current;
                current = current->next;
            }
        }
    }

    // Fungsi untuk menampilkan informasi pelanggan di restoran
    void displayCustomers() {
        Node* current = head;
        while (current != nullptr) {
            cout << "Customer ID: " << current->data.id << ", Color: " << current->data.color << ", Lives: " << current->data.lives << endl;
            current = current->next;
        }
    }

    // Fungsi untuk menampilkan informasi antrian pelanggan
    void displayQueue() {
        queue<Customer> tempQueue = customerQueue;
        int groupNumber = 1;

        while (!tempQueue.empty()) {
            cout << "Group " << groupNumber << ": ";
            for (int i = 0; i < maxCustomersPerGroup && !tempQueue.empty(); ++i) {
                Customer customer = tempQueue.front();
                cout << "ID: " << customer.id << ", Color: " << customer.color << ", Lives: " << customer.lives << " | ";
                tempQueue.pop();
            }
            cout << endl;
            groupNumber++;
        }
    }

    // Fungsi untuk meng-generate pelanggan setiap 30 detik
    void spawnCustomers() {
        for (int i = 0; i < maxCustomersPerSpawn; ++i) {
            if (customerCount < maxCustomersPerSpawn) {
                enqueueCustomerGroup();
            }
        }
    }

    // Destruktor untuk membersihkan memori
    ~CustomerGenerator() {
        Node* current = head;
        Node* next;

        while (current != nullptr) {
            next = current->next;
            delete current;
            current = next;
        }
    }
};

// Fungsi utama
int main() {
    CustomerGenerator customerGenerator;

    // Simulasi waktu selama 90 detik
    for (int seconds = 0; seconds < 90; ++seconds) {
        // Spawn pelanggan setiap 30 detik
        if (seconds % 30 == 0) {
            customerGenerator.spawnCustomers();
        }

        // Update nyawa pelanggan setiap detik
        customerGenerator.updateCustomerLives();

        // Hapus pelanggan yang nyawanya habis
        customerGenerator.removeExpiredCustomers();

        // Tampilkan informasi pelanggan di restoran dan antrian
        system("cls");
        cout << "Time: " << seconds << " seconds" << endl;
        cout << "Customers in the restaurant:" << endl;
        customerGenerator.displayCustomers();
        cout << "Queue at the entrance:" << endl;
        customerGenerator.displayQueue();
        cout << endl;

        // Tunggu selama 1 detik (mensimulasikan perjalanan waktu)
        this_thread::sleep_for(chrono::seconds(1));
    }

    return 0;
}
