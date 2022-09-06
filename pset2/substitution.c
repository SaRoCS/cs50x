#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

string cipher(string ptext, string key);

int main(int argc, string argv[])
{
    //get argument
    string k = argv[1];
    //check for only one key
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    //check key length
    if (strlen(k) != 26)
    {
        printf("Key must be 26 characters\n");
        return 1;
    }
    //check non-alphabetic
    int counter = 0;
    for (int i = 0, n = strlen(k); i < n; i++)
    {
        bool x = isalpha(k[i]);
        if (x == true)
        {
            counter++;
        }
    }
    if (counter != strlen(k))
    {
        printf("Key can only contain alphabetic characters\n");
        return 1;
    }
    //check repeated characters
    for (int i = 0, n = strlen(k); i < n; i++)
    {
        //convert to lower for case insensitive
        k[i] = tolower(k[i]);
    }
    int repeat = 0;
    for (int i = 0, n = strlen(k); i < n; i++)
    {
        //each letter
        int x, y, z;
        z = 1;
        for (int j = 0; j < n; j++)
        {
            //compare it to every other letter and count
            y = i + z;
            x = y % 26;
            if (k[i] == k[x])
            {
                repeat++;
            }
            z++;
        }
    }
    // subtract the letters that are equal to themselves
    repeat -= 26;
    if (repeat != 0)
    {
        printf("Characters cannot be repeated\n");
        return 1;
    }
    string key = k;

    //get text
    string ptext = get_string("plaintext: ");
    //cipher
    string ctext = cipher(ptext, key);
    printf("ciphertext: %s\n", ctext);
    return 0;
}

string cipher(string ptext, string key)
{
    string ctext = ptext;
    for (int i = 0, n = strlen(ptext); i < n; i++)
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
                int z = ptext[i];
                ptext[i] = key[z];
                ctext[i] = ptext[i];
            }
            //uppercase
            else if (y == false)
            {
                //alpha index
                ptext[i] -= 65;
                int z = ptext[i];
                ptext[i] = key[z];
                ptext[i] = toupper(ptext[i]);
                ctext[i] = ptext[i];
            }
        }
        else
        {
            //keep punctuation the same
            ctext[i] = ptext[i];
        }
    }
    return ctext;
}


