#include <ctype.h>
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char encode(char, string, string);

int main(int argc, string argv[])
{
    //make sure only one command-line argument
    if(argc != 2)
    {
        printf("ERROR: Multiple command-line arguments.\n");
        return 1;
    }
    //check if key is 26 long
    if(strlen(argv[1]) != 26)
    {
      printf("ERROR: Key should be exactly 26 letters long.\n");
        return 1;
    }
    //check if key contains only alphabetic character
    for(int i = 0; i < strlen(argv[1]); i++)
    {
        if(!isalpha(argv[1][i]))
        {
            printf("Key must contain only letters.\n");
            return 1;
        }
    }
    //check if all char in key are unique
    for(int i = 0; i < strlen(argv[1]); i++)
    {
        for(int j = i+1; j < strlen(argv[1]); j++)
        {
            if(argv[1][j] == argv[1][i])
            {
                printf("ERROR: Key should contain only unique characters.\n");
                return 1;
            }
        }
    }
    string key = argv[1];
    //make array of the key, e.g. Letter K1 in pos 0, Letter K2 in pos 2, Letter K3 in pos 3.
    //make uppercase version
    string upper_key[strlen(key)+1];
    for(int i = 0; i < strlen(key); i ++)
    {
        upper_key[i] = toupper(key[i]);
    }
    upper_key[strlen(key)] = '\0';
    //make lowercase version
    string lower_key[strlen(key)+1];
    for(int i = 0; i < strlen(key); i ++)
        {
            lower_key[i] = tolower(key[i]);
        }
        lower_key[strlen(key)] = '\0';

    //prompt user for plaintext
    string plaintext = get_string("plaintext: ");
    //subsitute each character in the string according to the key
    printf("ciphertext: ");
    encoded_char = 0
    for(int i = 0; i < strlen(plaintext); i++)
    {
        encoded_char = encode(plaintext[i], upper_key, lower_key);
        printf("%c", encoded_char);
    }
    printf("\n")
    return 0
}

//function to check validity of key (26 char and only alphabetic)
//function to substitute each character
char encode(char c, string u, string l)
{
    //check if character is alphabetical
    if(isalpha(c))
    {
        if(isupper(c))
        {
            c = u[c-65];
            return c;
        }
        if(islower(c))
        {
            c = l[c-97];
            return c;
        }
    }
    //if not alphabetical, skip it
    return c;
}
    //check if character of plaintext is alphabetical

    //make 2 26 char-long arrays out of the key. One in lower case and one in upper case
    //take char, convert from ASCII (e.g A = 0) and set equal to value at pos (eg. pos 0)
    //use a for loop to iterate through the characters of the plaintext string. For the i-th char:
        //check if uppercase, if so, print the


        .


