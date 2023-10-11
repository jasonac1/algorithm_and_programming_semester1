#include <stdio.h>
#define GREEN "\033[0;32m"
#define WHITEBOLD "\033[1;37m"
#define RESET "\033[0;0m"

//color code format "\033[(num);(color)m". num = 0 untuk teks biasa, 1 untuk bold.

//mengganti \n di akhir string yang didapat dari fgets menjadi \0
void nullify(char s[], int bufsize) {
    for(int i = 0; i < bufsize; i++) {
        if(s[i] == '\n') {
            s[i] = '\0';
            break;
        }
    }
}

//memprint message untuk meminta input pengguna
void displayMessage() {
    printf("Masukkan total pembelian Anda (masukkan angka bulat saja): Rp");
}

//memprint garis
void line() {
    printf("-----------------------------------------------------------\n");
}

void prosesTransaksi(int totalBeli, float * arrayTransaksiAkhir);
int strToInt(char s[]);

int main() {
    char totalPembelianStr[255]; // buffer
    int totalPembelian;
    float hasilTransaksiAkhir[4];

    displayMessage();
    while(fgets(totalPembelianStr, 255, stdin)) {
        line();
        nullify(totalPembelianStr, 255);
        totalPembelian = strToInt(totalPembelianStr);
        
        //cek input kosong
        if(totalPembelianStr[0] == '\0') {
            printf("Maaf, input Anda tidak boleh kosong.\n\n");
            displayMessage();
            continue;
        }

        //cek input invalid
        if(strToInt(totalPembelianStr) == -1) {
            printf("Maaf, input Anda mengandung karakter invalid. Karakter yang diperbolehkan hanya angka (0-9).\n\n");
            displayMessage();
            continue;
        }
        //printf("total: %d", strToInt(totalPembelian));
        prosesTransaksi(totalPembelian, hasilTransaksiAkhir);
        float awal = hasilTransaksiAkhir[0];
        float kupon = hasilTransaksiAkhir[1];
        float diskon = hasilTransaksiAkhir[2];
        float akhir = hasilTransaksiAkhir[3];

        printf("%sTRANSAKSI\n%s", WHITEBOLD, RESET);
        line();
        printf("Harga awal                  : Rp%.0f\n", awal);
        printf("Kupon undian yang didapat   : %.0f\n", kupon);
        if(kupon > 5) {
            printf("%sDiskon yang didapat         : 25.00%% (max. 5 kupon)\n%s", GREEN, RESET);
        } else if(kupon > 0) {
            printf("%sDiskon yang didapat         : Rp%.2f%%\n%s", GREEN, diskon * 100, RESET);
        } else {
            printf("Diskon yang didapat         : Rp0.00%%\n");
        }
        printf("Anda menghemat              : Rp%.0f\n", awal-akhir);
        printf("Harga akhir                 : Rp%.0f\n", akhir);
        line();
        printf("\n");
        displayMessage();
    }
    return 0;
}

//mengubah string menjadi integer (karena menggunakan fgets)
int strToInt(char s[]) {
    //returnVal akan mengakumulasi nilai ASCII dari angka yang dimasukkan - 48 untuk mendapatkan nilai aslinya, misal '1' == ASCII 49 - 48 = 1. 
    int returnVal = 0;
    for(int i = 0; s[i] != '\0'; i++) {
        if(s[i] >= 48 && s[i] <= 57) {
            //angka yang sudah ada di"shift" ke kiri dengan mengalikan 10 untuk menyediakan ruang untuk digit selanjutnya.
            returnVal = (returnVal * 10) + (s[i] - 48); 
        } else {
            return -1; // error code -1;
        }
    }
    return returnVal;
}

//pass by reference int array (memasukkan nilai ke array yg dipass ke function)
void prosesTransaksi(int totalBeli, float * arrayTransaksiAkhir) {
    float hargaAwal = totalBeli;
    float jmlKupon; // 1 per Rp100.000,00
    float diskon; // 5% per kupon, dimaksimalkan 25% atau 5 kupon supaya realistis
    float hargaAkhir;

    //menentukan jumlah kupon
    jmlKupon = totalBeli / 100000; // tidak diapa-apakan karena sudah mengambil hasil bulatnya saja (seperti Math.floor di JS)

    //menentukan diskon dr kupon (0.05 -> 5%)
    diskon = (float)jmlKupon * 0.05;
    if(diskon > 0.25) {
        diskon = 0.25;
    }

    //harga akhir
    hargaAkhir = (1-diskon)*hargaAwal;

    //memasukkan nilai akhir ke array yang dipass ke function.
    arrayTransaksiAkhir[0] = hargaAwal;
    arrayTransaksiAkhir[1] = jmlKupon;
    arrayTransaksiAkhir[2] = diskon;
    arrayTransaksiAkhir[3] = hargaAkhir;
}