#include <stdio.h>
#include <stdlib.h>
/* The purpose of the function main is to print a row from Pascal's triangle.
 We accomplish this by first asking the user for the row number.
 We then set up a for loop for k, representing the binomial coefficient we are currently printing.
 This for loop runs until k > row value inputted
 We can also set up our coef value as 1, since the first value of each row is 1.
 We then set up a nested for loop for i, in the for loop for k.
 It is in this nested loop that we perform our operation for the current k coefficient.
 We do so by repeated multiplication of the coefficient * (n+1-i)/i, until i > k.
 At this point we can then print the calculated coefficient, and loop back to print the next.
 This algorithm will succesfully print the row of Pascal's triangle.*/
int main()
{
  int row; // initialize row var

  printf("Enter a row index: ");  //prompt user for row number and scan their input
  scanf("%d",&row);

  // Write your code here
  for (int k=0; k<=row; k++) {  // for loop initializing k
    unsigned long coef = 1;  // initializing our coefficient to 1
    for (int i=1; i <= k; i++) {  // for loop initializing i
      coef = coef * (row + 1 - i);  // perform the coefficient calculation
      coef = coef / i;
    }
    printf("%ld ", coef);  // print our coefficient
  }
  printf("\n");  //print a newline after the row has been printed
  return 0;
}
