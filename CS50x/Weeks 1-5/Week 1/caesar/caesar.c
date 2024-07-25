#include <ctype.h>
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool only_digits(string);
char rotate(char, int);


int main(int argc, string argv[])
{
    //printf("%d\n", argc);

    //make sure the program was run with a single command-line argument
    if(argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    //make sure every character in argv[1] is a digit
    bool only_digits_result = only_digits(argv[1]);
    //printf("%i\n",only_digits_result);
    if (only_digits_result == false)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }


    //convert argv[1] from a 'string' to an 'int'
    int key = atoi(argv[1]);
    printf("Key: %i\n", key);

     //output "plaintext:  and prompt user for string
    string plaintext = get_string("plaintext:  ");

    //output ciphertext

    printf("ciphertext: ");
    char rotated_char = 0;
    for(int i = 0, n = strlen(plaintext); i < n; i ++)
    {
        rotated_char = rotate(plaintext[i], key);
        printf("%c", rotated_char);
    }

    printf("\n");
}


//function to check if key is only digits
bool only_digits(string s)
{
    for(int i = 0, n = strlen(s); i < n; i++)
    {
        if(isdigit(s[i]) == false)
        {
            return false;
        }
    }
    return true;
}

//function to implement caesar shift
char rotate(char c, int k)
{
    // check if char
    //printf("Rotating: %c with key: %d\n", c, k);
    if(isalpha(c))
    {
        if (k > 26)
        {
            k = k % 26;
        }
         //if uppercase
         if(isupper(c))
         {
            //printf("Before: %c\n", c);
            c -= 65; //convert from ASCII to A = 0, B = 1, etc
            c+= k; //add the key to char c
            c = c % 26; // divide mod 26 to "wrap around"
            c+= 65; //convert back to ASCII
            //printf("After: %c\n", c);
            return c;

         }
         //if lowercase
          else if(islower(c))
         {
            //printf("Before: %c\n", c);
            c -= 97; //convert from ASCII to a = 0, b = 1, etc
            c+= k; //add the key to char c
            c = c % 26; // divide mod 26 to "wrap around"
            c+= 97; //convert back to ASCII
            //printf("After: %c\n", c);
            return c;
         }
    }
    return c;
}



