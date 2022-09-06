#include <stdio.h>
#include <cs50.h>
#include <math.h>
//announce function
long get_number(void);


int main(void)
{
    //get and copy number
    long number = get_number();
    long numberC = number;
    //count number of digits
    int digits = 1;
    do
    {
        number /= 10;
        digits ++;
    }
    while (number > 9);
    //take only 13 15 and 16 digits
    if (digits < 13 || digits > 16 || digits == 14)
    {
        printf("INVALID\n");
    }
    //make a variable for every digit
    int digit1 = 2, digit2 = 0, digit3 = 0, digit4 = 0, digit5 = 0;
    int digit6 = 0, digit7 = 0, digit8 = 0, digit9 = 0, digit10 = 0;
    int digit11, digit12, digit13 = 0, digit14 = 0, digit15 = 0, digit16 = 0;
    //first test a 13 digit number
    if (digits == 13)
    {
        //find the value of each digit in a 13 digit number
        for (int i = 0; i < 13; i++)
        {
            switch (i)
            {
                //each iteratio of for loop, switch which digit is being calculated
                case 0 :
                    digit13 = numberC % 10;
                    break;
                case 1 :
                    digit12 = numberC % 10;
                    break;
                case 2 :
                    digit11 = numberC % 10;
                    break;
                case 3 :
                    digit10 = numberC % 10;
                    break;
                case 4 :
                    digit9 = numberC % 10;
                    break;
                case 5 :
                    digit8 = numberC % 10;
                    break;
                case 6 :
                    digit7 = numberC % 10;
                    break;
                case 7 :
                    digit6 = numberC % 10;
                    break;
                case 8 :
                    digit5 = numberC % 10;
                    break;
                case 9 :
                    digit4 = numberC % 10;
                    break;
                case 10 :
                    digit3 = numberC % 10;
                    break;
                case 11 :
                    digit2 = numberC % 10;
                    break;
                case 12 :
                    digit1 = numberC % 10;
                    break;
            }
            //change number to find next digit
            numberC /= 10;
        }
        //copy first digits to use later
        int digit1C = digit1;
        int digit2C = digit2;
        //multiply digits by 2 and add the digits
        //test if the digit * 2 will be single digit
        if (digit2 >= 5)
        {
            digit2 *= 2;
            digit2 %= 10;
            digit2++;
        }
        else
        {
            digit2 *= 2;
        }
        //test if the digit * 2 will be single digit
        if (digit4 >= 5)
        {
            digit4 *= 2;
            digit4 %= 10;
            digit4++;
        }
        else
        {
            digit4 *= 2;
        }
        //test if the digit * 2 will be single digit
        if (digit6 >= 5)
        {
            digit6 *= 2;
            digit6 %= 10;
            digit6++;
        }
        else
        {
            digit6 *= 2;
        }
        //test if the digit * 2 will be single digit
        if (digit8 >= 5)
        {
            digit8 *= 2;
            digit8 %= 10;
            digit8++;
        }
        else
        {
            digit8 *= 2;
        }
        //test if the digit * 2 will be single digit
        if (digit10 >= 5)
        {
            digit10 *= 2;
            digit10 %= 10;
            digit10++;
        }
        else
        {
            digit10 *= 2;
        }
        //test if the digit * 2 will be single digit
        if (digit12 >= 5)
        {
            digit12 *= 2;
            digit12 %= 10;
            digit12++;
        }
        else
        {
            digit12 *= 2;
        }
        //calculate checksum
        int checksum = digit1 + digit2 + digit3 + digit4 + digit5 + digit6;
        checksum = checksum + digit7 + digit8 + digit9 + digit10 + digit11 + digit12 + digit13;
        checksum %= 10;
        //test if card passes
        if (checksum == 0 && digit1C == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }

    }
    //test 15 digit number
    if (digits == 15)
    {
        //find value of 15 digits
        for (int i = 0; i < 15; i++)
        {
            switch (i)
            {
                //each iteration of for loop switch digit
                case 0 :
                    digit15 = numberC % 10;
                    break;
                case 1 :
                    digit14 = numberC % 10;
                    break;
                case 2 :
                    digit13 = numberC % 10;
                    break;
                case 3 :
                    digit12 = numberC % 10;
                    break;
                case 4 :
                    digit11 = numberC % 10;
                    break;
                case 5 :
                    digit10 = numberC % 10;
                    break;
                case 6 :
                    digit9 = numberC % 10;
                    break;
                case 7 :
                    digit8 = numberC % 10;
                    break;
                case 8 :
                    digit7 = numberC % 10;
                    break;
                case 9 :
                    digit6 = numberC % 10;
                    break;
                case 10 :
                    digit5 = numberC % 10;
                    break;
                case 11 :
                    digit4 = numberC % 10;
                    break;
                case 12 :
                    digit3 = numberC % 10;
                    break;
                case 13 :
                    digit2 = numberC % 10;
                    break;
                case 14 :
                    digit1 = numberC % 10;
                    break;
            }
            //next digit
            numberC /= 10;
        }
        //copy first digits
        int digit1C = digit1;
        int digit2C = digit2;
        //multiply digits by two and add
        //test if the digit * 2 will be single digit
        if (digit2 >= 5)
        {
            digit2 *= 2;
            digit2 %= 10;
            digit2++;
        }
        else
        {
            digit2 *= 2;
        }
        //test if the digit * 2 will be single digit
        if (digit4 >= 5)
        {
            digit4 *= 2;
            digit4 %= 10;
            digit4++;
        }
        else
        {
            digit4 *= 2;
        }
        //test if the digit * 2 will be single digit
        if (digit6 >= 5)
        {
            digit6 *= 2;
            digit6 %= 10;
            digit6++;
        }
        else
        {
            digit6 *= 2;
        }
        //test if the digit * 2 will be single digit
        if (digit8 >= 5)
        {
            digit8 *= 2;
            digit8 %= 10;
            digit8++;
        }
        else
        {
            digit8 *= 2;
        }
        //test if the digit * 2 will be single digit
        if (digit10 >= 5)
        {
            digit10 *= 2;
            digit10 %= 10;
            digit10++;
        }
        else
        {
            digit10 *= 2;
        }
        //test if the digit * 2 will be single digit
        if (digit12 >= 5)
        {
            digit12 *= 2;
            digit12 %= 10;
            digit12++;
        }
        else
        {
            digit12 *= 2;
        }
        //test if the digit * 2 will be single digit
        if (digit14 >= 5)
        {
            digit14 *= 2;
            digit14 %= 10;
            digit14++;
        }
        else
        {
            digit14 *= 2;
        }
        //calculate checksum
        int checksum = digit1 + digit2 + digit3 + digit4 + digit5 + digit6 + digit7 + digit8;
        checksum = checksum + digit9 + digit10 + digit11 + digit12 + digit13 + digit14 + digit15;
        checksum %= 10;
        //test if card passes
        if (checksum == 0 && digit1C == 3)
        {
            if (digit2C == 4 || digit2C == 7)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }

    }
    //test 16 digit number
    if (digits == 16)
    {
        //find value of 16 digits
        for (int i = 0; i < 16; i++)
        {
            switch (i)
            {
                //each time find next digit
                case 0 :
                    digit16 = numberC % 10;
                    break;
                case 1 :
                    digit15 = numberC % 10;
                    break;
                case 2 :
                    digit14 = numberC % 10;
                    break;
                case 3 :
                    digit13 = numberC % 10;
                    break;
                case 4 :
                    digit12 = numberC % 10;
                    break;
                case 5 :
                    digit11 = numberC % 10;
                    break;
                case 6 :
                    digit10 = numberC % 10;
                    break;
                case 7 :
                    digit9 = numberC % 10;
                    break;
                case 8 :
                    digit8 = numberC % 10;
                    break;
                case 9 :
                    digit7 = numberC % 10;
                    break;
                case 10 :
                    digit6 = numberC % 10;
                    break;
                case 11 :
                    digit5 = numberC % 10;
                    break;
                case 12 :
                    digit4 = numberC % 10;
                    break;
                case 13 :
                    digit3 = numberC % 10;
                    break;
                case 14 :
                    digit2 = numberC % 10;
                    break;
                case 15 :
                    digit1 = numberC % 10;
                    break;
            }
            //next digit
            numberC /= 10;
        }
        //copy first digits
        int digit1C = digit1;
        int digit2C = digit2;
        //multiply by two and add
        //test if the digit * 2 will be single digit
        if (digit1 >= 5)
        {
            digit1 *= 2;
            digit1 %= 10;
            digit1++;
        }
        else
        {
            digit1 *= 2;
        }
        //test if the digit * 2 will be single digit
        if (digit3 >= 5)
        {
            digit3 *= 2;
            digit3 %= 10;
            digit3++;
        }
        else
        {
            digit3 *= 2;
        }
        //test if the digit * 2 will be single digit
        if (digit5 >= 5)
        {
            digit5 *= 2;
            digit5 %= 10;
            digit5++;
        }
        else
        {
            digit5 *= 2;
        }
        //test if the digit * 2 will be single digit
        if (digit7 >= 5)
        {
            digit7 *= 2;
            digit7 %= 10;
            digit7++;
        }
        else
        {
            digit7 *= 2;
        }
        //test if the digit * 2 will be single digit
        if (digit9 >= 5)
        {
            digit9 *= 2;
            digit9 %= 10;
            digit9++;
        }
        else
        {
            digit9 *= 2;
        }
        //test if the digit * 2 will be single digit
        if (digit11 >= 5)
        {
            digit11 *= 2;
            digit11 %= 10;
            digit11++;
        }
        else
        {
            digit11 *= 2;
        }
        //test if the digit * 2 will be single digit
        if (digit13 >= 5)
        {
            digit13 *= 2;
            digit13 %= 10;
            digit13++;
        }
        else
        {
            digit13 *= 2;
        }
        //test if the digit * 2 will be single digit
        if (digit15 >= 5)
        {
            digit15 *= 2;
            digit15 %= 10;
            digit15++;
        }
        else
        {
            digit15 *= 2;
        }
        //find checksum
        int checksum = digit1 + digit2 + digit3 + digit4 + digit5 + digit6 + digit7 + digit8;
        checksum = checksum + digit9 + digit10 + digit11 + digit12 + digit13 + digit14 + digit15 + digit16;
        checksum %= 10;
        //test card
        if (checksum == 0 && digit1C == 4)
        {
            printf("VISA\n");
        }
        else if (checksum == 0 && digit1C == 5)
        {
            if (digit2C == 1 || digit2C == 2 || digit2C == 3 || digit2C == 4 || digit2C == 5)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
}
//get number
long get_number(void)
{
    long number;
    number = get_long("Number: ");
    return number;
}