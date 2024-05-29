#include <iostream>
using namespace std;

struct Gerbong
{
    string Nama;
    Gerbong *next;
    Gerbong *prev;
};

void printLinkedList(Gerbong *start)
{
    Gerbong *current = start;
    while (current != nullptr)
    {
        cout << current->Nama << " --> ";
        current = current->next;
    }
    cout << "nullptr" << endl;
}

int main()
{
    Gerbong satu, dua, tiga;

    satu.next = &tiga; // menyambungkan gerbong 1 dengan gerbong 3
    satu.prev = nullptr;
    tiga.prev = &satu; // update gerbong 1 sebelum gerbong 3
    
    dua.next = nullptr; // Hapus gerbong 2

    satu.Nama = "Gerbong 1";
    dua.Nama = "Gerbong 2";
    tiga.Nama = "Gerbong 3";

    // Sekarang gerbong 2 sudah terhapus dan gerbong 1 dengan gerbong 3 sudah tersambung
    // Tampilkan Linked List setelah modifikasi di console
    cout << "Linked List setelah modifikasi: ";
    printLinkedList(&satu);
    
    return 0;
}
