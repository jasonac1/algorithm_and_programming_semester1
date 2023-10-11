#include <stdio.h>

int main()
{
    const short int HOURLY_RATE = 10000;
    float hours_used = 0;
    double usage_bill = 0;
    int discount_percent = 0;

    //ask user for input how on many hours used.
    printf("Please input the number of hours you used our computer (decimals are fine too.)\n");

    // Check for illegal input
    if ((scanf("%f", &hours_used) != 1) || (hours_used < 0))
    {
        printf("Input not valid.\n");
        return 1;
    } 

    // Calculate the usage bill.
    usage_bill = hours_used * HOURLY_RATE;
    // Apply discounts.
    if (hours_used > 4) discount_percent = 10;
    else if (hours_used > 6) discount_percent = 15;
    else if (hours_used > 8) discount_percent = 20;
    else if (hours_used > 10) discount_percent = 25; 

    // Calculate the usage bill.
    usage_bill *= ((100 - discount_percent) / 100.0);

    // Print the result.
    printf("Your bill is Rp%.2f\n", usage_bill);


    // TODO don't forget to convert hrs to hr, min.
    return 0;
}