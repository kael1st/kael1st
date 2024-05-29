#include <iostream>
#include <chrono>
#include <thread>
using namespace std;
using namespace std::chrono_literals;

const int MaxNode = 10; // jumlah maksimum antrian
int currentMode = 0; // mode generator pelanggan
int countNode = 0;

struct Customer
{
    int numberOfCustomers;
    int emotionalLevel;
};

Customer queue[MaxNode]; // array untuk menyimpan antrian
int front = 0; // pointer untuk mengakses elemen depan antrian
int rear = -1; // pointer untuk mengakses elemen belakang antrian

Customer* CreateCustomer (int numb)
{
    Customer* Output = new Customer;
    Output->numberOfCustomers = numb;
    Output->emotionalLevel = 5;
    return Output;
}

void intialization()
{
    front = 0;
    rear = -1;
    countNode = 0;
}

bool isFull()
{
    return countNode == MaxNode;
}

bool isEmpty()
{
    return countNode == 0;
}

void enqueue(Customer *cust)
{
    if (!isFull())
    {
        rear = (rear + 1) % MaxNode;
        queue[rear] = *cust;
        countNode++;
    }
    else
    {
        cout << "Queue is full. Cannot enqueue." << endl;
    }
}

Customer* dequeue()
{
    if (!isEmpty())
    {
        Customer *output = new Customer;
        *output = queue[front];
        front = (front + 1) % MaxNode;
        countNode--;
        return output;
    }
    else
    {
        cout << "Queue is empty. Cannot dequeue." << endl;
        return nullptr;
    }
}

void setMaxQueue(int max)
{
    cout << "Jumlah maksimal antrian diubah menjadi : " << max << endl;
}

void setCustomerGeneratorMode(int mode)
{
    currentMode = mode;
    cout << "Customer Generator Mode di set ke-" << currentMode << endl;
}

void generatorMode1()
{
    int customerCount = 0;
    while (true)
    {
        if (customerCount < MaxNode)
        {
            // Generate new customer group
            cout << "Generated new customer group (Mode 1)" << endl;
            customerCount++;
        }
        else
        {
            break;
        }
        // Sleep for 1 second
        this_thread::sleep_for(1s);
    }
}

void generatorMode2()
{
    int customerCount = 0;
    while (true)
    {
        if (customerCount < MaxNode)
        {
            // Generate new customer group
            cout << "Generated new customer group (Mode 2)" << endl;
            customerCount++;
        }
        else
        {
            break;
        }
        // Sleep for 4 seconds
        this_thread::sleep_for(4s);
    }
}

void generatorMode3()
{
    while (true)
    {
        // Generate new customer group
        cout << "Generated new customer group (Mode 3)" << endl;
        // Sleep for 4 seconds
        this_thread::sleep_for(4s);
    }
}

int main()
{
    intialization();
    setMaxQueue(MaxNode);

    setCustomerGeneratorMode(1); // Set mode generator
    thread generatorThread;

    system("cls");
    cout << "Pilih Mode Generate Customer : ";
    cin >> currentMode;
    // Pilih fungsi generator sesuai dengan mode yang dipilih
    switch (currentMode)
    {
    case 1:
        generatorThread = thread(generatorMode1);
        break;
    case 2:
        generatorThread = thread(generatorMode2);
        break;
    case 3:
        generatorThread = thread(generatorMode3);
        break;
    default:
        cout << "Invalid mode selected!" << endl;
        return 1;
    }

    // Tunggu hingga thread generator selesai
    generatorThread.join();

    return 0;
}
