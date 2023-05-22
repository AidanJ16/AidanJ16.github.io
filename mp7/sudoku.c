#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// INTRO PARAGRAPH
// To implement a C program that solves a Sudoku puzzle using recursive backtracking, we had to implement the following functions:
// The first function is is_val_in_row that checks if a given value has already been filled in the given row.
// We implemented this function by iterating through every cell in the given row.
// We then checked if the value was present in any of the cells.
// If value was found we return 1, else we return 0.
// The second function is is_val_in_col that checks if a given value has already been filled in the given column.
// We implemented this function by iterating through every cell in the given column.
// We then checked if the value was present in any of the cells.
// If value was found we return 1, else we return 0.
// The third function is is_val_in_3x3_zone that checks if the given value has already been filled in the 3x3 zone corresponding to the given cell (i,j).
// We implemented this function by taking the given cell and finding the top left cell of the corresponding 3x3 zone that the given cell is in.
// We then iterated through all cells in the zone and checked if any of them had the given value.
// If value was found we return 1, else we return 0.
// The fourth function is is_val_valid, that uses the first three functions to check the legality of filling a given cell with a given val.
// We implemented this function by calling the first three functions.
// If all functions returned 0, that means the value was not found in the row, column, or zone, so we return 1.
// Else the value was found and we return 0.
// The fifth function is solve_sudoku that uses the fourth function and recursive backtracking to solve the sudoku board
// We implemented this function through the recursive backtracking algorithm shown in the description of the mp.
// We did so by checking if all cells were assigned numbers 1-9, if so retrun 1.
// Else we find a cell that has the value 0, and using our fourth function, cheked if the cell could be filled with numbers 1-9.
// If the cell can be filled by the number we change the cells value to that number and call our function on our changed board.
// If the call works we return true, otherwise we change the cell back to 0 and try a different number.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
  // iterate through each cell in row i
  for (int j = 0; j < 9; j++){
    if (val == sudoku[i][j]) {
      return 1;  // if value is found return 1
    }
  }
  return 0;  // if value was not found return 0
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
  // iterate through all cells in column j
  for (int i = 0; i < 9; i++){
    if (val == sudoku[i][j]) {
      return 1;  // if value was found, return 1
    }
  }
  return 0;  // if value was not found return 0
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  // BEG TODO
  // compute offsets of given cell so as to ensure we begin at the top left cell of the
  // corresponding 3x3 zone that the given cell resides
  int srow = i - i % 3;
  int scol = j - j % 3;
  // iterate through 3x3 zone
  for (int p = 0; p < 3; p++) {
      for (int q = 0; q < 3; q++) {
	  if (val == sudoku[p + srow][q + scol]) {
	    return 1;  // if value was found, return 1
	  }
	}
  }
  return 0;  // if value was not found, return 0
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
  // check that value is not found in row, column, or 3x3 zone of our cell
  if(!(is_val_in_row(val, i, sudoku)) && !(is_val_in_col(val, j, sudoku)) && !(is_val_in_3x3_zone(val, i, j, sudoku)))
    return 1;  // if value wasn't found in any of the above, return 1
  return 0;  // if value was found return 0
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
  // set up local variables, i and j corresponding to the row and column of cell in question
  // and b being the boolean to ensure we break out of the double for loop when we found a cell == 0
  int i, j;
  bool b = false;
  // iterate through sudoku board
  for(i = 0; i < 9; i++) {
    for(j = 0; j < 9; j++) {
      if(sudoku[i][j] == 0) {  // if we found a cell == 0, we set b to true and break out of if loop
	b = true;
	break;
      } else if(i == 8 && j == 8) {  // if all cells arent equal to 0 and we have reached the end of our board, return 1
	return 1;
      }
    }
    if(b)  // if we found a cell == 0, break out of for loop
      break;
  }
  // iterate through numbers 1-9 and check if the cell can be filled with them
  for(int num = 1; num <= 9; num++) {
    if(is_val_valid(num, i, j, sudoku)) {  // if cell can take value, implement the change
      sudoku[i][j] = num;
      if (solve_sudoku(sudoku))  // if cell change works return true, otherwise reset change and keep trying other numbers
          return  1;
	sudoku[i][j] = 0;
    }
  }
  return 0;  // else return 0
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}





