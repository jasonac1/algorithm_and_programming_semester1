#include <stdio.h>
int addLegs(int legs) {
    static int accumulate = 0;
    accumulate += legs;
    return accumulate;
}

int main() {
    int cows;
    printf("How many cows do you see?\n");
    scanf("%d", &cows);

    int i;
    int legs;
    for(i = 0; i < cows; i++) { 
        legs = addLegs(4);
    }
    printf("Total number of legs is: %d", legs);
    return 0;
}