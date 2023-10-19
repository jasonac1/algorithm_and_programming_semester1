#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define YELLOW "\e[0;33m"
#define RED "\e[0;31m"
#define RESET "\e[0;0m"

int inAlphabet(char c);
void clearstdin();
void invalidInput(char* s);

//note to self:
//SEGFAULT CAUSES
//1. CHECK IF ANY ARRAYS ARE ACCESSING OUT OF BOUNDS
//2. CHECK IF YOU PASS THE CORRECT NUMBER OF ARGUMENTS INTO PRINTF AND IF THEIR FORMATTING ALIGNS. A GOOD SIGN IS AN ERROR IN STDIO.H SAYING STDOUT (THERES AN ISSUE WITH OUTPUT FORMATTING)
//3. DONT FORGET SCANF AND VARIABLE ADDRESSES. USE & FOR NON POINTERS AND DON'T OTHERWISE.

int main(void) {
    //1. menghandle pilihan
    char k; //karakter
    char listBulan[12][10] = {"Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"};
    char listBulanPilihan[12][10];
    //september paling panjang 9 karakter, jadi max size per stringnya 10 (termasuk \0)
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

        if(indexBulanPilihan == 0) {
            printf("%sMaaf, bulan dengan awalan karakter %c tidak dapat kami temukan. Mohon masukkan karakter lain.\n\n%s", RED, k, RESET);
            clearstdin();
            continue;
        }
        int j; int listBulanPilihanSize = indexBulanPilihan; // untuk looping array list bulan pilihan (di iterasi for akhir, dia akan ter-increment jadi nilainya akan pas dengan index yang sekarang out-of-bounds / 1 + index akhir = size)   
        printf("%sDitemukan %d bulan dengan awalan karakter '%c', diantaranya:\n%s", YELLOW, listBulanPilihanSize, toupper(k), RESET);
        for(j = 0; j < listBulanPilihanSize; j++) {
            printf("%s\n", listBulanPilihan[j]);
        }
        printf("\n");
        clearstdin();
    }

    /*int debug;
    for(debug = 0; debug < 12; i++) {
        printf("%s\n", listBulan[debug]);
    }*/
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

/*void invalidInput(char* s) {
    printf("%sMaaf, input Anda invalid. %s%s", RED, s, RESET);
}*/