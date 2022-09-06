#include <stdio.h>
#include <cs50.h>
#include <math.h>

float get_change(void);

int main(void)
{
    //types of coins
    int quarters = 0;
    int dimes = 0;
    int nickels = 0;
    int pennies = 0;
    //get the change due and round it to cents
    float change = get_change();
    int cents = round(change * 100);
    //take off quaters
    while (cents >= 25)
    {
        cents -= 25;
        quarters ++;
    }
    //take off dimes
    while (cents >= 10)
    {
        cents -= 10;
        dimes ++;
    }
    //take off nickels
    while (cents >= 5)
    {
        cents -= 5;
        nickels ++;
    }
    //take off pennies
    while (cents >= 1)
    {
        cents -= 1;
        pennies ++;
    }
    //add the number of each coin used
    int coins = quarters + dimes + nickels + pennies;
    printf("%i\n", coins);


}
float get_change(void)
{
    float change;
    do
    {
        change = get_float("Change Owed: ");
    }
    while (change < 0);
    return change;
}
