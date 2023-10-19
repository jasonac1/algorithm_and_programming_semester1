#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int linsearch(int* intArr, int size, int key) {
    int i;
    for(i = 0; i < size; i++) {
        if(key == intArr[i]) return i;
    }
    return -1;
}


int main() {
    char noExit[100]; // supaya tidak langsung exit di akhir program
    srand(time(0)); // seed untuk angka acak
    int randInts[10];
    int key;

    //minta input user
    printf("Masukkan key yang akan dicari (1-10): ");
    scanf("%d", &key);

    //generate angka acak
    int i;
    for(i = 0; i < 10; i++) {
        randInts[i] = rand() % 10 + 1; // generate angka acak dari 1-10
    }

    printf("Angka: ");
    int j;
    for(j = 0; j < 10; j++) {
        if(j == 9) printf("%d\n", randInts[j]);
        else printf("%d ", randInts[j]);
    }

    int index = linsearch(randInts, 10, key); // mengembalikan index instansi pertama key
    if(index != -1) {
        printf("Instansi pertama key %d ditemukan dalam list pada urutan ke-%d.", key, index+1);
    } else { 
        printf("Instansi key %d tidak ditemukan dalam list.", key);
    }
    
    int c;
    while(c = getchar() != '\n' && c != EOF);
    fgets(noExit, 100, stdin);
    return 0;
}