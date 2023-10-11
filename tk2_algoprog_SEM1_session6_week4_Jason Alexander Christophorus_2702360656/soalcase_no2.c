#include <stdio.h>

void clear_stdin() {
    char c;
    while(c = getchar() != '\n' && c != EOF);
}

void invalid() {
    printf("\033[0;31mMaaf, Anda telah memasukkan input invalid atau di luar range (0-100). Mohon diinput lagi.\n\n\033[0;0m");
    clear_stdin();
}

char jadikanGrade(float nilai) {
    if(nilai <= 55) {
        return 'E';
    } else if(nilai <= 65) {
        return 'D';
    } else if(nilai <= 75) {
        return 'C';
    } else if(nilai <= 85) {
        return 'B';
    } else if(nilai <= 100) {
        return 'A';
    }
}

int main() {
    int bufferSize = 100;
    struct Data {
        int noUrut;
        char nama[bufferSize];
        float nilaiKuis;
        float nilaiTugas;
        float nilaiAbsensi;
        float nilaiPraktek;
        float nilaiUAS;
        float nilaiRataRata;
    } d[50];

    //variabel yg diperlukan
    int jumlahMahasiswa = 0;
    float kuis;
    float tugas;
    float absensi;
    float praktek;
    float UAS;
    float rata_rata;
    while(1) {
        printf("Masukkan jumlah mahasiswa yang akan didata: ");
        if(scanf("%d", &jumlahMahasiswa) != 1) {
            printf("Nilai invalid!\n\n");
            clear_stdin();
            continue;
        }

        if(jumlahMahasiswa < 10 || jumlahMahasiswa > 50) {
            printf("Maaf, jumlah mahasiswa yang didata minimal 10 orang dan maksimal 50 orang.\n\n");
            clear_stdin();
            continue;
        } else {
            clear_stdin();
            break;
        }
    }

    int i = 0;
    while(i < jumlahMahasiswa) { 
        d[i].noUrut = i+1;
        printf("%d.\n", i+1);
        printf("Masukkan nama mahasiswa        : ");
        scanf("%s", d[i].nama);
        printf("Masukkan nilai kuis (0-100)    : ");
        if(scanf("%f", &d[i].nilaiKuis) != 1 || d[i].nilaiKuis < 0 || d[i].nilaiKuis > 100) {
            invalid();
            continue;
        }
        printf("Masukkan nilai tugas (0-100)   : ");
        if(scanf("%f", &d[i].nilaiTugas) != 1 || d[i].nilaiTugas < 0 || d[i].nilaiTugas > 100) {
            invalid();
            continue;
        }
        printf("Masukkan nilai absensi (0-100) : ");
        if(scanf("%f", &d[i].nilaiAbsensi) != 1 || d[i].nilaiAbsensi < 0 || d[i].nilaiAbsensi > 100) {
            invalid();
            continue;
        }

        printf("Masukkan nilai praktek (0-100) : ");
        if(scanf("%f", &d[i].nilaiPraktek) != 1 || d[i].nilaiPraktek < 0 || d[i].nilaiPraktek > 100) {
            invalid();
            continue;
        }

        printf("Masukkan nilai UAS (0-100)     : ");
        if(scanf("%f", &d[i].nilaiUAS) != 1 || d[i].nilaiUAS < 0 || d[i].nilaiUAS > 100) {
            invalid();
            continue;
        }

        d[i].nilaiRataRata = (float) (d[i].nilaiKuis + d[i].nilaiTugas + d[i].nilaiAbsensi + d[i].nilaiPraktek + d[i].nilaiUAS) / 5;
        printf("\n");
        i++;
    }

    for(int j = 0; j < jumlahMahasiswa; j++) {
        kuis = d[j].nilaiKuis;
        tugas = d[j].nilaiTugas;
        absensi = d[j].nilaiAbsensi;
        praktek = d[j].nilaiPraktek;
        UAS = d[j].nilaiUAS;
        rata_rata = d[j].nilaiRataRata;
        printf("%d.\n", d[j].noUrut);
        printf("Nama mahasiswa                 : %s\n", d[j].nama);
        printf("Nilai kuis                     : %.2f -> %c\n", kuis, jadikanGrade(kuis));
        printf("Nilai tugas                    : %.2f -> %c\n", tugas, jadikanGrade(tugas));
        printf("Nilai absensi                  : %.2f -> %c\n", absensi, jadikanGrade(absensi));
        printf("Nilai praktek                  : %.2f -> %c\n", praktek, jadikanGrade(praktek));
        printf("Nilai UAS                      : %.2f -> %c\n", UAS, jadikanGrade(UAS));
        printf("Nilai rata-rata                : \033[0;33m%.2f -> %c\n\033[0;0m", rata_rata, jadikanGrade(rata_rata));
        printf("Lulus?                         : ");
        if(jadikanGrade(rata_rata) == 'D' || jadikanGrade(rata_rata) == 'E') {
            printf("\033[0;31mTidak\n\033[0;0m");
        } else {
            printf("\033[0;32mYa\n\033[0;0m");
        }
        printf("\n");
    }
    printf("Press enter to exit program.");
    clear_stdin();
    char c;
    if(c = getc(stdin)) {
        return 0;
    }
    return 0;
}