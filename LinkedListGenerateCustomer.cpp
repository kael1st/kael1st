#include <iostream>
#include <chrono>
#include <thread>
using namespace std;
using namespace std::chrono_literals;

int MaxNode = 10; // jumlah maksimum antrian
int currentMode = 0; // mode generator pelanggan
int countNode = 0;

struct Customer
{
    int numberOfCustomers;
    double emotionalLevel; // Mengubah tipe data emosi menjadi double
    Customer *next;
    Customer *prev;
} *head, *tail;

Customer* CreateCustomer(int numb)
{
    Customer* Output = new Customer;
    Output->numberOfCustomers = numb;
    Output->emotionalLevel = 5.0; // Inisialisasi emosi dengan 5.0

    return Output;
}

void intialization()
{
    head == NULL && tail == NULL;
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
    if (isEmpty() == 1)
    {
        head = tail = cust;
    }
    else
    {
        cust->next = head;
        head->prev = cust;
        head = cust;
    }
    countNode++;
}

Customer* dequeue()
{
    Customer *Output = new Customer;
    Output->numberOfCustomers = tail->numberOfCustomers;
    Output->emotionalLevel = tail->emotionalLevel;

    Customer *temp = tail;
    tail = tail->prev;
    if (tail)
        tail->next = NULL;
    delete temp;
    countNode--;

    return Output;
}

void setMaxQueue(int max)
{
    MaxNode = max;
    cout << "Jumlah maksimal antrian adalah : " << MaxNode << endl;
}

void setCustomerGeneratorMode(int mode)
{
    currentMode = mode;
    cout << "Customer Generator Mode di set ke-" << currentMode << endl;
}

void decreaseEmotion()
{
    while (true)
    {
        if (!isEmpty())
        {
            Customer *cust = dequeue();
            if (cust->emotionalLevel > 0.0)
            {
                cust->emotionalLevel -= 0.5;
                cout << "Emosi pelanggan " << cust->numberOfCustomers << " berkurang menjadi " << cust->emotionalLevel << endl;
                if (cust->emotionalLevel <= 0.0)
                {
                    cout << "Customer " << cust->numberOfCustomers << " dengan emosi 0 telah dihapus dari antrian." << endl;
                    delete cust;
                    continue;
                }
                enqueue(cust);
            }
        }
        this_thread::sleep_for(2s); // Tunggu 2 detik sebelum mengurangi emosi lagi
    }
}

void generatorMode1()
{
    int customerCount = 0;
    int number = 1;
    while (true)
    {
        if (customerCount < MaxNode)
        {
            // Generate new customer group
            cout << number << ". Generated new customer group (Mode 1)" << endl;
            Customer *newCustomer = CreateCustomer(number);
            enqueue(newCustomer);
            customerCount++;
            number++;
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
    int number = 1;
    while (true)
    {
        if (customerCount < MaxNode)
        {
            // Generate new customer group
            cout << number << ". Generated new customer group (Mode 2)" << endl;
            Customer *newCustomer = CreateCustomer(customerCount + 1);
            enqueue(newCustomer);
            customerCount++;
            number++;
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
    int number = 1;
    int customerCount = 0;
    while (true)
    {
        // Generate new customer group
        cout << number << ". Generated new customer group (Mode 3)" << endl;
        Customer *newCustomer = CreateCustomer(customerCount + 1);
        enqueue(newCustomer);
        customerCount++;
        // Sleep for 4 seconds
        this_thread::sleep_for(4s);
        number++;
    }
}

void selamatDatang(){
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

void chooseMode ()
{
    cout << "Dinner Dash Game" << endl;
    cout << "=================================" << endl;
    cout << "Pilih Mode Generate Customer : ";
    cin >> currentMode;
}

int main()
{
    selamatDatang();
    intialization();
    setMaxQueue(10);


    chooseMode();

    setCustomerGeneratorMode(currentMode); // Set mode generator
    thread generatorThread;
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

    // Mulai thread untuk mengurangi emosi pelanggan
    thread emotionThread(decreaseEmotion);

    // Tunggu hingga thread generator selesai
    generatorThread.join();
    // Tunggu hingga thread pengurangan emosi selesai
    emotionThread.join();

    return 0;
}
