#include <stdio.h>

//notes: \033[1;<kode warna>m buat mewarnai teks.
//kode warna 0 mereset warna.

//menaruh '\0' di akhir string
void nullify(char str[], int bufsize) {
    for(int i = 0; i < bufsize; i++) {
        if(str[i] == '\n') {
            str[i] = '\0';
            break;
        }
    }
}

//mengubah input string menjadi integer (karena menggunakan fgets)
int strToInt(char str[]) {
    //num akan berakumulasi nilai ASCII dari karakter (0-9) - 48 (untuk mendapatkan nilai aslinya)
    int returnNum = 0;
    int invalidCounter = 0;
    for(int i = 0; str[i] != '\0'; i++) {
        if(str[i] >= 48 && str[i] <= 57) {
            returnNum = returnNum * 10 + (str[i] - 48); // setiap kali ini berjalan, posisi angka akan meng-shift. Misal 123 -> masuk 1 > 1 * 10 = 10 > masuk 2 = 12 > 12 * 10 = 120 > masuk 3 > 123.
        }

        else {
            return 300;
        }
    }
    return returnNum;
}

//mengembalikan diskon berdasarkan waktu yang dimasukkan
float hitungDiskon(int wktMain) {
    if(wktMain > 10) {
        return 0.25;
    } else if(wktMain > 8) {
        return 0.2;
    } else if(wktMain > 6) {
        return 0.15;
    } else if(wktMain > 4) {
        return 0.1;
    }
    return 0;
}

float hitungAkhir(int wktMain) {
    float diskon = hitungDiskon(wktMain);
    float hargaAkhir = 10000 * wktMain * (1 - diskon);
    printf("Lama pemakaian / waktu bermain           : %d jam\n", wktMain);
    printf("Diskon yang didapat                      : %.0f%%\n", diskon * 100);
    printf("Jumlah yang harus dibayar sebelum diskon : Rp%.0f,00\n", 10000 * (float) wktMain);
    printf("Jumlah akhir yang harus dibayar          : Rp%.0f,00\n\n", hargaAkhir);
}

int main() {
    const int bufferSize = 255;
    char waktuMain[bufferSize]; // buffer

    printf("\033[1;33mMasukkan durasi atau waktu bermain Anda (dalam jam): \033[1;0m");
    while(fgets(waktuMain, bufferSize, stdin)) { // dengan fgets tidak ada overflow, plus bisa memasukkan bufferSize langsung (beda dengan scanf). Tapi, ada \n yang perlu diganti di akhir string.
        printf("------------------------------------------------------\n");
        nullify(waktuMain, bufferSize); // menambah '\0' di akhir string;
        if(strToInt(waktuMain) == 300) {
            printf("Maaf, input Anda mengandung beberapa karakter invalid. Masukkan ulang waktu yang Anda inginkan\n\n");
            printf("\033[1;33mMasukkan durasi atau waktu bermain Anda (dalam jam): \033[1;0m");
            continue;
        }

        hitungAkhir(strToInt(waktuMain));
        //printf("2 * %d = %d", strToInt(waktuMain), 2 * strToInt(waktuMain));

        printf("\033[1;33mMasukkan durasi atau waktu bermain Anda (dalam jam): \033[1;0m");
    }

    return 0;
}