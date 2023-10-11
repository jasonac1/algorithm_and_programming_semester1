#include <stdio.h>
#include <string.h>
#define WHITEBOLD "\033[1;37m"
#define GREENBOLD "\033[1;32m"
#define RED "\033[0;31m"
#define RESET "\033[0;0m"

typedef struct dataPegawai {
    char nip[19]; //basisnya NIP PNS (18-digit)
    char nama[100];
    char alamat[100];
    char no_hp[16]; //15 digit maksimum biar aman;
    char jabatan[50];
    char golongan[3]; // 2 character maksimum (D1, D2, D3)
    int gajiPokok;
    int gajiLembur;
    int jamLembur;
    int gajiTotal; 

} DP;

long int gajiPokokDari(char * s);
long int gajiLemburDari(char * s);
void mintaInput1(struct dataPegawai *ptr, int i);
void mintaInput2(struct dataPegawai *s1);
void displayEntri(struct dataPegawai *ptr, int i);
int matchAndReturnGaji(struct dataPegawai kini, struct dataPegawai *semua);
void nullify(char s[], int bufsize);
int strToInt(char s[]);
void invalidInput(char * s);

//input safety
int testforInt(char * s);

int main() {
    DP pegawai[100]; //terisi semua data
    DP pegawaiKini; //terisi data kini yang akan dicek keberadaannya dalam variabel pegawai.
    int i = 0;
    char pilihan[3]; 
    while(1) {
        fflush(stdin);
        mintaInput1(pegawai, i);
        if((pegawai+i)->gajiPokok == -1) {
            invalidInput("Mohon input salah satu diantara D1, D2, dan D3 (case-sensitive).");
            continue;
        }
        printf("\n");

        printf("%sTelah dimasukkan data sebagai berikut sebagai entri ke-%d (maksimal 100 entri):\n%s", GREENBOLD, i+1, RESET);
        displayEntri(pegawai, i);

        fflush(stdin);

        pilihLagi:
        printf("\nApakah Anda ingin menambah entris lagi? (Y/N): ");
        fgets(pilihan, 3, stdin);
        nullify(pilihan, 3);
        //program menanyakan user apakah ingin menamabh entri lagi. Jika input invalid, balik ke menanyakan pilihan user.
        switch(pilihan[0]) {
            case 'Y':
            case 'y':
                i++;
                continue;
                break;

            case 'N':
            case 'n':
                break;
            
            default: 
                invalidInput("");
                goto pilihLagi;    
        }

        pilihLagi2:
        printf("Apakah Anda ingin menampilkan gaji total pegawai? (Y/N): ");
        fflush(stdin);
        fgets(pilihan, 3, stdin);
        //jika tidak, program menanyakan user apakah ingin menambah entri lagi. Jika tidak, maka exit program. Jika input invalid, balik ke menanyakan pilihan user.
        if(pilihan[0] == 'N' || pilihan[0] == 'n') {
            printf("\nApakah Anda ingin menambah entri lagi? (Y/N) (N akan mengakhiri program.): ");
            fflush(stdin);
            fgets(pilihan, 3, stdin);
            switch(pilihan[0]) {
                case 'Y':
                case 'y':
                    i++;
                    continue;
                    break;

                case 'N':
                case 'n':
                    return 0;
                    break;

                default:
                    invalidInput("");
                    goto pilihLagi2;
            }
        }

        //pass (lanjut ke statement berikut hanya untuk input Y atau y)
        if(pilihan[0] == 'Y' || pilihan[0] == 'y') {
            ;
        }

        else {
            invalidInput("");
            goto pilihLagi2;
        }

        //di sini statement dimulai jika ingin mengisi gaji total pegawai (Y atau y)
        //printf("This is what you get when you choose Y for the gaji total pegawai (Input 2): \n");
        tampilkanGaji:
        mintaInput2(&pegawaiKini);
        nullify(pegawaiKini.nip, 19);
        nullify(pegawaiKini.golongan, 3);

        //printf("jam lembur: %d\n", pegawaiKini.jamLembur);
        //jika ketemu data pegawai dengan NIP dan golongan yang sama di daftar pegawai, maka execute statement dalam blok.
        matchAndReturnGaji(pegawaiKini, pegawai);
        pilihLagi3:
        printf("Apakah Anda ingin menampilkan gaji total pegawai lagi? (Y/N) (N akan mengakhiri program): ");
        fflush(stdin);
        fgets(pilihan, 3, stdin);
        nullify(pilihan, 3);
        switch(pilihan[0]) {
            case 'Y':
            case 'y':;
                goto tampilkanGaji;
                break;

            case 'N':
            case 'n':
                return 0;
                break;

           default:
                invalidInput("");
                goto pilihLagi3;
                
        }
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

//mengembalikan gaji pokok berdasarkan golongan
long int gajiPokokDari(char * s) { 
    if(s[0] == 'D') {
        if(s[1] == '1') return 2500000;
        if(s[1] == '2') return 2000000;
        if(s[1] == '3') return 1500000;
        else {
            return -1;
        }
    }
    //error code
    return -1;
}

//mengembalikan gaji lembur berdasarkan golongan
long int gajiLemburDari(char * s) {
    if(s[0] == 'D') {
        if(s[1] == '1') return 10000;
        if(s[1] == '2') return 5000;
        if(s[1] == '3') return 2500;
        else {
            return -1;
        }
    }
    //error code
    return -1;
}

//untuk input semua pegawai, karena array struct, jadi perlu adanya counter i
//jika setiap input gagal karena invalid, maka akan memanggil function kembali secara recursive.
void mintaInput1(struct dataPegawai *ptr, int i) {
    printf("Masukkan data pegawai:\n");
    fflush(stdin);
    printf("NIP                     = ");
    fgets((ptr+i)->nip, 19, stdin);
    nullify((ptr+i)->nip, 19);
    if(testforInt((ptr+i)->nip) == -1) { 
        invalidInput("Hanya boleh angka (0-9).");
        mintaInput1(ptr, i);
    }

    printf("Nama Pegawai            = ");
    fgets((ptr+i)->nama, 100, stdin);
    nullify((ptr+i)->nama, 100);

    printf("Alamat tempat tinggal   = ");
    fgets((ptr+i)->alamat, 100, stdin);
    nullify((ptr+i)->alamat, 100);

    printf("Nomor telepon / HP      = ");
    fgets((ptr+i)->no_hp, 16, stdin);
    nullify((ptr+i)->no_hp, 16);
    if(testforInt((ptr+i)->no_hp) == -1) {
        invalidInput("Hanya boleh angka (0-9).");
        mintaInput1(ptr, i);
    }

    printf("Jabatan                 = ");
    fgets((ptr+i)->jabatan, 50, stdin);
    nullify((ptr+i)->jabatan, 50);

    printf("%s\nGolongan\n%s", WHITEBOLD, RESET);
    printf("Gaji pokok\n");
        //??? mungkin kebalik?
    printf("Golongan D1             = Rp2.500.000\n");
    printf("Golongan D2             = Rp2.000.000\n");
    printf("Golongan D3             = Rp1.500.000\n\n");

    printf("Lemburan\n");
    printf("Golongan D1             = Rp10.000/jam\n");
    printf("Golongan D2             = Rp5.000/jam\n");
    printf("Golongan D3             = Rp2.500/jam\n");

    printf("Golongan                = ");
    fgets((ptr+i)->golongan, 3, stdin);
    nullify((ptr+i)->golongan, 3);

    //mengambil gaji pokok berdasarkan golongan
    (ptr+i)->gajiPokok = gajiPokokDari((ptr+i)->golongan);
    (ptr+i)->gajiLembur = gajiLemburDari((ptr+i)->golongan);
}

//untuk meminta input pegawai kini yang akan diambil datanya dari semua pegawai tersedia, berarti cuma satu instansi struct (bukan array) dan tidak diperlukan counter i
//s1 pegawai kini, s2 pegawai semua
void mintaInput2(struct dataPegawai *ptr) {
    //meminta NIP, golongan + waktu lembur, dan dicek apakah ada di daftar pegawai di function matchAndReturnGaji
    printf("Masukkan data pegawai:\n");
    fflush(stdin);
    printf("NIP                     = ");
    fgets(ptr->nip, 19, stdin);
    nullify(ptr->nip, 19);
    if(testforInt(ptr->nip) == -1) {
        invalidInput("Hanya boleh angka (0-9).");
        mintaInput2(ptr);
    }

    printf("Golongan                = ");
    fgets(ptr->golongan, 3, stdin);
    nullify(ptr->golongan, 3);
    if((ptr->golongan)[0] == 'D') {
        switch((ptr->golongan)[1]) {
            case '1':
            case '2':
            case '3':
                break;

            default:
                invalidInput("Mohon input salah satu diantara D1, D2, dan D3 (case-sensitive).");
                mintaInput2(ptr);
                break;
        }
    } else {
        invalidInput("Mohon input salah satu diantara D1, D2, dan D3 (case-sensitive).");
        mintaInput2(ptr);
    }

    printf("Lembur (dalam jam)      = ");

    //karena jamLembur adalah integer maka menggunakan variable string sementara kemudian baru dibuah menjadi integer.
    char lemburanStr[20];
    fflush(stdin);
    fgets(lemburanStr, 20, stdin);
    nullify(lemburanStr, 20);
    if(testforInt(lemburanStr) == -1)  {
        invalidInput("Hanya boleh angka (0-9)");

        mintaInput2(ptr);
    }

    int jamLembur = strToInt(lemburanStr);
    ptr->jamLembur = jamLembur;
}

void displayEntri(struct dataPegawai *ptr, int i) {
    printf("NIP                     = %s\n", (ptr+i)->nip);
    printf("Nama                    = %s\n", (ptr+i)->nama);
    printf("Alamat tempat tinggal   = %s\n", (ptr+i)->alamat);
    printf("Nomor telepon / HP      = %s\n", (ptr+i)->no_hp);
    printf("Jabatan                 = %s\n", (ptr+i)->jabatan);
    printf("Golongan                = %s\n", (ptr+i)->golongan);
    printf("Gaji pokok              = Rp%ld\n", (ptr+i)->gajiPokok);
    printf("Gaji lembur             = Rp%ld/jam\n", (ptr+i)->gajiLembur);
}

//"kini" data pegawai kini, "*semua" daftar pegawai. Akan disearch apakah ada data s1 di s2.
//matchData mencocokkan data pegawai kini dengan data dari daftar semua pegawai yang ada. Jika tidak, akan mengembalikan -1.
int matchAndReturnGaji(struct dataPegawai kini, struct dataPegawai *semua) {
    int matchIndex;
    for(int i = 0; i < 100; i++) { 
        if( (strcmp(kini.nip, (semua+i)->nip) == 0) && (strcmp(kini.golongan, (semua+i)->golongan) == 0) ) {
            //Found matching NIP and golongan at entry i+1
            matchIndex = i;
            break;
        } else { 
            matchIndex = -1;
        }
    }

    if(matchIndex == -1) {
        printf("Maaf, pegawai dengan data tersebut tidak ditemukan.\n\n");
        return -1;
    }

    //menset value pegawaiKini dari pegawai
    //krn gaji total baru didapat setelah ada jam lembur (dr pegawai kini), makanya baru memasukkan nilai gaji total ke pegawai semua setelah pegawai kini.
    kini.gajiPokok = (semua+matchIndex)->gajiPokok;
    kini.gajiLembur = (semua+matchIndex)->gajiLembur;
    kini.gajiTotal = kini.gajiPokok + (kini.gajiLembur * kini.jamLembur);
    (semua+matchIndex)->gajiTotal = kini.gajiTotal;
    printf("Gaji bulan ini = Rp%d\n\n", (semua+matchIndex)->gajiTotal);
    return 0;
}

void nullify(char * s, int bufsize) {
    for(int i = 0; i < bufsize; i++) {
        if(s[i] == '\n') {
            s[i] = '\0';
            break;
        }
    }
}

void invalidInput(char * s) {
    printf("%sMaaf, input Anda invalid. %s\n\n%s", RED, s, RESET);
    fflush(stdin);
}

int testforInt(char * s) {
    if(strToInt(s) == -1) {
        return -1;
    } else {
        return 1;
    }
}
