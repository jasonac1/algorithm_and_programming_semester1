#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define YELLOW "\033[0;33m"
#define RED  "\033[0;31m"
#define RESET "\033[0;0m"
#define SIZE_NAMABUKU 100
#define SIZE_JENISBUKU 30
#define SIZE_TGLTRANSAKSI 100
typedef struct DataBuku {
    int kodeBuku;
    char namaBuku[SIZE_NAMABUKU];
    char jenisBuku[SIZE_JENISBUKU];
    int harga;
    int stok; // diimplikasikan oleh adanya transaksi / history penjualan
} Buku;

typedef struct DataTransaksi {
    int id;
    int kodeBuku;
    char namaBuku[SIZE_NAMABUKU];
    char tanggalTransaksi[SIZE_TGLTRANSAKSI];
    int jumlahPembayaran;
} Transaksi;

//function mengambil data
char* bacaData(FILE* fp); // membaca data dari file dan mengembalikannya sebagai string
char** bagiData(char* str, int* jmlSubstring); // membagi data per baris menjadi substring
Buku* buatStructDataBuku(char** substrings, int jmlSubstring, int* jmlDataBuku); // memasukkan data ke dalam struct menggunakan malloc karena di runtime
Transaksi* buatStructDataTransaksi(char** substrings, int jmlSubstring, int* jmlTransaksi);
char* ambilData(char* str); // mengambil data yang berformat [nama]: [data]

//function display
void displayMenu(void); //mendisplay menu yang ada
void clearstdin(void); //mengclear stdin
void displayMenuPilihan(char pilihan, Buku* data, int* jmlDataBuku, Transaksi* dtTransaksi, int *jmlDataTransaksi); //mendisplay menu yang diplih, serta memasukkan data struct buku
void nullTerminate(char* str); //mengakhiri string input dari fgets dengan '\0'

//function masing-masing menu (menu exit juga mensave data ke file)
void a_menuInput(Buku* data, int* jmlDataBuku);
void b_menuViewHistory(Transaksi* dtTransaksi, int jmlDataTransaksi);
void c_menuViewBuku(Buku* data, int jmlDataBuku);
void* d_menuDeleteHistory(Transaksi* dtTransaksi, int* jmlDataTransaksi);
void e_menuDeleteBuku(Buku* data, int *jmlDataBuku);
void f_menuExit(Buku* data, int jmlDataBuku, Transaksi* dtTransaksi, int jmlDataTransaksi);

void invalidInput(const char* str); //mendisplay message error invalid input

//function insert & update data
void* insertDataBuku(Buku* data, int* jmlDataKini, int kode, char* nama, char* jenis, int harga, int stok); // insert data ke dalam daftar data buku, dan mengupdate jumlah data buku
void* hapusDataTransaksi(Transaksi* dtTransaksi, int* jmlDataTransaksi, int delIndex);
void* hapusDataBuku(Buku* data, int* jmlDataBuku, int delIndex);
void saveFile(Buku* data, int jmlDataBuku, Transaksi* dtTransaksi, int jmlDataTransaksi);

int main() { 
    //--- Ambil data buku
    FILE* file_databuku = fopen("databuku.txt", "r+");
    //return error jika tidak berhasil
    if(file_databuku == NULL) { 
        printf("Maaf, file tidak dapat dibuka.\n");
        return -1;
    }

    char* stringData = bacaData(file_databuku); //memasukkan data buku ke dalam string

    int jumlahSubstring = 0;
    char** arraySubstringData = bagiData(stringData, &jumlahSubstring); //kemudian membagi string tersebut per data, dan meng-increment jumlah substring

    int jumlahDataBuku = 0;
    Buku* daftarDataBuku = buatStructDataBuku(arraySubstringData, jumlahSubstring, &jumlahDataBuku);
    
    //--- Ambil data transaksi
    FILE* file_datatransaksi = fopen("datatransaksi.txt", "r+");
    if(file_datatransaksi == NULL) {
        printf("Maaf, file tidak dapat dibuka.\n");
        return -1;
    }

    char* stringTransaksi = bacaData(file_datatransaksi);

    int jumlahSubstringTransaksi;
    char** arraySubstringTransaksi = bagiData(stringTransaksi, &jumlahSubstringTransaksi);

    int jumlahDataTransaksi = 0;
    Transaksi* daftarDataTransaksi = buatStructDataTransaksi(arraySubstringTransaksi, jumlahSubstringTransaksi, &jumlahDataTransaksi);

    //--- Minta input
    while(1) {
        /*for(j = 0; j < jumlahDataTransaksi; j++) { 
            printf("%d, ", daftarDataTransaksi[j].id);
            printf("%d, ", daftarDataTransaksi[j].kodeBuku);
            printf("%s, ", daftarDataTransaksi[j].namaBuku);
            printf("%s, ", daftarDataTransaksi[j].tanggalTransaksi);
            printf("%d\n", daftarDataTransaksi[j].jumlahPembayaran);
        }*/

        char pilihan;
        printf("------------\nMENU\n------------\n");
        displayMenu();
        scanf("%c", &pilihan);
        displayMenuPilihan(pilihan, daftarDataBuku, &jumlahDataBuku, daftarDataTransaksi, &jumlahDataTransaksi);
        printf("\n");
        clearstdin();
    }
    
    //--- dealokasi memori + closing file
    free(stringData);
    int i;
    for(i = 0; i < jumlahSubstring; i++) {
        free(arraySubstringData[i]);
    }
    free(arraySubstringData);

    free(stringTransaksi);
    int j;
    for(j = 0; j < jumlahSubstringTransaksi; j++) {
        free(arraySubstringTransaksi[j]);
    }
    free(arraySubstringTransaksi);
    fclose(file_databuku);
    getchar();
    return 0;
}

char* bacaData(FILE* fp) {
    //Membaca file ke dalam string.
    int sizeDariString = 1;
    int index = 0;
    //dynamic string
    char* stringData = (char*)malloc(sizeDariString * sizeof(char));
    if(stringData == NULL) { 
        printf("Alokasi memori gagal.\n");
        return '\0';
    }

    char c;
    do { 
        c = fgetc(fp);
        if(feof(fp)) break;
        
        stringData[index++] = c;
        //menambah size string, kemudian menambahkan character ke string dan meng-increment indexnya
        stringData = (char*)realloc(stringData, ++sizeDariString); // alokasikan 2 space untuk iterasi pertama (character + '\0')
        if(stringData == NULL) {
            printf("Alokasi memori gagal.\n");
            return '\0';
        }
        stringData[index] = '\0'; // terminate string dengan '\0'
    } while(1);

    return stringData;
}

//pass by reference integer untuk mendapatkan jumlah substring di function main
char** bagiData(char* str, int* jmlSubstring) {
    int jumlahSubstring = 0;
    //dynamic array, memisahkan string penuh dengan karakter '\n'
    char** substringData = (char**)malloc(sizeof(char*)); // buat array substring
    if(substringData == NULL) {
        printf("Alokasi memori gagal.\n");
        return NULL;
    }

    char* token = strtok(str, "\n");
    int panjangToken;
    //loop untuk setiap token dipisahkan dengan karakter '\n'
    //kemudian, memasukkan tiap token ke dalam array substrings

    while(token != NULL) {
        panjangToken = strlen(token);
        substringData = (char**)realloc(substringData, (jumlahSubstring + 1) * sizeof(char*));
        if(substringData == NULL) {
            printf("Alokasi memori gagal.\n");
            return NULL;
        }

        substringData[jumlahSubstring] = (char*)malloc((panjangToken + 1) * sizeof(char));
        if(substringData[jumlahSubstring] == NULL) {
            printf("Alokasi memori gagal.\n");
            return NULL;
        }
        
        strcpy(substringData[jumlahSubstring++], token);
        token = strtok(NULL, "\n");
    }
    *jmlSubstring = jumlahSubstring;
    return substringData;
}

//pass by reference juga untuk mendapatkan jumlah data buku di function main
Buku* buatStructDataBuku(char** substrings, int jmlSubstring, int* jmlDataBuku) {
    Buku* outputData = (Buku*)malloc(jmlSubstring * sizeof(Buku));
    if(outputData == NULL) {
        printf("Alokasi memori gagal.\n");
        return NULL;
    }
    
    //loop semua substring dalam cycle 5 (karena ada 5 data) dan memasukkannya sebagai data baru
    int structIndex;
    int i;
    int cycle = 5;
    for(i = 0, structIndex = 0; i < jmlSubstring; i+=cycle, structIndex++) {
        //ambil data dari format [nama]: [data] dengan mensplit karakter titik dua (:) 
        outputData[structIndex].kodeBuku = atoi(ambilData(substrings[i]));
        strcpy(outputData[structIndex].namaBuku, ambilData(substrings[i+1]));
        strcpy(outputData[structIndex].jenisBuku, ambilData(substrings[i+2]));
        outputData[structIndex].harga = atoi(ambilData(substrings[i+3]));
        outputData[structIndex].stok = atoi(ambilData(substrings[i+4]));

        // harga dan stok dikonversi dari string menjadi integer.
    }
    *jmlDataBuku = structIndex;
    outputData = (Buku*)realloc(outputData, (*jmlDataBuku)*sizeof(Buku)); //realokasi untuk jumlah data
    return outputData;
}

Transaksi* buatStructDataTransaksi(char** substrings, int jmlSubstring, int* jmlDataTransaksi) {
    Transaksi* outputData = (Transaksi*)malloc(jmlSubstring* sizeof(Transaksi));
    if(outputData == NULL) {
        printf("Alokasi memori gagal.\n");
        return NULL;
    }

    //loop substring dalam cycle 5 (5 data) untuk dimasukkan ke struct transaksi (sama seperti membuat struct buku)
    int structIndex;
    int i;
    int cycle = 5;
    for(i = 0, structIndex = 0; i < jmlSubstring; i += cycle, structIndex++) {
        outputData[structIndex].id = atoi(ambilData(substrings[i]));
        outputData[structIndex].kodeBuku = atoi(ambilData(substrings[i+1]));
        strcpy(outputData[structIndex].namaBuku, ambilData(substrings[i+2]));
        strcpy(outputData[structIndex].tanggalTransaksi, ambilData(substrings[i+3]));
        outputData[structIndex].jumlahPembayaran = atoi(ambilData(substrings[i+4]));
    }
    *jmlDataTransaksi = structIndex;
    outputData = (Transaksi*)realloc(outputData, (*jmlDataTransaksi)*sizeof(Transaksi));
    return outputData;
}

char* ambilData(char* str) {
    const char* delimiter = ":";
    char* namaData;
    char* isiData;
    namaData = strtok(str, delimiter);
    isiData = strtok(NULL, delimiter);
        while(*isiData == ' ') {
            isiData++;
        }
    return isiData;
}

void displayMenu(void) {
    printf("%sCatatan: Setiap data yang Anda input atau hapus akan tersimpan pada program secara lokal saja. Perubahan yang dilakukan akan tersimpan ke file jika Anda memilih menu exit.\n%s", YELLOW, RESET);
    printf("a. Input (1)\n");
    printf("b. View History (2)\n");
    printf("c. View Buku (3)\n");
    printf("d. Delete History (4)\n");
    printf("e. Delete Buku (5)\n");
    printf("f. Exit (6)\n");
    printf("Pilih menu: ");
}

void nullTerminate(char* str) {
    int i = 0;
    while(1) {
        if(str[i] == '\n') {
            str[i] = '\0';
            break;
        }
        i++;
    }
}

void clearstdin(void) {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void displayMenuPilihan(char pilihan, Buku* data, int* jmlDataBuku, Transaksi* dtTransaksi, int *jmlDataTransaksi) {
    switch(pilihan) {
        case '1':
            a_menuInput(data, jmlDataBuku);
            break;

        case '2':
            printf("\n-----------------------------------\n%sHISTORY PENJUALAN / TRANSAKSI%s\n-----------------------------------\n", YELLOW, RESET);
            b_menuViewHistory(dtTransaksi, *jmlDataTransaksi);
            break;

        case '3':
            c_menuViewBuku(data, *jmlDataBuku);
            break;

        case '4':
            d_menuDeleteHistory(dtTransaksi, jmlDataTransaksi);
            break;

        case '5':
            e_menuDeleteBuku(data, jmlDataBuku);
            break;

        case '6':
            f_menuExit(data, *jmlDataBuku, dtTransaksi, *jmlDataTransaksi);
            exit(0);
            break;

        default:
            invalidInput("Mohon masukkan salah satu angka menu pilihan.\n");
            break;
    }
}

void a_menuInput(Buku* data, int* jmlDataBuku) {
    printf("\n--------------\n%sINPUT DATA BUKU%s\n--------------\n", YELLOW, RESET);
    int kodeBukuBerikutnya = (data[*(jmlDataBuku)-1].kodeBuku)+1;
    char namaBukuBerikutnya[SIZE_NAMABUKU];
    char jenisBukuBerikutnya[SIZE_JENISBUKU];
    int hargaBukuBerikutnya = 0;
    int stokBukuBerikutnya = 0;
    int intCheck = 0; // variabel untuk memeriksa apakah input integer atau bukan, menggunakan nilai return scanf
    char konfirmasi = '0'; // pilihan konfirmasi input data
    char konfirmasiLanjut = '0'; // pilihan konfirmasi untuk lanjut input data

    clearstdin();
    while(1) {
        printf("Kode Buku: %d\n", kodeBukuBerikutnya);
        printf("Nama Buku: ");
        fgets(namaBukuBerikutnya, SIZE_NAMABUKU, stdin);
        nullTerminate(namaBukuBerikutnya);
        
        printf("Jenis Buku: ");
        fgets(jenisBukuBerikutnya, SIZE_JENISBUKU, stdin);
        nullTerminate(jenisBukuBerikutnya);

        printf("Harga: ");
        intCheck = scanf("%d", &hargaBukuBerikutnya);
        if(intCheck == 0) {
            invalidInput("Mohon masukkan harga integer.\n\n");
            clearstdin();
            continue;
        }

        printf("Stok: ");
        intCheck = scanf("%d", &stokBukuBerikutnya);
        if(intCheck == 0) {
            invalidInput("Mohon masukkan harga integer.\n\n");
            clearstdin();
            continue;
        }

        clearstdin();
        //loop untuk mengambil konfirmasi input data
        while(1) {
            //jika input y maka break dari while loop ini, dan break dari while loop paling luar, selesai.
            //jika input n maka akan masuk ke while loop konfirmasi lanjut.
            //jika input invalid maka akan looping terus dalam while loop ini sampai valid.
            printf("Apakah data input sudah benar? (Y/N): ");
            scanf("%c", &konfirmasi);
            if(konfirmasi == 'y' || konfirmasi == 'Y') {
                insertDataBuku(data, jmlDataBuku, kodeBukuBerikutnya, namaBukuBerikutnya, jenisBukuBerikutnya, hargaBukuBerikutnya, stokBukuBerikutnya);
                (*jmlDataBuku)++;
                printf("Input telah dimasukkan ke dalam daftar data buku.\n");
                konfirmasiLanjut = 'n'; // untuk memastikan flow kembali ke menu
                break;
            } else if(konfirmasi == 'n' || konfirmasi == 'N') {
                clearstdin();
                printf("Apakah Anda ingin melanjutkan input data? (Y/N): ");
                //konfirmasi lagi jika ingin menambah lagi
                while(1) {
                    scanf("%c", &konfirmasiLanjut);
                    //input invalid maka akan terus looping
                    if(konfirmasiLanjut != 'y' && konfirmasiLanjut != 'Y' && konfirmasiLanjut != 'n' && konfirmasiLanjut != 'N') {
                        invalidInput("Mohon masukkan pilihan Y / N saja.\n\n");
                        clearstdin();
                        continue;
                    }
                    //jika input valid maka break dari loop while ini, dan menjalankan sesuai konfirmasi di luar loop
                    break;
                }
                //break, konfirmasi lanjut di luar loop while luar
                break;
            } else {
                invalidInput("Mohon masukkan pilihan Y / N saja.\n\n");
                clearstdin();
                continue;
            }
        }

        //konfirmasi lanjut di sini
        if(konfirmasiLanjut == 'y' || konfirmasiLanjut == 'Y') {
            clearstdin();
            printf("\n");
            continue; //jika konfirmasi lanjut, maka input ulang
        } else if((konfirmasiLanjut == 'n' || konfirmasiLanjut == 'N') || (konfirmasi == 'y' || konfirmasi == 'Y')) {
            printf("%sMembuka menu...\n%s", YELLOW, RESET);
            break; //1. konfirmasi pertama sudah benar atau 2. konfirmasi tidak lanjut memasukkan data, kembali ke menu.
        }
    }
}

void b_menuViewHistory(Transaksi* dtTransaksi, int jmlDataTransaksi) {
    int i;
    for(i = 0; i < jmlDataTransaksi; i++) {
        printf("ID Transaksi: %d\n", dtTransaksi[i].id);
        printf("Kode Buku: %d\n", dtTransaksi[i].kodeBuku);
        printf("Nama Buku: %s\n", dtTransaksi[i].namaBuku);
        printf("Tanggal Transaksi: %s\n", dtTransaksi[i].tanggalTransaksi);
        printf("Jumlah pembayaran: %d\n", dtTransaksi[i].jumlahPembayaran);
        printf("\n");
    }
}

void c_menuViewBuku(Buku* data, int jmlDataBuku) {
    printf("\n-------------------\n%sDAFTAR DATA BUKU%s\n-------------------\n", YELLOW, RESET);
    //printf("Jumlah data buku = %d\n", jmlDataBuku);
    int i;
    for(i = 0; i < jmlDataBuku; i++) {
        printf("Kode Buku: %d\n", data[i].kodeBuku);
        printf("Nama Buku: %s\n", data[i].namaBuku);
        printf("Jenis Buku: %s\n", data[i].jenisBuku);
        printf("Harga: %d\n", data[i].harga);
        printf("Stok: %d\n", data[i].stok);
        printf("\n");
    }
}

void* d_menuDeleteHistory(Transaksi* dtTransaksi, int* jmlDataTransaksi) { 
    printf("\n-----------------------------------\n%sDELETE HISTORY PENJUALAN / TRANSAKSI%s\n-----------------------------------\n", YELLOW, RESET);
    b_menuViewHistory(dtTransaksi, *jmlDataTransaksi);
    int index = 0;
    char pilihan = '0';
    //looping input
    //jumlah item == 0: pass
    if(*jmlDataTransaksi == 0) {
        printf("Data tidak ditemukan.\n");
        return NULL;
    }

    while(1) {
        printf("Input index data penjualan / transaksi yang akan dihapus (index dimulai dari 1): ");
        if(scanf("%d", &index) != 1) {
            invalidInput("Mohon masukkan index integer.\n\n");
            clearstdin();
            continue;
        }

        if(index < 1 || index > *jmlDataTransaksi) {
            invalidInput("Mohon masukkan index diantara 1-index terakhir\n\n");
            continue;
        }

        clearstdin();

        //loop konfirmasi sampai dapat input yang benar
        while(1) {
            printf("Apakah Anda ingin menghapus data tersebut? (Y/N): ");
            scanf("%c", &pilihan);
            //akan terus looping jika dapat input invalid
            if(pilihan != 'Y' && pilihan != 'y' && pilihan != 'N' && pilihan != 'n') {
                invalidInput("Mohon masukkan pilihan Y / N saja.\n\n");
                clearstdin();
                continue;
            }
            //break jika input valid
            break;
        }

        //jika yes maka data dihapus dan kembali ke menu, jika no maka kembali ke menu saja.
        if(pilihan == 'Y' || pilihan == 'y') {
            hapusDataTransaksi(dtTransaksi, jmlDataTransaksi, index);
            printf("Data successfully deleted (Data berhasil dihapus).\n");
        }

        if(pilihan == 'N' || pilihan == 'n') {
            ;
        }
        printf("%sMembuka menu...\n%s", YELLOW, RESET);
        break;
    } 
}

void e_menuDeleteBuku(Buku* data, int *jmlDataBuku) {
    printf("\n-----------------------\n%sDELETE BUKU%s\n-----------------------\n", YELLOW, RESET);
    c_menuViewBuku(data, *jmlDataBuku);
    int index = 0;
    char pilihan = '0';
    //looping input
    while(1) {
        printf("Input index data buku yang akan dihapus (index dimulai dari 1): ");
        if(scanf("%d", &index) != 1) {
            invalidInput("Mohon masukkan input integer.\n\n");
            clearstdin();
            continue;
        }

        if(index < 1 || index > *jmlDataBuku) {
            invalidInput("Mohon masukkan index diantara 1-index terakhir\n\n");
            continue;
        }

        clearstdin();

        //loop konfirmasi sampai dapat input valid
        while(1) { 
            printf("Apakah Anda ingin menghapus data tersebut? (Y/N): ");
            scanf("%c", &pilihan);
            if(pilihan != 'Y' && pilihan != 'y' && pilihan != 'N' && pilihan != 'n') {
                invalidInput("Mohon masukkan pilihan Y / N saja.\n\n");
                clearstdin();
                continue;
            }
            break;
        }

        if(pilihan == 'Y' || pilihan == 'y') {
            hapusDataBuku(data, jmlDataBuku, index);
            printf("Data successfully deleted (Data berhasil dihapus).\n");
        }

        if(pilihan == 'N' || pilihan == 'n') { 
            ;
        }
        printf("%sMembuka menu...\n%s", YELLOW, RESET);
        break;
    }
}

void f_menuExit(Buku* data, int jmlDataBuku, Transaksi* dtTransaksi, int jmlDataTransaksi) {
    saveFile(data, jmlDataBuku, dtTransaksi, jmlDataTransaksi);
}


void invalidInput(const char* str) {
    printf("%sMaaf, input Anda invalid. %s%s", RED, str, RESET);
}

void* insertDataBuku(Buku* data, int *jmlDataKini, int kode, char* nama, char* jenis, int harga, int stok) {
    data[*jmlDataKini].kodeBuku = kode;
    strcpy(data[*jmlDataKini].namaBuku, nama);
    strcpy(data[*jmlDataKini].jenisBuku, jenis);
    data[*jmlDataKini].harga = harga;
    data[*jmlDataKini].stok = stok;
}

void* hapusDataTransaksi(Transaksi* dtTransaksi, int* jmlDataTransaksi, int delIndex) {
    //delIndex dimulai dari 1 jadi sudah diperhitungkan. Misal yg dihapus delIndex 1 (index 0 di struct), berarti index item di struct yang bergerak dimulai dari 1 dan seterusnya (bukan 0), jadi dapat menggunakan delIndex langsung
    int moveIndex = -1; // untuk memperjelas maka membuat variabel baru bernama moveIndex. Defaultnya -1 supaya menghandle jika yang dihapus item terakhir (tidak bergerak)

    //n == 1: handle case jika jmlDataTransaksi tinggal 1, berarti tinggal set semua valuenya kosong, nanti di function updateData akan terdeteksi kosong dan menulis nihil pada file.
    if(*jmlDataTransaksi == 1) {
        //semua elemen diset ke value default / kosong
        dtTransaksi[0].id = -1;
        dtTransaksi[0].kodeBuku = -1;
        strcpy(dtTransaksi[0].namaBuku, "");
        strcpy(dtTransaksi[0].tanggalTransaksi, "");
        dtTransaksi[0].jumlahPembayaran = -1;
        dtTransaksi = (Transaksi*)realloc(dtTransaksi, 1); // secara praktis memuat 0 item. Dibuat 1 supaya pointer tidak NULL.
        if(dtTransaksi == NULL) {
            printf("Alokasi memori gagal.\n");
            return NULL;
        }
        *jmlDataTransaksi -= 1;
        return NULL;
    }

    //n > 1: logic: untuk index yang dihapus, maka semua data setelahnya akan bergerak mundur 1 index menempatinya. Kemudian, array akan di-realloc
    for(moveIndex = delIndex; moveIndex < *jmlDataTransaksi; moveIndex++) {
        //semua item sebelumnya di set value item kini
        dtTransaksi[moveIndex-1].id = dtTransaksi[moveIndex].id; 
        dtTransaksi[moveIndex-1].kodeBuku = dtTransaksi[moveIndex].kodeBuku;
        strcpy(dtTransaksi[moveIndex-1].namaBuku, dtTransaksi[moveIndex].namaBuku);
        strcpy(dtTransaksi[moveIndex-1].tanggalTransaksi, dtTransaksi[moveIndex].tanggalTransaksi);
        dtTransaksi[moveIndex-1].jumlahPembayaran = dtTransaksi[moveIndex].jumlahPembayaran;
    }

    //kemudian, kurangi jumlah data transaksi, dan realloc untuk menyesuaikan ukuran array.
    *jmlDataTransaksi -= 1;
    dtTransaksi = (Transaksi*)realloc(dtTransaksi, (*jmlDataTransaksi)*sizeof(Transaksi));
    if(dtTransaksi == NULL) {
        printf("Alokasi memori gagal.\n");
        return NULL;
    }
}

void* hapusDataBuku(Buku* data, int* jmlDataBuku, int delIndex) {
    //hampir sama seperti hapusDataTransaksi
    int moveIndex = -1;

    //n == 1
    if(*jmlDataBuku == 1) {
        data[0].kodeBuku = -1;
        strcpy(data[0].namaBuku, "");
        strcpy(data[0].jenisBuku, "");
        data[0].harga = -1;
        data[0].stok = -1;
        data = (Buku*)realloc(data, 1);
        if(data == NULL) {
            printf("Alokasi memori gagal.\n");
            return NULL;
        }
        *jmlDataBuku -= 1;
        return NULL;
    }
    
    //n > 1
    for(moveIndex = delIndex; moveIndex < *jmlDataBuku; moveIndex++) {
        data[moveIndex-1].kodeBuku = data[moveIndex].kodeBuku;
        strcpy(data[moveIndex-1].namaBuku, data[moveIndex].namaBuku);
        strcpy(data[moveIndex-1].jenisBuku, data[moveIndex].jenisBuku);
        data[moveIndex-1].harga = data[moveIndex].harga;
        data[moveIndex-1].stok = data[moveIndex].stok;
    }

    *jmlDataBuku -= 1;
}

void saveFile(Buku* data, int jmlDataBuku, Transaksi* dtTransaksi, int jmlDataTransaksi) {
    FILE* outDataBuku = fopen("databuku.txt", "w");
    FILE* outDataTransaksi = fopen("datatransaksi.txt", "w");

    int i;
    for(i = 0; i < jmlDataBuku; i++) {
        fprintf(outDataBuku, "Kode Buku: %d\n", data[i].kodeBuku);
        fprintf(outDataBuku, "Nama Buku: %s\n", data[i].namaBuku);
        fprintf(outDataBuku, "Jenis Buku: %s\n", data[i].jenisBuku);
        fprintf(outDataBuku, "Harga: %d\n", data[i].harga);
        fprintf(outDataBuku, "Stok: %d\n\n", data[i].stok);
    }

    int j;
    for(j = 0; j < jmlDataTransaksi; j++) {
        fprintf(outDataTransaksi, "ID Transaksi: %d\n", dtTransaksi[j].id);
        fprintf(outDataTransaksi, "Kode Buku: %d\n", dtTransaksi[j].kodeBuku);
        fprintf(outDataTransaksi, "Nama Buku: %s\n", dtTransaksi[j].namaBuku);
        fprintf(outDataTransaksi, "Tanggal Transaksi: %s\n", dtTransaksi[j].tanggalTransaksi);
        fprintf(outDataTransaksi, "Jumlah Pembayaran: %d\n\n", dtTransaksi[j].jumlahPembayaran);
    }

    fclose(outDataBuku);
    fclose(outDataTransaksi);
}