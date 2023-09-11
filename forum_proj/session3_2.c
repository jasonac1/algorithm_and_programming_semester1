#include <stdio.h>
int main() {
    char name[100]; // string
    int age; // int
    double favNumber; // double
    char favoriteLetter; // char
    float agePercentageTo30; // float

    printf("Please input your name: ");
    scanf("%s", name);
    printf("Please input your age: ");
    scanf("%d", &age);
    printf("Please input your favorite number: ");
    scanf("%lf", &favNumber);
    printf("Please input your favorite letter: ");
    scanf(" %c", &favoriteLetter); // scanf takes the enter before, so it's important to add a space
    agePercentageTo30 = ((float) age / 30) * 100;
    printf("Hello %s, you are currently %d years old. Your favorite number subtracted by pi is %lf, your favorite letter is %c and you are %.2f%% of the way there to age 30.", name, age, favNumber - 3.1415926535, favoriteLetter, agePercentageTo30);
    
    return 0;
}