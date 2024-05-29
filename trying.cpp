#include <stdio.h>

#define MAX_PLAYERS 100
#define MAX_NAME_LENGTH 15

char namaPlayer[MAX_PLAYERS][MAX_NAME_LENGTH];
int playerAttack[MAX_PLAYERS];
int playerCooldown[MAX_PLAYERS];
int playerDefense[MAX_PLAYERS];
int player = 0;

void tampilMenu();
void inputData();
void daftarPlayer();
void tambahAttribut();
void tampilAttribut();

int main() {
    printf("------------------------------\n");
    printf("       Selamat Datang\n");
    printf("------------------------------\n");

    int choice;
    do {
        tampilMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                inputData();
                break;

            case 2:
                printf("\nDaftar Pemain\n");
                daftarPlayer();
                break;

            case 3:
                tambahAttribut();
                break;

            case 4:
                tampilAttribut();
                break;

            case 5:
                printf("Terima kasih, program selesai.\n");
                break;

            default:
                printf("Pilihan tidak valid, silakan coba lagi.\n");
        }

    } while (choice != 5);

    return 0;
}

void tampilMenu() {
    printf("\n------------------------------\n");
    printf("Daftar Menu:\n");
    printf("1. Input Data Player\n");
    printf("2. Tampilkan Daftar Player\n");
    printf("3. Tambah Atribut Player\n");
    printf("4. Tampilkan Atribut Player\n");
    printf("5. Exit\n");
    printf("Pilih Menu: ");
}

void inputData() {
    char data = 'y';
    while ((data == 'y' || data == 'Y') && player < MAX_PLAYERS) {
        printf("Masukkan nama player ke-%d : ", player + 1);
        scanf("%s", namaPlayer[player]);

        printf("Lanjut Y atau N ? ");
        scanf(" %c", &data);

        player++;
    }

    if (player >= MAX_PLAYERS) {
        printf("Jumlah pemain maksimal tercapai.\n");
    }
}

void daftarPlayer() {
    printf("Jumlah pemain saat ini: %d\n", player);
    if (player != 0) {
        printf("\n------------------------\n");
        printf("| No.| Nama\t\t\t  |\n");
        printf("------------------------\n");
        for (int i = 0; i < player; i++) {
            printf("| %2d | %15s |\n", i + 1, namaPlayer[i]);
            printf("------------------------\n");
        }
    } else {
        printf("Belum ada pemain.\n");
    }
}

void tambahAttribut() {
    printf("\nTambah Atribut Player\n");
    for (int i = 0; i < player; i++) {
        printf("Masukkan Attack untuk %s : ", namaPlayer[i]);
        scanf("%d", &playerAttack[i]);

        printf("Masukkan Cooldown untuk %s : ", namaPlayer[i]);
        scanf("%d", &playerCooldown[i]);

        printf("Masukkan Defense untuk %s : ", namaPlayer[i]);
        scanf("%d", &playerDefense[i]);
    }
}

void tampilAttribut() {
    printf("\n-----------------------------------------------------\n");
    printf("| No.| Nama\t\t\t  | Attack | Cooldown | Defense |\n");
    printf("-----------------------------------------------------\n");
    for (int i = 0; i < player; i++) {
        printf("| %2d | %15s | %6d | %7d | %7d |\n", i + 1, namaPlayer[i], playerAttack[i], playerCooldown[i], playerDefense[i]);
        printf("-----------------------------------------------------\n");
    }
}