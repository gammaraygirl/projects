#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>



// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

//prompt for input prototype
//convert to uppercase prototype
void return_uppercase(string);
int scoring(string);

int main (void)
{
    //Prompt user 1 for input
    string p1_input = get_string("Player 1 word: ");
    //get p1 string length
    int p1_input_lenth = strlen(p1_input);
    //convert player 1 input to uppercase
    return_uppercase(p1_input);
    //add up p1 score
    int p1_score = scoring(p1_input);



    // Prompt user 2 for input
    string p2_input = get_string("Player 2 word: ");
    // Get p2 string length
    int p2_input_lenth = strlen(p2_input);
    //convert p2 input to uppercase
    return_uppercase(p2_input);
    //add up p2 score
    int p2_score = scoring(p2_input);

    //print scores
    printf("Player 1 score: %i \n", p1_score);
    printf("Player 2 score: %i \n", p2_score);

    if (p1_score > p2_score)
    {
        printf("Player 1 wins!\n");
    }
    else if (p2_score > p1_score)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("It's a tie!\n");
    }

}


//function to convert to uppercase
void return_uppercase(string s)
    {
    for (int i = 0, n = strlen(s); i < n; i++)
        {
            s[i] = toupper(s[i]);
        }
    }
//score function
// int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
int scoring(string s)
{
    int score = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
            if (isalpha(s[i]))
            {
        score +=  POINTS[s[i]-'A'];
            }
    }
    return score;
}
//        for (int i = 0, n = strlen(s); i < n; i++)
  //          {
 //               switch(s[i])
 //               {
  //                  case 'A': score += 1;
    //                break;
      //              case 'E': score += 1;
        //            break;
          //          case 'I': score += 1;
            //        break;
              //      case 'O': score += 1;
                   // break;
 //                   case 'U': score += 1;
 //                   break;
  //                  case 'L': score += 1;
  //                  break;
  //                  case 'N': score += 1;
   //                 break;
  //                  case 'S': score += 1;
    //                break;
   //                 case 'T': score += 1;
   //                 break;
  //                  case 'R': score += 1;
   //                 break;
   //                 case 'D': score += 2;
    //                break;
    //                case 'G': score += 2;
    //                break;
    //                case 'B': score += 3;
  //                  break;
    //                case 'C': score += 3;
      //             break;
       //            case 'M': score += 3;
         //           break;
        //            case 'P': score += 3;
           //         break;
             //       case 'F': score += 4;
 //                   break;
   //                 case 'H': score += 4;
     //               break;
       //             case 'V': score += 4;
         //           break;
           //         case 'W': score += 4;
             //       break;
               //     case 'Y': score += 4;
                 //   break;
          //          case 'K': score += 5;
            //        break;
              //      case 'J': score += 8;
                //    break;
                  //  case 'X': score += 8;
 //                   break;
   //                 case 'Q': score += 10;
     //               break;
       //             case 'Z': score += 10;
         //           break;
           //         default: score += 0;
             //   }
 //           }
   //     return score;
//}
//1 point - A, E, I, O, U, L, N, S, T, R
//2 points - D, G
//3 points - B, C, M, P
//4 points - F, H, V, W, Y
//5 points - K
//8 points - J, X
//10 points - Q, Z
//0 points - Blank Tiles
