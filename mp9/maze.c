#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

// INTRO PRARAGRAPH
// We had to implement 4 functions for this MP
// The first was createMaze which gives us a name of a file containing the maze.
// In this function I had to allocate memory for the maze structure and the cells.
// Then had to parse the file and fill in the parameters of the maze structure including:
// Height, width, start position, end position, and the cells parameter.
// We then return a pointer to the maze structure we've created.
// The second function was destroyMaze that freed all memory associated with the maze.
// The third function was printMaze where given a structure of a maze:
// Had to print maze in human readable format to console
// The last function was solveMazeDFS where we recursively solved the maze using DFS algorithm
// This was done by setting base case as ensuring position was inside bounds of maze and is empty cell
// We then set position as part of solution path and perform recursion for position to the:
// Left, right, up, and down of the original position
// We then mark original position as visited

/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
  FILE *in_file;
  int i, j, height, width;
  char ch;
  maze_t *maze = malloc(sizeof(maze_t));  // create maze pointer and allocate memory space for maze structure
  
  in_file = fopen(fileName, "r");  // open text file containing maze structure

  // find width and height values from file and store them in maze structure
  fscanf(in_file, "%d %d%c", &height, &width, &ch);
  maze->width = width;
  maze->height = height;
  
  maze->cells = (char**) malloc(height*sizeof(char*));  // allocate memory for cells row pointer
  
  for(i = 0; i < height; i++) {
    maze->cells[i] =  malloc(width*sizeof(maze->cells[i]));  // allocate memory for size of each row
    for(j = 0; j < width; j++) {
      // populate each cell with char from file
      fscanf(in_file, "%c", &ch);
      maze->cells[i][j] = ch;
      // if start position set up maze structure
      if(maze->cells[i][j] == START) {
	maze->startRow = i;
	maze->startColumn = j;
      }
      // if end position set up maze structure
      if(maze->cells[i][j] == END) {
	maze->endRow = i;
	maze->endColumn = j;
      }
    }
    // discard newline char at end of row
    fscanf(in_file, "%c", &ch);
  }
  // close file
  fclose(in_file);
  return maze;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
  // free memory for cells
  for(int i = 0; i < maze->height; i++) {
     free(maze->cells[i]);
  }
  // free maze structure
  free(maze->cells);
  free(maze);
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
  // print each cell for each row
  for(int i = 0; i < maze->height; i++) {
    for(int j = 0; j < maze->width; j++) {
      printf("%c", maze->cells[i][j]);
    }
    // print newline for next row of maze
    printf("\n");
  }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
  // base cases: check position is valid and is empty cell
  if(row < 0 || row >= maze->height || col < 0 || col >= maze->width)
    return 0;
  if(maze->cells[row][col] != START && maze->cells[row][col] != END) {
    if(maze->cells[row][col] != EMPTY) {
      return 0;
    }
  }
  // if at end, we are done restore start and return 1
  if(maze->cells[row][col] == END){
    maze->cells[maze->startRow][maze->startColumn] = START;
    return 1;
  }
  // mark position as solution path
  maze->cells[row][col] = PATH;
  // check left, right, up, down, positions recursively
  if (solveMazeDFS(maze, col - 1, row) == 1) {
      return 1;
  }
  if (solveMazeDFS(maze, col + 1, row) == 1) {
      return 1;
  }
  if (solveMazeDFS(maze, col, row - 1) == 1) {
      return 1;
  }
  if (solveMazeDFS(maze, col, row + 1) == 1) {
      return 1;
  }
  // mark cell as visited
  maze->cells[row][col] = VISITED;
  
  return 0;
}
