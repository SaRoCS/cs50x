#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//prototype
string shift_text(string ptext, int key);

int main(int argc, string argv[])
{
    //get the c-line arument
    string k = argv[1];
    //check if there is only one argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    int counter = 0;
    int n = strlen(k);
    //check argument for digits
    for (int i = 0; i < n; i++)
    {
        bool x = isdigit(k[i]);
        if (x == true)
        {
            counter++;
        }
    }
    int key;
    //if it is all digits its the key
    if (counter == n)
    {
        key = atoi(k);
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    //get the plaintext
    string ptext = get_string("plaintext: ");
    //cipher the text
    string ctext = shift_text(ptext, key);
    //print the ciphertext
    printf("ciphertext: %s\n", ctext);
    return 0;
}

string shift_text(string ptext, int key)
{
    int n = strlen(ptext);
    string ctext = ptext;
    for (int i = 0; i < n; i++)
    {
        //check for only letters
        bool x = isalpha(ptext[i]);
        if (x == true)
        {
            //check for upper or lowercase
            bool y = islower(ptext[i]);
            //lowercase
            if (y == true)
            {
                //put it in alpha index
                ptext[i] -= 97;
                //shift it
                ctext[i] = (ptext[i] + key) % 26;
                //back to ascii
                ctext[i] += 97;

            }
            //uppercase
            else if (y == false)
            {
                //alpha index
                ptext[i] -= 65;
                //shift
                ctext[i] = (ptext[i] + key) % 26;
                //ascii
                ctext[i] += 65;
            }
        }
        else
        {
            //keep punctuation the same
            ctext[i] = ptext[i];
        }
    }
    //return the ciphertext
    return ctext;
}

