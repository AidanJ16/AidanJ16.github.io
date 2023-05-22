/*			
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */



#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"

// INTRO PARAGRAPH
// We will be creating three functions: set_seet, start_game, and make_guess
// The function set_seed will take input string from user and check that there is exactly one integer in string
// If exactly one integer, we set the seed value for random number generation using the integer user inputted and return 1
// Else, we print invalid seed and return 0
// The function start_game creates 4 random numbers from 1-8 as the solution code
// The values at four integer pointers are set to the solution numbers
// The four values of the solutions code will be saved using static vairables defined directly below
// The number of guesses is set to 1 to initialize the starting of the game
// The function make_guess will take in a guess from user
// First it will check if the guess contained exactly four numbers from 1-8 seperated by spaces
// If any of these checks fail, the function prints that the guess was invalid and returns 0
// Otherwise the function counts up the numer of perfect and misplaced matches
// It then prints these counts along with the guess number
// It then increments guess number and returns 1

/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the guess number.
 */

static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int
set_seed (const char seed_str[])
{
  // use function sscanf to find integer seed value from the string the user entered
  // check that exactly one integer was entered by user
  // if exactly one integer was entered, set seed value using integer user enetered and return 1
  // else, print invalid seed and return 0
  
  int seed;  // will contain number typed by the user (if any)
  int return_val;  // return value of sscanf
  char post[2];  // will contain anything after the integer put in seed
  return_val = sscanf(seed_str, "%d%1s", &seed, post);
  if(return_val  == 1) {  // checking if return value of sscanf is 1 to indicate a single integer being read
    srand(seed);  // set seed using user input
    return 1;
  } else {
    printf("set_seed: invalid seed\n");  // if return value is not 1, print invalid seed
    return 0;
  }
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above. 
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void
start_game (int* one, int* two, int* three, int* four)
{
    // create four solution numbers using rand() to generate random number between 1 and 8,
    // set values at pointers to these numbers
    // store these solution numbers in the static vars defined above
    // set number of guesses to 1 to signal start of game
  
  *one = (rand() % 8) + 1;
  solution1 = *one;
  *two = (rand() % 8) + 1;
  solution2 = *two;
  *three = (rand() % 8) + 1;
  solution3 = *three;
  *four = (rand() % 8) + 1;
  solution4 = *four;
  guess_number = 1;
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int
make_guess (const char guess_str[], int* one, int* two, 
	    int* three, int* four)
{
  // in this function, we will check if return value of sscanf is 4 signalling we recieved exactly four integers from user
  // we then check if each integer is between 1-8
  // if any of these checks fail, we print invalid guess and return 0
  // if all checks pass, we check for perfect matches first, if there are any we set the corresponding guess and solution paired variables
  // to be paired (their paired variables set to 1), and increment number of perfect matches
  // next we then check for misplaced matches according to the corresponding guess and solution paired variables (make sure unpaired (0))
  // and if the guess and solution match
  // if so set corresponding guess and solution paired variables to 1, and increment the number of misplaced matches
  // after checking for all perfect and misplaced matches we print the number of each along with the guess number
  // we then increment guess number and return 1  
  
  // setting up our local variables
  // these include: count of perfect matches and a count of misplaced matches
  // variables to indicate if guess 1-4 has been matched with a solution 1-4 (if set to 0 unpaired, 1 paired)
  // variables to indicate if solution 1-4 has been matched with a guess 1-4 (if set to 0 unpaired, 1 paired)
  // variable to store any characters trailing the four integers from user
  // variable to store return value of sscanf
  
  int perf_match = 0;
  int mis_match = 0;
  int paired_guess1 = 0;
  int paired_guess2 = 0;
  int paired_guess3 = 0;
  int paired_guess4 = 0;
  int paired_sol1 = 0;
  int paired_sol2 = 0;
  int paired_sol3 = 0;
  int paired_sol4 = 0;
  char post[2];
  int return_val;

  // check if sscanf scanned exactly 4 integers, and that each integer is from 1-8
  return_val = sscanf(guess_str, "%d%d%d%d%1s", one, two, three, four, post);
  if(return_val == 4 && *one >= 1 && *one <=8 && *two >= 1 && *two <= 8 && *three >= 1 && *three <= 8 && *four >= 1 && *four <= 8){
    // check for perfect matches
    if (*one == solution1){
	   perf_match ++;
	   paired_guess1 ++;
	   paired_sol1 ++;
    }
    if (*two == solution2){
	   perf_match ++;
	   paired_guess2 ++;
	   paired_sol2 ++;
    }
    if(*three == solution3){
	   perf_match ++;
	   paired_guess3 ++;
	   paired_sol3 ++;
    }
    if(*four == solution4){
	   perf_match ++;
	   paired_guess4 ++;
	   paired_sol4 ++;
    }
    // check for misplaced matches for guess one
    if(paired_guess1 == 0 && paired_sol2 == 0 && *one == solution2){
	   mis_match ++;
	   paired_guess1 ++;
	   paired_sol2 ++;
    }
    if(paired_guess1 == 0 && paired_sol3 == 0 && *one == solution3){
           mis_match ++;
	   paired_guess1 ++;
	   paired_sol3 ++;
    }
    if(paired_guess1 == 0 && paired_sol4 == 0 && *one == solution4){
           mis_match ++;
           paired_guess1 ++;
	   paired_sol4 ++;
    }
    // check for misplaced matches for guess two
    if(paired_guess2 == 0 && paired_sol1 == 0 && *two == solution1){
	   mis_match ++;
	   paired_guess2 ++;
	   paired_sol1 ++;
    }
    if(paired_guess2 == 0 && paired_sol3 == 0 && *two == solution3){
           mis_match ++;
	   paired_guess2 ++;
	   paired_sol3 ++;
    }
    if(paired_guess2 == 0 && paired_sol4 == 0 && *two == solution4){
           mis_match ++;
           paired_guess2 ++;
	   paired_sol4 ++;
    }
    // check for misplaced matches for guess three
    if(paired_guess3 == 0 && paired_sol1 == 0 && *three == solution1){
	   mis_match ++;
	   paired_guess3 ++;
	   paired_sol1 ++;
    }
    if(paired_guess3  == 0 && paired_sol2 == 0 && *three == solution2){
	   mis_match ++;
	   paired_guess3 ++;
	   paired_sol2 ++;
    }
    if(paired_guess3 == 0 && paired_sol4 == 0 && *three == solution4){
	   mis_match ++;
	   paired_guess3 ++;
	   paired_sol4 ++;
    }
    // check for misplaced matched for guess four
    if(paired_guess4 == 0 && paired_sol1 == 0 && *four == solution1){
	   mis_match ++;
	   paired_guess4 ++;
	   paired_sol1 ++;
    }
    if(paired_guess4 == 0 && paired_sol2 == 0 && *four == solution2){
	   mis_match ++;
	   paired_guess4 ++;
	   paired_sol2 ++;
    }
    if(paired_guess4 == 0 && paired_sol3 == 0 && *four == solution3){
	   mis_match ++;
	   paired_guess4 ++;
	   paired_sol3 ++;
    }
    // print number of guesses, perfect matches, and misplaced matches, then increment guess number and return 1
    printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, perf_match, mis_match);
    guess_number ++;
    return 1;
 			      		       
  } else {
    // if any check above fails, print invalid guess and return 0
	 printf("make_guess: invalid guess\n");
	 return 0;
  }
  
}


