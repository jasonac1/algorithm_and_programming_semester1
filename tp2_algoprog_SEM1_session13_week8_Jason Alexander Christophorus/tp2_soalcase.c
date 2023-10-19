#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define YELLOW "\e[0;33m"
#define GREEN "\e[0;32m"
#define GREENBOLD "\e[1;32m"
#define RED "\e[0;31m"
#define RESET "\e[0;0m"
#define MAXCHARBULAN 10 // maximum 10 karakter (september + '\0\');

//mengecek jika karakter dalam alfabet
int inAlphabet(char c);

//seperti fflush(stdin) tapi lebih optimal seperti ini
void clearstdin();

//mendisplay input invalid
void invalidInput(char* s);

//memberikan nilai terhadap array integer jumlah huruf vokal dan non-vokal (konsonan)
void vowelsConsonants(int* destination, char* source);

//apakah huruf vokal atau bukan
int inVowels(char c);

int main(void) {
    //1. menghandle pilihan
    char k; //karakter
    char listBulan[12][MAXCHARBULAN] = {"Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"};
    char listBulanPilihan[12][MAXCHARBULAN];
    while(1) {
        printf("Masukkan karakter awalan (Program hanya akan membaca karakter pertama): ");
        scanf("%c", &k);

        //jika tidak dalam alfabet maka skip iterasi, minta input lagi
        if(!inAlphabet(k)) {
            invalidInput("Karakter ini tidak ada dalam alfabet. Mohon masukkan karakter lain.\n\n");
            clearstdin();
            continue;
        }

        //jika iya, lanjut looping semua bulan dan mengecek huruf awalannya
        int i;
        int indexBulanPilihan = 0;
        char* ptrBulan;
        for(i = 0; i < 12; i++) {
            ptrBulan = listBulan[i]; // pointer ke char array (bulan index kini)
            if(toupper(k) == ptrBulan[0]) { // jika huruf awalan sama
                strcpy(listBulanPilihan[indexBulanPilihan], ptrBulan);
                indexBulanPilihan++; // lanjut ke index berikutnya di listBulanPilihan
            }
        }

        //jika tidak ditemukan bulan dengan karakter awalan k di index manapun maka akan lanjut ke iterasi berikutnya, dan meminta input lagi
        if(indexBulanPilihan == 0) {
            printf("%sMaaf, bulan dengan karakter awalan '%c' tidak dapat kami temukan. Mohon masukkan karakter lain.\n\n%s", RED, toupper(k), RESET);
            clearstdin();
            continue;
        }
        int j; int listBulanPilihanSize = indexBulanPilihan; // untuk looping array list bulan pilihan (di iterasi for akhir, dia akan ter-increment jadi nilainya akan pas dengan index yang sekarang out-of-bounds / 1 + index akhir = size)   
        printf("%sDitemukan %d bulan dengan awalan karakter '%c', diantaranya:\n%s", YELLOW, listBulanPilihanSize, toupper(k), RESET);
        for(j = 0; j < listBulanPilihanSize; j++) {
            printf("%s (%d)\n", listBulanPilihan[j], j+1);
        }
        printf("\n");

        //meminta input pilihan bulan
        int angkaPilihan;

        //menanyakan terus jika ada invalid input, jika tidak akan lanjut
        while(1) {
            clearstdin(); // menghilangkan buffer overflow dari input karakter pertama
            printf("Masukkan pilihan anda (angka yang dipasangkan pada setiap bulan, program akan mengabaikan karakter lainnya): ");
            scanf("%d", &angkaPilihan); //jika tidak integer maka akan mengembalikan 0.

            //jika tidak memenuhi kriteria di antara 1-pilihan terbesar maka akan meminta input ulang
            if(angkaPilihan == 0 || angkaPilihan < 1 || angkaPilihan > listBulanPilihanSize) {
                invalidInput("Pilihan hanya boleh bilangan bulat antara 1 dan angka terbesar (inklusif).\n\n");
                continue;
            }

            //jika iya, maka break.
            break;
        }

        //mencetak bulan pilihan
        char bulanPilihan[MAXCHARBULAN]; 
        strcpy(bulanPilihan, listBulanPilihan[angkaPilihan-1]);
        printf("%sBulan yang dipilih: %s%s\n%s", GREEN, GREENBOLD, bulanPilihan, RESET);

        //2. menghandle penghitungan huruf vokal dan huruf konsonan (non-vokal)
        int vokalDanKonsonan[2];
        vowelsConsonants(vokalDanKonsonan, bulanPilihan);
        printf("Jumlah huruf vokal dalam nama bulan %s: %d\n", bulanPilihan, vokalDanKonsonan[0]);
        printf("Jumlah huruf non-vokal dalam nama bulan %s: %d\n", bulanPilihan, vokalDanKonsonan[1]);
        printf("\n");
        clearstdin();
    }
}

int inAlphabet(char c) {
    char* alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHJIKLMNOPQRSTUVWXYZ";
    int i;
    for(i = 0; alphabet[i] != '\0'; i++) {
        if(c == alphabet[i])  {
            return 1;
        }
    }
    return 0;
}

void clearstdin() {
    int c;
    while((c = getchar()) != '\n' && c != EOF) {
        ;
    }
}

void invalidInput(char* s) {
    printf("%sMaaf, input Anda invalid. %s%s", RED, s, RESET);
}

void vowelsConsonants(int* destination, char* source) {
    int vow = 0; int con = 0;
    int i;
    for(i = 0; source[i] != '\0'; i++) { 
        switch(tolower(source[i])) {
            case 'a':
            case 'i':
            case 'u':
            case 'e':
            case 'o':
                vow++;
                break;
            
            default:
                con++;
        }
    }
    destination[0] = vow;
    destination[1] = con;
}