#include "game.h"

// INTRO PARAGRAPH
// To implement the game 2048 we had to implement the following functions
// In the function make_game, we had to create an instance of a game structure with the given number of rows and columns
// Also had to initialize the cells to -1 and the score to 0
// In the function remake_game, we had to change a game structure passed by reference with the given number of rows and columns
// Also had to initialize the cells to -1 and the score to 0
// In the function get_cell we had to return a pointer to the cell corresponding to the given row and column
// If the row or column given is out of range we return NULL
// In the function move_w we had to slide all the tiles in the game upwards
// If a tile matches with the one above it, the tiles had to be merged by adding their values together
// Had to ensure a tile does not merge twice
// We return 0 if sliding tiles up causes no cell to change value, otherwise we return 1
// In the function move_s we had to slide all the tiles in the game downwards
// If a tile matched the one below it, the tiles had to be merged by adding their values together
// Had to ensure a tile does not merge twice
// We return 0 if sliding tiles down causes no cell to change value, otherwise we return 1
// In the function move_a we had to slide all tiles in the game to the left
// If a tile matched the one to the left of it, the tiles had to be merged by adding their values together
// Had to ensure a tile does not merge twice
// We return 0 if sliding tiles to the left causes no cell to change value, otherwise we return 1
// In the function move_d we had to slide all tiles in the game to the right
// If a tile matched the one to the right of it, the tiles had to be merged by adding their values together
// Had to ensure a tile does not merge twice
// We return 0 if sliding tiles to the right causes no cell to change value, otherwise we return 1
// In the function legal_move_check we had to check if any legal moves were possible
// If there are legal moves possible, we return 1, otherwise we return 0

game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
    mygame->rows = rows;  // assign given rows
    mygame->cols = cols;  // assign given columns
    mygame->score = 0;  // set score to 0
    for(int i = 0; i < rows; i++) {  // loop through every cell
      for(int j = 0; j < cols; j++) {
	mygame->cells[i*cols + j] = -1;  // set cells to -1
      }
    }

    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
	(*_cur_game_ptr)->rows = new_rows;  // assign given rows 
        (*_cur_game_ptr)->cols = new_cols;  // assign given columns
	(*_cur_game_ptr)->score = 0;  // set score to 0
	for(int i = 0; i < new_rows; i++) {  // loop through all cells
	  for(int j = 0; j < new_cols; j++) {
	    (*_cur_game_ptr)->cells[i*new_cols + j] = -1; // set cells to -1
	  }
	}
	return;
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE
  if(row < cur_game->rows && row >= 0 && col < cur_game->cols && col >= 0){
    return &(cur_game->cells[row*cur_game->cols + col]);  // if row and col are valid return pointer to the cell
  }
  return NULL;  // otherwise return NULL
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{
    //YOUR CODE STARTS HERE
  int target_i;  // var for the target row to move our cells to
  int merge;  // var for when we need to merge only once
  int cols = cur_game->cols;  
  int rows = cur_game->rows;
  int val = 0;  // return value
  for(int j = 0; j < cols; j++) {  // loop through each column
    target_i = 0;  // set target to topmost cell
    for(int i = 1; i < rows; i++) {  // loop through each row in the column (can disregard row 0)
      if(cur_game->cells[i*cols + j] != -1) {  // if the cell is not empty
	while(cur_game->cells[target_i*cols + j] != -1 && target_i < i) { 
	  ++target_i;  // increase target row until we find empty cell or it passes the row in question
	}
	if(target_i < i) {  // if target row is above the row in question
	  cur_game->cells[target_i*cols + j] = cur_game->cells[i*cols + j];  // move cell up to target row
	  cur_game->cells[i*cols + j] = -1;  // cell in question is set to empty
	  val = 1;  // set return value to 1
	}
      }
    }
  }
  for(int p = 0; p < cols; p++) {  // loop through each column
    merge = 0;  // set merge to 0
    for(int q = 1; q < rows; q++) {  // loop through each row in the column (can disregard row 0)
      // if cell in question and cell above have same value, cell above hasn't been merged already, and our cells aren't empty
      if(cur_game->cells[q*cols + p] == cur_game->cells[(q - 1)*cols + p] && (q - 1) >= merge && cur_game->cells[q*cols + p] != -1) {
	cur_game->cells[(q - 1)*cols + p] += cur_game->cells[q*cols + p];  // double value of cell above cell in question
	cur_game->cells[q*cols + p] = -1;  //cell in question is set to empty
	cur_game->score += cur_game->cells[(q - 1)*cols + p];  // increase score by cell above value
	merge = q;  // set merge to cell in question so as to not merge the cell above again
	val = 1;  // return value set to 1
      }
    }
  }
  for(int a = 0; a < cols; a++) { // loop through columns
    target_i = 0;  // set target to 0
    for(int b = 1; b < rows; b++) {  // loop through each row in columns
      if(cur_game->cells[b*cols + a] != -1) {  // if cell is empty
	while(cur_game->cells[target_i*cols + a] != -1 && (target_i < b)) { 
	  ++target_i;  // while the target cell is not empty and is above the cell in question, increase target
	}
	if(target_i < b) {  // if target row is above row in question
	  cur_game->cells[target_i*cols + a] = cur_game->cells[b*cols + a];  // move cell in question to target row
	  cur_game->cells[b*cols + a] = -1; // set cell in question to empty
	  val = 1;  // return value set to 1
	}
      }
    }
  }
  return val;
};

int move_s(game * cur_game) //slide down
{
    //YOUR CODE STARTS HERE
  int target_i;  // target row
  int merge;  // var for merging
  int cols = cur_game->cols;
  int rows = cur_game->rows;
  int val = 0;  // return value
  for(int j = 0; j < cols; j++) {  // loop through each column
    target_i = rows-1;  // set target to lowest row
    for(int i = rows-2; i >= 0; i--) {  // loop through each row from bottom to top of column
      if(cur_game->cells[i*cols + j] != -1) {  // if cell is not empty
	while(cur_game->cells[target_i*cols + j] != -1 && target_i > i) {
	  --target_i;  // while target row is not empty and target is below row in question, move target up
	}
	if(target_i > i) {  // if target is below cell in question
	  cur_game->cells[target_i*cols + j] = cur_game->cells[i*cols + j];  // move cell in question to target row
	  cur_game->cells[i*cols + j] = -1;  // cell in row of question is set to empty
	  val = 1; // return value is set to 1
	}
      }
    }
  }
  for(int p = 0; p < cols; p++) {  // loop through each column
    merge = rows-1;  // set merge to lowest row in column
    for(int q = rows-2; q >= 0; q--) {  // loop through each row form bottom to top of column
      // if cell in question and cell below have same value, cell below can be merged, and cells are not empty
      if(cur_game->cells[q*cols + p] == cur_game->cells[(q + 1)*cols + p] && (q + 1) <= merge && cur_game->cells[q*cols + p] != -1) {
	cur_game->cells[(q + 1)*cols + p] += cur_game->cells[q*cols + p];  // merge cells
	cur_game->cells[q*cols + p] = -1;  // set cell in question to empty
	cur_game->score += cur_game->cells[(q + 1)*cols + p];  // increase score
	merge = q;  // set merge to row in question so as to not merge the row below again
	val = 1;  // set return value to 1       
      }
    }
  }
  for(int a = 0; a < cols; a++) {  // loop through each column
    target_i = rows - 1;  // set target row to lowest row 
    for(int b = rows - 2; b >= 0; b--) {  // loop through each row in column
      if(cur_game->cells[b*cols + a] != -1) {  // if cell is not empty
	while(cur_game->cells[target_i*cols + a] != -1 && (target_i > b)) {
	  --target_i;  // while target cell is not empty and target cell is below cell in question, decrease target
	}
	if(target_i > b) {  // if target cell is below cell in question
	  cur_game->cells[target_i*cols + a] = cur_game->cells[b*cols + a];  // move cell to target cell
	  cur_game->cells[b*cols + a] = -1;  // set cell that moved to empty
	  val = 1;  // set return value to 1
	}
      }
    }
  }
  return val;
};

int move_a(game * cur_game) //slide left
{
    //YOUR CODE STARTS HERE
  int target_j;
  int merge;
  int cols = cur_game->cols;
  int rows = cur_game->rows;
  int val = 0;
  for(int i = 0; i < rows; i++) {  // loop through each row
    target_j = 0;
    for(int j = 1; j < cols; j++) {  // loop through each column
      if(cur_game->cells[i*cols + j] != -1) {  // if cell is not empty
	while(cur_game->cells[i*cols + target_j] != -1 && target_j < j) {
	  ++target_j;  // while the target cell is not empty and the target cell is more left than cell in question, increase target
	}
	if(target_j < j) { // if target is more left than cell
	  cur_game->cells[i*cols + target_j] = cur_game->cells[i*cols + j];  // move cell to target
	  cur_game->cells[i*cols + j] = -1;  // cell moved is set to empty
	  val = 1;  // return value is 1
	}
      }
    }
  }
  for(int q = 0; q < rows; q++) {  // loop through each row
    merge = 0;
    for(int p = 1; p < cols; p++) {  // loop through each column
      // if cell to left of cell in question and cell in question share same value, cell to left hasn't merged yet, and cells arent empty
      if(cur_game->cells[q*cols + p] == cur_game->cells[q*cols + p-1] && (p - 1) >= merge && cur_game->cells[q*cols + p] != -1) {
	cur_game->cells[q*cols + p-1] += cur_game->cells[q*cols + p];  // merge cells
	cur_game->cells[q*cols + p] = -1;  // set the cell in question to empty
	cur_game->score += cur_game->cells[q*cols + p-1];  // increase score
	merge = p;  // set merge to cell in question so as to not merge the cell to the left again
	val = 1;  // return value is set to 1
       
      }
    }
  }
  for(int b = 0; b < rows; b++) {  // loop through each row
    target_j = 0;
    for(int a = 0; a < cols; a++) {  // loop through each column
      if(cur_game->cells[b*cols + a] != -1) {  // if cell is not empty
	while(cur_game->cells[b*cols + target_j] != -1 && (target_j < a)) {
	  ++target_j;  // while the target cell is not empty and the target is more left, increase target
	}
	if(target_j < a) {  // if target is more left than our cell
	  cur_game->cells[b*cols + target_j] = cur_game->cells[b*cols + a];  // move cell to target
	  cur_game->cells[b*cols + a] = -1;  // old cell is set to empty
	  val = 1; // return value is 1
	}
      }
    }
  }
  return val;
};

int move_d(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE
 int target_j;
  int merge;
  int cols = cur_game->cols;
  int rows = cur_game->rows;
  int val = 0;
  for(int i = 0; i < rows; i++) {  // loop through each row
    target_j = cols-1;
    for(int j = cols-2; j >= 0; j--) {  // loop through each column from right to left
      if(cur_game->cells[i*cols + j] != -1) {  // if cell is not empty
	while(cur_game->cells[i*cols + target_j] != -1 && target_j > j) {
	  --target_j;  // while target cell is not empty and target cell is more right, move target cell to the right
	}
	if(target_j > j) {  // if target is more right than cell
	  cur_game->cells[i*cols + target_j] = cur_game->cells[i*cols + j];  // move cell to target
	  cur_game->cells[i*cols + j] = -1;  // set old cell to empty
	  val = 1;  // return value set to 1	 
	}
      }
    }
  }
  for(int q = 0; q < rows; q++) {  // loop through every row
    merge = cols-1;
    for(int p = cols-2; p >= 0; p--) {  // loop through each column from right to left
      // if cell in question and cell to the right of it have same value, cell to the right is able to merge, and cells are not empty
      if(cur_game->cells[q*cols + p] == cur_game->cells[q*cols + p+1] && (p + 1) <= merge && cur_game->cells[q*cols + p] != -1) {
	cur_game->cells[q*cols + p+1] += cur_game->cells[q*cols + p];  // merge cells
	cur_game->cells[q*cols + p] = -1;  // set cell in question to empty
	cur_game->score += cur_game->cells[q*cols + p+1];  // update score
	merge = p;  // set merge to cell in question so as to not merge the cell to the right again
	val = 1;  // set return value to 1
      }
    }
  }
  for(int b = 0; b < rows; b++) { // loop through each row
    target_j = cols-1;
    for(int a = cols-2; a >= 0; a--) {  // loop through each column from right to left
      if(cur_game->cells[b*cols + a] != -1) {  // if cell is not empty
	while(cur_game->cells[b*cols + target_j] != -1 && (target_j > a)) {  
	  --target_j;  // while target cell is not empty and target is more right than cell, decrease target
	}
	if(target_j > a) {  // if target is more right than cell
	  cur_game->cells[b*cols + target_j] = cur_game->cells[b*cols + a];  // move cell to target
	  cur_game->cells[b*cols + a] = -1;  // set old cell to empty
	  val = 1;  // set return value to 1
	}
      }
    }
  }
  return val;
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    //YOUR CODE STARTS HERE
  int rows = cur_game->rows;
  int cols = cur_game->cols;
  for(int i = 0; i < rows; i++) { // loop through rows and columns
    for(int j = 0; j < cols; j++) {
      if(cur_game->cells[i*cols + j] == -1){  // if a cell is empty
	return 1;  // there is possible legal move
      }
      if(cur_game->cells[i*cols + j] == cur_game->cells[i*cols + j + 1] && j+1 < cols) {  // if cells can merge left to right or right to left
	return 1;  // there is possible legal move
      }
      if(cur_game->cells[i*cols + j] == cur_game->cells[(i+1)*cols + j] && i+1 < rows) {  // if cells can merge top to bottom or bottom to top
	return 1;  // there is possible legal move
      }
    }
  }
  return 0;  // otherwise no legal moves
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
