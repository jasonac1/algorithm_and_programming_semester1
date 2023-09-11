#include <stdio.h>
#include <string.h>
int main() {
    const int jumlahMahasiswa = 100;
    char nama[100];
    int hasil;
    char listNama[jumlahMahasiswa][100]; //[jumlah mahasiswa][panjang string]
    int listHasil[jumlahMahasiswa];
    int lulus = 0;
    int gagal = 0;
    int i;

    //mendata semua mahasiswa dan hasil ujian
    printf("Berikut adalah data mahasiswa dan hasil ujian yang Anda harus masukkan: (1 = lulus, 2 = gagal)\n");
    for(i = 0; i < jumlahMahasiswa; i++) {
        printf("%d. Nama: ", i+1);
        scanf("%s", nama);
        printf("Masukkan hasil: ");
        scanf("%d", &hasil);
        printf("\n");
        strcpy(listNama[i], nama);
        listHasil[i] = hasil;
    } 
    
    //memprint semua data
    for(i = 0; i < jumlahMahasiswa; i++) {
        printf("%d. %s: ", i+1, listNama[i]);
        if(listHasil[i] == 1) {
            printf("Lulus\n");
            lulus++;
        } else if (listHasil[i] == 2) {
            printf("Gagal\n");
            gagal++;
        } else {
            printf("STATUS INVALID / Tidak ada data\n");
        }
    }

    //memprint statistik lulus-gagal
    printf("Jumlah mahasiswa yang lulus: %d\n", lulus);
    printf("Jumlah mahasiswa yang gagal: %d\n", gagal);
    float persentaseKelulusan = (float) lulus * 100 / jumlahMahasiswa;
    if((float) lulus / jumlahMahasiswa >= 0.8) {
        printf("Kelulusan kelas telah mencapai target! (%.2f%% (kelulusan) >= 80% (minimal))", persentaseKelulusan);
    } else {
        printf("Kelulusan kelas belum mencapai target! (%.2f%% (kelulusan) < 80% (minimal))", persentaseKelulusan);
    }

    return 0;
}