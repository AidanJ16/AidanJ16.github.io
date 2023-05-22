#include <stdlib.h>
#include <stdio.h>
/* Errors and their effects on the program:
 * The first error we encountered was in the func is_prime.
 * Here we found that we returned the wrong value, 1, when the number was not prime
 * and 0 if it was which made us print nothing.
 * To fix this bug we just had to make sure to switch the return values in the function.
 * The second error we encountered was in the func print_semiprimes.
 * We know that a semiprime is a product of two prime numbers.
 * So checking if j was prime when it evenly divided our number i found us the first prime factor.
 * To find the second prime factor k,
 * we have to first make sure k*j = i, based on our definition of semiprime.
 * So we had to change k = i%j to k = i/j, to get the factor of i corresponding to j.
 * The third  error we encountered was also in the func print_semiprimes.
 * We found that for numbers such as 6, we could find the prime factors 2 and 3, and thus print 6.
 * However we also would discover the prime factors 3 and 2, and thus again print 6.
 * To fix this bug when we print the semiprime number we break to 
 * ensure this semiprime is not printed multiple times.
 * The fourth and last error was our return value. 
 * The func print_semiprimes sets our return value ret to 0 but never changes it again.
 * So our return value will always be 0, even if there are semiprimes from [a,b].
 * So to fix  when we print a semiprime we need to update ret and set it equal to 1.
 */

/*
 * is_prime: determines whether the provided number is prime or not
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
    int i;
    if (number == 1) {return 0;}
    for (i = 2; i < number; i++) { //for each number smaller than it
        if (number % i == 0) { //check if the remainder is 0
            return 0;
        }
    }
    return 1;
}


/*
 * print_semiprimes: prints all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
    int i, j, k;
    int ret = 0;
    for (i = a; i <=b; i++) { //for each item in interval
        //check if semiprime
        for (j = 2; j <= i; j++) {
            if (i%j == 0) {
                if (is_prime(j)) {
                    k = i/j;
                    if (is_prime(k)) {
                        printf("%d ", i);
			ret = 1;
			break;
                    }
                }
            }
        }

    }
    printf("\n");
    return ret;

}
