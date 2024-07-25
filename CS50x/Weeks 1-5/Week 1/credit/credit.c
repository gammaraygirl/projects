#include<cs50.h>
#include<stdio.h>
#include<math.h>


// MASTERCARD: 16-Digit #'s, Start with: 51, 52, 53, 54, or 55
// VISA: 13-16-Digit #'s, Start with: 4
// AMEX: 15-Digit #'s, Star with: 34 or 37

// Luhn's Algorithm:
// 1. Multiply every other digit by 2, starting with the second number to the last
// 2. Add the sum of those digits
// 3. Add the sum of the other digits
// 4. If the total sum ends with a 0, it is valid!
int getLength(long);
void checkLength(int);
int firstDigits(long, int, int);

int main(void)
{
    //get cc number from user
    long creditCard = get_long("What is the credit card number?\n");
    long number = creditCard;

    //get the length of the cc number
    int length = getLength(number);
    //check if length is 13, 15, or 16 long. If else, invalid!
    checkLength(length);

    //declare variables
    int sumEvenDigits = 0;
    int sumOddDigits = 0;
    int sumFinal = 0;
    int i = 0;
    int currentDigit = 0;

    //run Luhn's Algorithm
    while(length > 0)
    {
        currentDigit = number % 10; //divide the number by modulo 10 to pull out the last digit
        number = number / 10; //update number to remove the last digit by dividing by 10 (feature of integer division in C)
        i++; //add one to the counter
        if(i % 2 == 0) //if the number is even...
        {
            if ( 2 * currentDigit > 9) //check if 2*lastDigit is greater than 9. (If greater than 9, need to separate out those digits and add them to sumEvenDigits)
            {
                int currentDigitTimes2 = currentDigit * 2; //declare a new variable to store 2*currentDigit
                int currentDigitMod = currentDigitTimes2 % 10; //do currentDigitTimes2 mod 10 to pull the last digit, and store result in new var currentDigitMod
                currentDigit = currentDigitTimes2 / 10; //divide currentDigitTimes2 by ten and update the value of currentDigit
                sumEvenDigits = sumEvenDigits + currentDigit + currentDigitMod; //add currentDigit and currentDigitMod to sumEvenDigits
            }
            else //add it to sumEvenDigits
            {
                sumEvenDigits = sumEvenDigits + 2 * currentDigit;
            }

        }
        else //if the number is odd, add the digit to sumOddDigits
        {
                sumOddDigits = sumOddDigits + currentDigit;
            }

        length--;
    }
        sumFinal = sumEvenDigits + sumOddDigits;


          if ( sumFinal % 10 != 0 )
    {
        printf("%i\n", sumFinal);
        printf("INVALID\n");
    }
// MASTERCARD: 16-Digit #'s, Start with: 51, 52, 53, 54, or 55
// VISA: 13-16-Digit #'s, Start with: 4
// AMEX: 15-Digit #'s, Star with: 34 or 37
    else
    {
        int firstTwoDigits = firstDigits(number,length, 2);

        //NEXT STEP: TURN THE BELOW INTO A CHECKCARDTYPE FUNCTION.
        //Code is already below but commented out. Don't forget to bring it to the top.

        if (currentDigit == 4 && ( length == 13 || length == 16))
        {
            printf("VISA\n");
        }
        else if (length == 16 &&(firstTwoDigits >= 51 && firstTwoDigits <=55 ))
        {
            printf("MASTERCARD\n");
        }
        else if (length == 15 && (firstTwoDigits == 34 || firstTwoDigits == 37 ))
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
}


//function to get the length of a long
int getLength(long a)
{
    int length = 0;
    while (a > 0)
        {
            a = a/10;
            length++;
        }
    return length;
}

//check the length of the cc number
void checkLength(int a)
{
     if (a != 13 && a != 15 && a != 16)
    {
        printf("INVALID\n");
    }
}

//function that will pull the first "a" number of digits off of a base-10 number
int firstDigits(long ccnumber, int length, int numDigits)
{
     int lengthTest = length;
     while(lengthTest > numDigits)
    {
        ccnumber = ccnumber/10;
        lengthTest--;
    }
    int firstDigitsResult = ccnumber;
    return firstDigitsResult;
}

//check card type
//void checkCardType()
//{
   // {
    //   firstDigits
     //   if (currentDigit == 4 && ( length == 13 || length == 16))
     //   {
      //      printf("VISA\n");
    //    }
     //   else if (length == 16 &&(test >= 51 && test <=55 ))
      //  {
      //      printf("MASTERCARD\n");
     //   }
     //   else if (length == 15 && (test == 34 || test == 37 ))
    //    {
    //        printf("AMEX\n");
    //    }
    //    else
    //    {
    //        printf("INVALID\n");
    //    }
  //  }
 //}


