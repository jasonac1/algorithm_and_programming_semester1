#include <stdio.h>
#include <string.h>
int main() {
    //penginputan 3 kalimat:
    char kalimat1[100];
    char kalimat2[100];
    char kalimat3[100];
    char gabungan[300];
    printf("Input:\n");
    printf("Kalimat 1 = ");
    fgets(kalimat1, 100, stdin);
    kalimat1[strlen(kalimat1) - 1] = '\0'; // it should be ''. "" treats the characters inside as a string.

    printf("Kalimat 2 = ");
    fgets(kalimat2, 100, stdin);
    kalimat2[strlen(kalimat2) - 1] = '\0';

    printf("Kalimat 3 = ");
    fgets(kalimat3, 100, stdin);
    kalimat3[strlen(kalimat3) - 1] = '\0';
    
    strcpy(gabungan, kalimat1);
    strcat(gabungan, " ");
    strcat(gabungan, kalimat2);
    strcat(gabungan, " ");
    strcat(gabungan, kalimat3);

    int i;
    char alphabetFilter[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int jumlahHurufKalimat1 = 0;
    int jumlahHurufKalimat2 = 0;
    int jumlahHurufKalimat3 = 0;

    //mencari jumlah huruf masing-masing kalimat:
    for(i = 0; i < strlen(kalimat1); i++) {
        //filter (mengabaikan space & special character)
        if(strchr(alphabetFilter, kalimat1[i]) != NULL) {
            jumlahHurufKalimat1++;
        }
    }

    for(i = 0; i < strlen(kalimat2); i++) {
        if(strchr(alphabetFilter, kalimat2[i]) != NULL) {
            jumlahHurufKalimat2++;
        }
    }

    for(i = 0; i < strlen(kalimat3); i++) {
        if(strchr(alphabetFilter, kalimat3[i]) != NULL) {
            jumlahHurufKalimat3++;
        }
    }

    //output
    printf("\n");
    printf("Gabungan 3 buah inputan kalimat = %s\n\n", gabungan);
    printf("Hasil membalik kalimat gabungan = %s\n\n", strrev(gabungan));
    printf("Jumlah huruf kalimat pertama = %d\n", jumlahHurufKalimat1);
    printf("Jumlah huruf kalimat kedua = %d\n", jumlahHurufKalimat2);
    printf("Jumlah huruf kalimat ketiga = %d\n", jumlahHurufKalimat3);
    printf("Total jumlah huruf = %d", jumlahHurufKalimat1 + jumlahHurufKalimat2 + jumlahHurufKalimat3);
    return 0;
}