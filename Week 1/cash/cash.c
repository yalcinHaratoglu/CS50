#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_coins(int cents, int value);

int main(void)
{
    int change = get_cents();
    int coins = 0;

    int quarters = calculate_coins(change, 25);
    change %= 25;

    int dimes = calculate_coins(change, 10);
    change %= 10;

    int nickels = calculate_coins(change, 5);
    change %= 5;

    int pennies = calculate_coins(change, 1);
    change %= 1;

    coins = quarters + dimes + nickels + pennies;
    printf("%i\n", coins);
}

int get_cents(void)
{
    int cents;
    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 1);
    return cents;
}

int calculate_coins(int cents, int value)
{
    return cents / value;
}
