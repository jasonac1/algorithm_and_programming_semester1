#include <stdio.h>
#include <string.h>

int main() {
    char selection[10];
    printf("Is the weather going to be hot today? ");
    scanf("%s", selection);
    if(strcmp(selection, "yes") == 0) {
        printf("I will wear a t-shirt.");
    } else if(strcmp(selection, "no") == 0) {
        printf("I would like to wear a formal shirt.");
    } else {
        printf("Invalid answer!");
    }
    
    return 0;
}