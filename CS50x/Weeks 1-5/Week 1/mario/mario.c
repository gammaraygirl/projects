#include <cs50.h>
#include <stdio.h>
int main(void)
{
    int height;
    do
    {
         height = get_int("What is the height? ");
    }
    while (height < 1 || height > 8);


    for (int i = 0; i < height; i++)
    {
        //generate H-i spaces per row
        for( int spaces = 0; spaces < height-i; spaces++)
        {
            printf(" ");
        }
        //generate i hashes per row
        for( int l_hashes = 0; l_hashes <= i; l_hashes++)
        {
            printf("#");
        }
        //print 2 spaces
        printf("  ");

        //print i hashes again
        for( int r_hashes = 0; r_hashes <=i; r_hashes++)
        {
            printf("#");
        }

        //new line
        printf("\n");
    }

}
