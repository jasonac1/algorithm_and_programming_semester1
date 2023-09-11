#include <stdio.h>
int main() {
    int n; 
    int i, j;
    printf("Print primes up to: ");
    scanf("%d", &n);

    int factors = 0;
    for(i = 2; i <= n; i++) {
        for(j = 1; j <= i; j++) {
            if(i % j == 0) {
                factors++;
            }
        }

        if(factors == 2) {
            printf("%d\n", i);
        }
        factors = 0;
    }
    return 0;
}