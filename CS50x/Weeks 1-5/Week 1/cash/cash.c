#include <cs50.h>
#include <stdio.h>

int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // define an integer to store cents
    int cents;
    // ask for amount of change in cents
    do
    {
        cents = get_int("How many cents? ");
    }
    // check if change is greater than or equal to zero
    while (cents < 0);

    // calculate quarters, dimes, nickels, and pennies
    int quarters = calculate_quarters(cents);
    cents = cents % 25;
    int dimes = calculate_dimes(cents);
    cents = cents % 10;
    int nickels = calculate_nickels(cents);
    cents = cents % 5;
    int pennies = calculate_pennies(cents);

    int coins = quarters + dimes + nickels + pennies;
    // print results
    printf("%i\n", coins);
    printf("Please give the customer %i quarters, %i dimes, %i nickels, and %i pennies.\n", quarters, dimes, nickels, pennies);
}
// see how many quarters will fit, subtract value of quarters from cents
int calculate_quarters(int cents)
{
    int quarters = cents / 25;
    return quarters;
}
// see how many dimes will fit, subtract value of dimes from cents
int calculate_dimes(int cents)
{
    int dimes = cents / 10;
    cents = cents % 10;
    return dimes;
}
// see how many nickels will fit into the remainder, subtract value of nickels from cents
int calculate_nickels(int cents)
{
    int nickels = cents / 5;
    cents = cents % 5;
    return nickels;
}
// see how many pennies will fit into the remainder
int calculate_pennies(int cents)
{
    int pennies = cents;
    return pennies;
}

