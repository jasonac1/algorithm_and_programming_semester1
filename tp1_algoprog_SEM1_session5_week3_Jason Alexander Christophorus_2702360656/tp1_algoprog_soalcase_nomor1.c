#include <stdio.h>
void konversi_jarak() {
    float x_km;
    printf("Masukkan jarak dalam kilometer (cukup angka saja, untuk koma menggunakan .): ");
    if(scanf("%f", &x_km) == 1) {
        float x_m = x_km * 1000;
        float x_cm = x_m * 100;
        printf("%.3f km = %.0f m = %.0f cm\n\n", x_km, x_m, x_cm);
    } else {
        printf("Maaf, input Anda invalid (tidak berupa angka).\n\n");
        fflush(stdin);
    }

}

int main() {
    // x = jarak dalam km
    while(1) {
        konversi_jarak();
    }

    return 0;
}
