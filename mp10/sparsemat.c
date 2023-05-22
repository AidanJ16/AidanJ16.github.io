#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>

// INTRO PARAGRAPH
// For this mp we had to implement the following functions
// The first was load_tuples, which should open a file and read data from it
// The data from the file is used to create a matrix of list of tuples type with elements ordered
// The second was gv_tuples which returns the valueof the element at a given row an dcolumn within the matrix
// The third was set_tuples which sets the element at the given row and column to the given value
// This function needed to be able to handle three cases:
// The first case is the value is 0: if the entry exits the node must be deleted
// The second case is if for any other value the entry exists: new value must replace the old one
// The third case is if for any other value the entry doesn't exist: new node must be created and inserted at the correct location
// Also need to update the 'nz' variable of our structure
// The fourth was save_tuples which writes the data in a sparse matrix to a text file
// The fifth was add_tuples which adds two sparse matrices and stores the sum in a matrix to be returned
// I implemented a method to add only the non-zero elements of the two matrices so as to perform the addition efficiently
// The sixth was destroy_tuples which freed all memory associeted with a given matrix

void delete(sp_tuples *, int, int);
 
sp_tuples * load_tuples(char* input_file)
{
  // set up variables in use for this function
  int rows, cols;
  double val;
  FILE *file;
  sp_tuples * matrix = (sp_tuples *) malloc(sizeof(sp_tuples));
  // open the file to read the matrix data from it
  file = fopen(input_file, "r");
  // scan the number of rows and cols
  fscanf(file, "%d %d\n", &rows, &cols);

  // set our matrix rows, cols, nz value, and head pointer
  matrix->m = rows;
  matrix->n = cols;
  matrix->nz = 0;
  matrix->tuples_head = NULL;
  
  // iterate through the file scanning the row, col, and value of each node
  // call our set_tuples function to manipulate our matrix based on the data from file
  while(fscanf(file, "%d %d %lf\n", &rows, &cols, &val) == 3) {
    set_tuples(matrix, rows, cols, val);
  }
  // close file
  fclose(file);
  return matrix;
}



double gv_tuples(sp_tuples * mat_t,int row,int col)

{
  // set up a node pointer to the head of our list
 sp_tuples_node * curr = NULL;
 curr = mat_t->tuples_head;
 // iterate through list until we found the node with the corresponding
 // row and col, return the node's value
 while(curr != NULL) {
   if(curr->row == row && curr->col == col) {
     return curr->value;
   }
   curr = curr->next;
 }
 // if no node found, value must be 0
 return 0;
}

// helper function to delete nodes in a linked list
void delete(sp_tuples * mat_t, int row, int col) {
  // create our current and tmp pointer
  sp_tuples_node * curr = NULL;
  curr = mat_t->tuples_head;

  // if matrix is empty nothing to delete
  if(curr == NULL) {
    return;
  }

  // if need to delete head, change head pointer to next node even if NULL
  // decrement counter as a node was deleted
  if(curr->row == row && curr->col == col) {
    sp_tuples_node * temp = curr;
    curr = curr->next;
    mat_t->nz --;
    free(temp);
    return;
  }
  // else find the node that corresponds to the given row and col
  while(curr != NULL) {
    // if at tail, couldn't find the node given so nothing to delete
    if(curr->next == NULL) {
      break;
    }
    // if node found in middle, we change previous nodes pointer to next node
    if(curr->next->row == row && curr->next->col == col) {
      sp_tuples_node * temp = curr->next;
      curr->next = temp->next;
      free(temp);
      mat_t->nz --;
      return;
    }
    // iterate to next node
    curr = curr->next;
  }
  return;
}

void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
  // if value is 0 call helper function delete
  if(value == 0) {
    delete(mat_t, row, col);
    return;
  }
  // for any other value set up a pointer to the head of our list
  // create temp storage for node (to be added)
  sp_tuples_node * curr = NULL;
  curr = mat_t->tuples_head;
  sp_tuples_node * tmp = (sp_tuples_node*) malloc(sizeof(sp_tuples_node));
  
  // adding node so increment counter
  // set up our node to be added with row, col, and value
  mat_t->nz++;
  tmp->row = row;
  tmp->col = col;
  tmp->value = value;
  // if list is empty add the node right after head 
  if(curr == NULL) {
    mat_t->tuples_head = tmp;
    tmp->next = NULL;
    return;
  }
  // if value is before head add it
  if(curr->row > row || (curr->row == row && curr->col > col)) {
    tmp->next = curr;
    mat_t->tuples_head = tmp;
    return;
  }
  // iterate through list
  while(curr != NULL) {
    // if node already exists change value and decrement counter since no node was added
    if(curr->row == row && curr->col == col) {
      curr->value = value;
      free(tmp);
      mat_t->nz--;
      return;
    }
    // if at tail set tail next pointer to new node and set new node next pointer to NULL
    if(curr->next == NULL) {
      curr->next = tmp;
      tmp->next = NULL;
      return;
    }
    // if in middle add it by changing previous next pointer to new node and new node next pointer to following node
    if(curr->next->row > row || (curr->next->row == row && curr->next->col > col)) {
      tmp->next = curr->next;
      curr->next = tmp;
      return;
    }
    // else iterate to next node
    curr = curr->next;
  }

  return;
}



void save_tuples(char * file_name, sp_tuples * mat_t)
{
  // open file to write to
  // set up pointer to head of list
 FILE * file = fopen("file_name", "w");
 sp_tuples_node * curr = NULL;
 curr = mat_t->tuples_head;
 // write the number of rows and columns to file
 fprintf(file, "%d %d\n", mat_t->m, mat_t->n);
 // iterate through the list while writing the row, col, and value to the file
 for(int i = 0; i < mat_t->nz; i++) {
   fprintf(file, "%d %d %lf\n", curr->row, curr->col, curr->value);
   curr = curr->next;
 }
 // close file
 fclose(file);
 return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){
  // set up variables for the function
  // including a double value, return matrix, and pointers to the heads of the given lists
  double val;
  sp_tuples * retmat = (sp_tuples *)malloc(sizeof(sp_tuples));
  sp_tuples_node * nodeA = NULL;
  nodeA = matA->tuples_head;
  sp_tuples_node * nodeB = NULL;
  nodeB = matB->tuples_head;

  // fill in the number of rows and columns, the nz, and the head pointer of return matrix
  retmat->m = matA->m;
  retmat->n = matA->n;
  retmat->nz = 0;
  retmat->tuples_head = NULL;
  // iterate through first list copying all nodes in matA to return matrix
  while(nodeA != NULL) {
    set_tuples(retmat, nodeA->row, nodeA->col, nodeA->value);
    nodeA = nodeA->next;
  }
  // iterate through second list copying all nodes in matB to return matrix
  // use gv_tuples to calculate the old value at a given row and col and update it
  // to the sum of that value and the value at the given row and col of matB
  while(nodeB != NULL) {
    val = gv_tuples(retmat, nodeB->row, nodeB->col);
    set_tuples(retmat, nodeB->row, nodeB->col, nodeB->value + val);
    nodeB = nodeB->next;
  }
  // return matrix
  return retmat;
}



//sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ 
//return retmat;

//}


	
void destroy_tuples(sp_tuples * mat_t){
  // set up pointer to matrix head and temp pointer for destroying nodes
  sp_tuples_node * curr = NULL;
  curr = mat_t->tuples_head;
  sp_tuples_node * tmp = NULL;
  // iterate through list saving next node to tmp and freeing the current node
  while(curr != NULL) {
    tmp = curr->next;
    free(curr);
    curr = tmp;
  }
  // free matrix structure
  free(mat_t);
  return;
}  






