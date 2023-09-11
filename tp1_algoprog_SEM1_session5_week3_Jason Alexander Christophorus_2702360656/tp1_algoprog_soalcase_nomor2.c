#include <stdio.h>
#include <stdlib.h>

int akhir_dan_diskon(int jml_transaksi, int total_belanja) {
    /*penghitungan: ada 2 diskon,
    diskon 1 (diskonHarga) adalah diskon dari besar harga (Rp... - Rp...) di mana ada 3 range harga.
    diskon 2 (diskonTransaksi) adalah diskon dari transaksi (jika berjumlah 4 atau lebih).
    kedua diskon diberlakukan secara kumulatif (berturut-turut). 

    Misal: 1.000.000 rupiah - diskon 30% - diskon 20% menjadi:
    1.000.000 - 30% * (1.000.000) = 700.000
    -> 700.000 - 20% * (700.000) = 560.000. (44%, lebih untung bagi perusahaan)

    Jika diskon tersebut ditambah saja maka menjadi diskon 50% = 500.000.
    */
    float diskonHarga;
    float diskonTransaksi;
    float total_akhir = total_belanja;

    //penghitungan diskonHarga
    if(total_belanja < 200000) {
        diskonHarga = 0; // 0% (< Rp200.000,00)
    }

    if(total_belanja >= 200000 && total_belanja <= 500000) {
        diskonHarga = 0.1; // 10% (Rp200.000,00 - Rp500.000,00)
    }

    if(total_belanja >= 500001 && total_belanja <= 1000000) {
        diskonHarga = 0.2; // 20% (Rp500.001,00 - Rp1.000.000,00)
    }

    if(total_belanja > 1000000) {
        diskonHarga = 0.3; // 30% (Rp1.000.001+)
    }

    //penghitungan diskonTransaksi
    if(jml_transaksi >= 4) {
        diskonTransaksi = 0.2; // 20% (>= 4 transaksi)
    } else {
        diskonTransaksi = 0; // 0% (< 4 transaksi)
    }

    total_akhir *= (1 - diskonHarga);
    total_akhir *= (1 - diskonTransaksi);

    printf("-----------------------------------------------------------\n");
    printf("Total harga belanja keseluruhan    : Rp%.0f,00\n", (float) total_belanja);
    printf("Diskon 1\t\t\t   : %0.f%%\n", diskonHarga * 100);
    printf("Diskon 2 (%d/4 transaksi dilakukan) : %.0f%%\n", jml_transaksi, diskonTransaksi * 100);
    printf("Harga belanja akhir setelah diskon : Rp%.0f,00\n", total_akhir);
    printf("Anda menghemat                     : Rp%.0f,00\n\n", (float) total_belanja - total_akhir);

    printf("Semoga hari Anda menyenangkan!\n");
    exit(0);
}

int belanja() {
    //total_belanja_buffer = nilai total belanja yang dimasukkan oleh user
    //total_belanja_kini = nilai total belanja sejauh ini
    //counter_pembelanjaan = counter untuk jumlah pembelanjaan
    //pilihan_lanjut = pilihan user untuk belanja atau tidak (y/n)
    //free = variabel yang saya tetapkan untuk membuat semacam statement pass; seperti di bahasa lain
    int total_belanja_buffer;
    int total_belanja_kini;
    int counter_pembelanjaan;
    char pilihan_lanjut;
    int pass;

    fflush(stdin);
    //printf untuk menanyakan apakah user ingin lanjut pembelanjaan atau tidak. Ditampilkan mulai setelah pembelanjaan pertama.
    if(counter_pembelanjaan > 0) {
        printf("Apakah Anda ingin melakukan pembelanjaan lagi? (Y/N): ");
        //gagal jika input tidak ter-scan dan tidak berupa y atau n
        if(scanf("%c", &pilihan_lanjut) == 0) {
            printf("Maaf, pilihan yang Anda masukkan invalid.\n\n");
            return 0;
        }

        switch(pilihan_lanjut) {
            case 'y':
            case 'Y':
            pass = 0;
            break;

            case 'n':
            case 'N':
            akhir_dan_diskon(counter_pembelanjaan, total_belanja_kini);
            break;
            
            default:
            printf("Maaf, pilihan yang Anda masukkan invalid.\n\n");
            return 0;
        }
    }

    printf("Masukkan nilai total belanja (rupiah, angka bulat. Masukkan 0 untuk mengakhiri pembelanjaan): ");

    if(scanf("%d", &total_belanja_buffer) == 0) {
        printf("Maaf, nilai yang Anda masukkan invalid.\n");
        return 0;
    }

    if(total_belanja_buffer == 0) {
        akhir_dan_diskon(counter_pembelanjaan, total_belanja_kini);
        return 0;
    } 

    total_belanja_kini += total_belanja_buffer;
    counter_pembelanjaan++;
    printf("Jumlah pembelanjaan kini: %d\n", counter_pembelanjaan);
    printf("Harga pembelanjaan kini: Rp%d,00\n\n", total_belanja_kini);
}

int main() {
    printf("----------------------------------------\n");
    printf("PROGRAM PENGHITUNG PEMBELANJAAN\n");
    printf("----------------------------------------\n");

    while(1 == 1) {
        belanja();
    }
    return 0;
}

