/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */
// INTRO PARAGRAPH
// In updateBoard.c we are implementing three functions
// The first function is countLiveNeighbor in which we count the number of alive neighbors for a cell
// To check each neighbor of a cell, we need to check each cell in the row above, below, and at the current cell
// while checking each cell in the column to the right, left, and at the current cell
// However we must make sure to not check the cell we are inspecting
// Thus we must iterate through the row below the cell to the row above the cell, inclusive
// We can then check that the row is on the board
// Then we iterate through the column on the left of the cell to the right of the cell, inclusive
// We can then make sure the column is on the board
// Then as long as the cell is not the one we are inspecting, if that cell is alive we increment our counter
// We then return the count of alive neighboring cells  after analyzing all neighbors
// The second function is updateBoard in which we update the board to the next step changing cells based on:
// live cell stays alive if 2 or 3 live neighbors, otherwise it dies, dead cell turns alive if has exactly 3 alive neighbors
// We implement this function by first copying our current board into an array new_board
// We then iterate through each cell in our board and find the count of live neighbor cells for each cell
// using countLiveNeighbor on new_board
// If the cell is alive and the count is not 2 or 3, then the cell in the original board is changed to dead (0)
// If the cell is dead and the count is 3, then the cell in the original board is changed to alive (1)
// The third function is aliveStable in which we check if the current board stays the same for the next step or not.
// We implement this function by copying our current board into an array next_board
// We then call updateBoard on next_board
// We then iterate through each cell in our board, and compare the original board with the updated board next_board
// If a cell from the original board is not equal to a cell from next_board we return 0
// If all cells are equal, we return 1

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
  int live = 0;  // count of live neighbors
  for(int i = row -1; i <= row +1; i++) { // iterating through row below to row above cell
    if(i >= 0 && i < boardRowSize) {  // ensure row is on board
      for(int j = col - 1; j <= col + 1; j++) {  // iterating through column from left of cell to right of cell
	if(j >= 0 && j < boardColSize) { // ensure column is on board
	  if(i != row || j != col) {  // ensure cell is neighbor and not the cell we are inspecting
	    if(board[i*boardColSize + j] == 1) { // if cell is alive increment counter
	      live ++;
	    }
	  }
	}
      }
    }
  }
  return live; // return count of alive neighbors
}
/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
  int live_count = 0;  // count of alive neighbors
  int board_size = boardRowSize*boardColSize; // board size
  int new_board[board_size]; // copy of board
  for(int p = 0; p < board_size; p ++){  // hard copying board to new_board
    new_board[p] = board[p];
  }
  for(int i = 0; i < boardRowSize; i++){  // iterating through all rows of board
    for(int j = 0; j < boardColSize; j++){  // iterating through all columns of board
      live_count = countLiveNeighbor(new_board, boardRowSize, boardColSize, i, j);  // find count of alive neighbors of cell
      if(new_board[i*boardColSize + j] == 1) {  // if cell is alive and does not have 2 or 3 alive neighbors, cell changes to dead
	if(live_count != 2 && live_count != 3) {
	  board[i*boardColSize + j] = 0;
	}
      }
      if(new_board[i*boardColSize + j] == 0) {  // if cell is dead and has exactly 3 alive neighbors, cell changes to alive
	if(live_count == 3) {
	  board[i*boardColSize + j] = 1;
	}
      }
    }
  }
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
  int board_size = boardRowSize * boardColSize;  // board size
  int next_board[board_size];  // copy of board
  for(int i = 0; i < board_size; i++) {  // copying board to next_board
    next_board[i] = board[i];
  }
  updateBoard(next_board, boardRowSize, boardColSize);  // updating next_board to next state
  for(int i = 0; i < boardRowSize; i++){  // iterating through all rows of board
    for(int j = 0; j < boardColSize; j++){  // iterating through all columns of board
      if(next_board[i*boardColSize + j] != board[i*boardColSize + j]){  // if original board differs from next board return 0
	return 0;
      }
    }
  }
  return 1;  // if original board and next board are the same return 1
}

				
				
			

