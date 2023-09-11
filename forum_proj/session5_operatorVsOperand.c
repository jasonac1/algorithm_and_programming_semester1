#include <stdio.h>
int main() {
    int money, cost;
    char option;
    printf("Input how much money you have: ");
    scanf("%d", &money);
    printf("How much does your item of choice cost: ");
    scanf("%d", &cost);

    //relational operator (<)
    if(cost < 0) {
        printf("You can't enter a negative cost for the item!\n");
    }

    //relational and arithmetic operators (>=, -)
    if((money >= cost)) {
        printf("You can buy your item of choice! You'll be left with %d.\n", money - cost);
    } else {
        printf("Sorry, you don't have enough money to buy your item of choice!\n");
        return 0;
    }
    
    //clears buffer
    fflush(stdin);
    
    printf("Would you like to buy the item? (Y/N): ");
    scanf("%c", &option);

    //logical and (arithmetic) assignment operators (||, -=);
    if(option == 'Y' || option == 'y') {
        money -= cost;
        printf("Item successfully bought! You now have %d money left.", money);
    } else if(option == 'N' || option == 'n') {
        printf("Okay, have a nice day!");
    } else {
        printf("Sorry, you entered an invalid option.");
        return 0;
    }

    return 0;    
}