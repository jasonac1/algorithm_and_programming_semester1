#include <stdio.h>
int main() {
    long int total_secs = 0;
    int hrs, remaining_secs, mins;
    printf("Please input the amount of seconds: ");
    //checks for long int type. scanf returns the number of inputs successfully scanned. if string is inputted, it'll be 0.
    if(scanf("%ld", &total_secs) != 1) {
        printf("Invalid input: Invalid data type! Should be int");
        return 0;
    } 

    //checks for negative numbers
    if(total_secs < 0) {
        printf("Invalid input: Number of seconds can't be negative!");
        return 0;
    }

    //calculation:
    hrs = total_secs / 3600;
    remaining_secs = total_secs % 3600; //remaining seconds after hours are taken off.
    mins = remaining_secs / 60;
    remaining_secs = remaining_secs % 60; //remaining seconds after minutes are taken off.
    printf("%ld is %02d hours, %02d minutes, and %02d seconds.", total_secs, hrs, mins, remaining_secs); // i have no idea why it's %02. i think it has to do with the amount of digits displayed + adding a zer to the front.
    return 0;
}