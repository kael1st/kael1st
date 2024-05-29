#include <iostream>
#include <unordered_map>
#include <queue>
#include <thread>
#include <chrono>
#include <ctime>

using namespace std;

// Struct for Customer
struct Customer {
    int NumberOfCustomer;
    int EmotionalLevel;
    bool OrderProcessed;
};

// Function prototype
Customer CreateCustomer();
void EnqueueCustomer(queue<Customer>& customerQueue, int maxQueueSize);
Customer DequeueCustomer(queue<Customer>& customerQueue);
void WelcomeMessage();
void TakeOrder(int tableNumber, Customer& customer, unordered_map<int, queue<string>>& kitchen, int& heldOrder, const unordered_map<int, pair<int, bool>>& tables, unordered_map<int, string>& menuNumber);
void PutOrderToKitchen(int& heldOrder, unordered_map<int, queue<string>>& kitchen, const unordered_map<int, pair<int, bool>>& tables, unordered_map<int, string>& menuNumber);
void DisplayKitchenStatus(const unordered_map<int, queue<string>>& kitchen);
void DisplayTableInfo(const unordered_map<int, pair<int, bool>>& tables);
void GenerateMenu(const unordered_map<int, queue<string>>& kitchen, unordered_map<int, bool>& menuStatus, unordered_map<int, string>& menuNumber);
void PlaceMenu(int tableNumber, unordered_map<int, string>& menuNumber, unordered_map<int, queue<string>>& kitchen);
void CustomerEat();
bool GenerateMoney(queue<int>& tableQueue, int& tableNumber);
bool CleanTheTable(int tableNumber, unordered_map<int, bool>& dirtyPlates);
void DisposeDirtyPlates(unordered_map<int, bool>& dirtyPlates, unordered_map<int, int>& trashCan);

// Function to create a new customer
Customer CreateCustomer() {
    Customer output;
    output.NumberOfCustomer = rand() % 6 + 1;
    output.EmotionalLevel = 5;
    output.OrderProcessed = false;
    return output;
}

// Function to enqueue a customer
void EnqueueCustomer(queue<Customer>& customerQueue, int maxQueueSize) {
    if (customerQueue.size() >= maxQueueSize) {
        cout << "Antrian pelanggan sudah penuh." << endl;
        return;
    }

    Customer newCustomer = CreateCustomer();
    customerQueue.push(newCustomer);
    cout << "Pelanggan dengan jumlah " << newCustomer.NumberOfCustomer << " telah dimasukkan ke dalam antrian." << endl;
}


// Function to take order from a customer
void TakeOrder(int tableNumber, Customer& customer, unordered_map<int, queue<string>>& kitchen, int& heldOrder, const unordered_map<int, pair<int, bool>>& tables, unordered_map<int, string>& menuNumber) {
    if (customer.OrderProcessed) {
        cout << "You already have an order in hand." << endl;
        return;
    }

    if (tables.find(tableNumber) == tables.end()) {
        cout << "Invalid table number." << endl;
        return;
    }

    if (tables.at(tableNumber).second) {
        if (customer.NumberOfCustomer <= tables.at(tableNumber).first) {
            cout << "You take the order from table number " << tableNumber << "." << endl;
            heldOrder = tableNumber;
            customer.OrderProcessed = true;
        } else {
            cout << "Not enough seats available at the table. Please choose another table." << endl;
        }
    } else {
        cout << "The table is not suitable. Please choose another table." << endl;
    }
}

// Function to put order to kitchen
void PutOrderToKitchen(int& heldOrder, unordered_map<int, queue<string>>& kitchen, const unordered_map<int, pair<int, bool>>& tables, unordered_map<int, string>& menuNumber) {
    if (heldOrder == 0) {
        cout << "You don't have any order in your hand." << endl;
        return;
    }

    if (tables.find(heldOrder) == tables.end()) {
        cout << "Invalid table number." << endl;
        heldOrder = 0;
        return;
    }

    if (!tables.at(heldOrder).second) {
        cout << "The table is not suitable." << endl;
        heldOrder = 0;
        return;
    }

    if (tables.at(heldOrder).first < 1) {
        cout << "Not enough seats available at the table." << endl;
        heldOrder = 0;
        return;
    }

    string order;
    cout << "Please put the order to kitchen from table number " << heldOrder << " (input number that same with table number): ";
    cin >> order;

    // Check if the order matches the held order
    if (order != to_string(heldOrder)) {
        cout << "Invalid order number. Please choose the correct order." << endl;
        PlaceMenu(heldOrder, menuNumber, kitchen);
        return;
    }

    kitchen[heldOrder].push(order);
    system("cls");
    cout << "Dinner Dash" << endl;
    cout << "=================================" << endl;
    cout << "Order put to kitchen from table number " << heldOrder << "." << endl;

    heldOrder = 0; // Reset heldOrder after putting the order to kitchen

    // Process menu automatically after 5 seconds
    cout << "Processing menu from order for 5 seconds..." << endl;
    this_thread::sleep_for(chrono::seconds(5));
    cout << "Menu processed." << endl;

    // After processing menu, place menu to table
    PlaceMenu(heldOrder, menuNumber, kitchen);
}

// Function to display kitchen status
void DisplayKitchenStatus(const unordered_map<int, queue<string>>& kitchen) {
    cout << "Kitchen Status:" << endl;
    for (const auto& item : kitchen) {
        cout << "Table Number: " << item.first << endl;
        cout << "Orders in Kitchen:" << endl;
        if (item.second.empty()) {
            cout << "No orders in kitchen from this table." << endl;
        } else {
            queue<string> orders = item.second;
            while (!orders.empty()) {
                cout << "- " << orders.front() << endl;
                orders.pop();
            }
        }
        cout << endl;
    }
}

// Function to display table information
void DisplayTableInfo(const unordered_map<int, pair<int, bool>>& tables) {
    system("cls");
    cout << "Dinner Dash" << endl;
    cout << "=================================" << endl;
    cout << "Table Information:" << endl;
    for (const auto& table : tables) {
        cout << "Table Number: " << table.first << endl;
        cout << "Number of Seats: " << table.second.first << endl;
        if (!table.second.second) {
            cout << "Status: Occupied" << endl;
        } else {
            cout << "Status: Available" << endl;
        }
        cout << endl;
    }
}

// Function to place menu to table
void PlaceMenu(int tableNumber, unordered_map<int, string>& menuNumber, unordered_map<int, queue<string>>& kitchen) {
    system("cls");
    cout << "Dinner Dash" << endl;
    cout << "=================================" << endl;
    if (kitchen.find(tableNumber) == kitchen.end() || kitchen[tableNumber].empty()) {
        cout << "No orders available. Please generate the menu first." << endl;
        return;
    }

    // Extract orders from kitchen queue and store in a vector for easy iteration
    vector<string> orders;
    while (!kitchen[tableNumber].empty()) {
        orders.push_back(kitchen[tableNumber].front());
        kitchen[tableNumber].pop();
    }

    // Display menu numbers available for the table
    cout << "Menu numbers available for table " << tableNumber << ":" << endl;
    for (const auto& order : orders) {
        cout << "- " << order << endl;
    }

    int MenuNumber;
    bool validMenuNumber = false;
    while (!validMenuNumber) {
        cout << "Enter menu number to place on table " << tableNumber << ": ";
        cin >> MenuNumber;

        if (menuNumber[tableNumber] == to_string(MenuNumber)) {
            validMenuNumber = true;
        } else {
            cout << "Invalid menu number. Please choose from the available menu numbers." << endl;
        }
    }

    // Place menu on table
    system("cls");
    cout << "Dinner Dash" << endl;
    cout << "=================================" << endl;
    cout << "Menu " << MenuNumber << " placed on table " << tableNumber << "." << endl;
}


// Function for customers to eat
void GenerateMenu(const unordered_map<int, queue<string>>& kitchen, unordered_map<int, bool>& menuStatus, unordered_map<int, string>& menuNumber) {
    int tableNumber;
    bool validTableNumber = false;
    while (!validTableNumber) {
        cout << "Enter table number to generate menu: ";
        cin >> tableNumber;

        if (kitchen.find(tableNumber) != kitchen.end() && !kitchen.at(tableNumber).empty()) {
            // Process orders in kitchen
            menuStatus[tableNumber] = true; // Set menu status as processed
            menuNumber[tableNumber] = to_string(tableNumber); // Assign menu number same as table number
            cout << "Menu generated for table number " << tableNumber << "." << endl;
            validTableNumber = true;
        } else {
            cout << "There are no orders in kitchen for table number " << tableNumber << ". Please choose another table." << endl;
        }
    }
}

// Function for customers to eat
void CustomerEat() {
    int eatTimer = 5; // Set eat timer to 5 seconds

    // Simulate eating for 5 seconds
    while (eatTimer > 0) {
        cout << "Customer is eating... " << eatTimer << " seconds left" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        eatTimer--;
    }

    cout << "Customer has finished eating" << endl;
}

// Function to generate money after customers finish eating
bool GenerateMoney(queue<int>& tableQueue, int& tableNumber) {
    if (tableQueue.empty()) {
        cout << "All tables have been processed. No more money to generate." << endl;
        return false;
    }

    tableNumber = tableQueue.front(); // Get the table number from the front of the queue
    tableQueue.pop(); // Remove the processed table from the queue

    // Generate money for the processed table
    cout << "You've got the money from table " << tableNumber << endl;
    return true;
}


// Function to dequeue a customer
Customer DequeueCustomer(queue<Customer>& customerQueue) {
    Customer dequeuedCustomer = customerQueue.front(); // Get the front customer in the queue
    customerQueue.pop(); // Remove the dequeued customer from the queue
    return dequeuedCustomer;
}

// Function to clean the table and generate dirty plate
bool CleanTheTable(int tableNumber, unordered_map<int, bool>& dirtyPlates) {
    // Clean the table (generate dirty plate)
    cout << "Customer from table number " << tableNumber << " has been dequeued. A dirty plate is generated." << endl;
    dirtyPlates[tableNumber] = true;
    return true;
}

// Function to dispose dirty plates into trash can
void DisposeDirtyPlates(unordered_map<int, bool>& dirtyPlates, unordered_map<int, int>& trashCan) {
    int tableNumber;
    bool validTableNumber = false;

    while (!validTableNumber) {
        cout << "Enter table number to dispose dirty plate into trash can: ";
        cin >> tableNumber;

        if (dirtyPlates.find(tableNumber) != dirtyPlates.end() && dirtyPlates[tableNumber]) {
            // Dispose dirty plate into trash can
            system("cls");
            cout << "Dinner Dash" << endl;
            cout << "=================================" << endl;
            trashCan[tableNumber]++;
            cout << "Dirty plate from table " << tableNumber << " disposed into trash can." << endl;
            dirtyPlates[tableNumber] = false; // Reset dirty plate status for the table
            validTableNumber = true;
        } else {
            cout << "Invalid table number or no dirty plate available. Please choose another table." << endl;
        }
    }
}

void WelcomeMessage() {
    system("cls");
    cout << "Selamat datang di Game Dinner Dash" << endl;
    cout << "=================================" << endl;
    cout << "GT11B Algoritma dan Struktur Data" << endl;
    cout << "Oleh : \nYudha Prawira            (5223600047)\nMichael Maeda Difaputra  (5223600048)\nRaden Harza Daffa Rajendra  (5223600050)" << endl;
    cout << "=================================" << endl;
    cout << "Ketik Enter untuk memulai Permainan" << endl;
    cin.get();
    system("cls");
}

void ServeNextCustomer(queue<Customer>& customerQueue, unordered_map<int, queue<string>>& kitchen, unordered_map<int, pair<int, bool>>& tables, int& heldOrder, unordered_map<int, bool>& menuStatus, unordered_map<int, string>& menuNumber, unordered_map<int, bool>& dirtyPlates, unordered_map<int, int>& trashCan, queue<int>& tableQueue) {
    // If there are no more customers, return
    if (customerQueue.empty()) {
        cout << "All customers have been served. Game finished." << endl;
        return;
    }

    // Take the next customer from the queue
    Customer nextCustomer = customerQueue.front();
    customerQueue.pop();

    // Display table information
    DisplayTableInfo(tables);

    // Display customer information
    cout << "Next Customer Information:" << endl;
    cout << "Number of Customers: " << nextCustomer.NumberOfCustomer << endl;
    cout << "Emotional Level: " << nextCustomer.EmotionalLevel << endl;

    int tableNumber;
    bool validTableNumber = false;
    while (!validTableNumber) {
        cout << "Enter table number to place customer (1-3): ";
        cin >> tableNumber;
        TakeOrder(tableNumber, nextCustomer, kitchen, heldOrder, tables, menuNumber);
        if (heldOrder != 0) {
            validTableNumber = true;
        }
    }

    // Wait for 5 seconds before taking order
    cout << "Waiting for 5 seconds to generate order..." << endl;
    this_thread::sleep_for(chrono::seconds(5));

    // Put order to kitchen
    PutOrderToKitchen(heldOrder, kitchen, tables, menuNumber);

    // Display kitchen status
    DisplayKitchenStatus(kitchen);

    // Generate menu based on orders in kitchen
    GenerateMenu(kitchen, menuStatus, menuNumber);

    // Place menu to table
    for (const auto& item : menuNumber) {
        if (item.second != "") {
            PlaceMenu(item.first, menuNumber, kitchen);
        }
    }

    // Customers eat
    CustomerEat();

    // Input table number where the customer ate to generate money
    cout << "Enter the table number where the customer ate: ";
    cin >> tableNumber;
    cout << "Generate Money from table number " << tableNumber << endl;

    // Generate money after customers finish eating
    if (GenerateMoney(tableQueue, tableNumber)) {
        // Dequeue the customer
        cout << "Dequeueing customer..." << endl;
        cout << "Customer dequeued." << endl;
    }

    // Clean the table and generate dirty plate
    CleanTheTable(tableNumber, dirtyPlates);

    // Dispose dirty plates into trash can
    DisposeDirtyPlates(dirtyPlates, trashCan);

    // Serve the next customer
    ServeNextCustomer(customerQueue, kitchen, tables, heldOrder, menuStatus, menuNumber, dirtyPlates, trashCan, tableQueue);
}


void selamatDatang() {
    system("cls");
    cout << "Selamat datang di Game Dinner Dash" << endl;
    cout << "=================================" << endl;
    cout << "GT11B Algoritma dan Struktur Data" << endl;
    cout << "Oleh : \nYudha Prawira            (5223600047)\nMichael Maeda Difaputra  (5223600048)\nRaden Harza Daffa Rajendra  (5223600050)" << endl;
    cout << "=================================" << endl;
    cout << "Ketik Enter untuk memulai Permainan" << endl;
    cin.get();
    system("cls");
}

int main() {
    // Deklarasi tableQueue di sini
    queue<int> tableQueue;

    srand(time(0)); // Set random seed based on current time

    selamatDatang();

    unordered_map<int, pair<int, bool>> tables;
    tables[1] = make_pair(2, true); // Table 1 with 2 seats, initially available
    tables[2] = make_pair(4, true); // Table 2 with 4 seats, initially available
    tables[3] = make_pair(6, true); // Table 3 with 6 seats, initially available

    queue<Customer> customerQueue;
    const int maxQueueSize = 4;

    unordered_map<int, queue<string>> kitchen;
    unordered_map<int, bool> menuStatus;
    unordered_map<int, string> menuNumber;
    unordered_map<int, bool> dirtyPlates; // Record dirty plates status for each table
    unordered_map<int, int> trashCan; // Trash can to dispose dirty plates

    int heldOrder = 0; // Nomor meja pesanan yang dipegang oleh pemain (0 jika tidak ada)

    // Enqueue customers
    for (int i = 0; i < maxQueueSize; ++i) {
        EnqueueCustomer(customerQueue, maxQueueSize); // Memanggil fungsi EnqueueCustomer untuk menambahkan pelanggan ke dalam antrian
    }

    // Serve the first customer
    ServeNextCustomer(customerQueue, kitchen, tables, heldOrder, menuStatus, menuNumber, dirtyPlates, trashCan, tableQueue);

    return 0;
}
