#include <iostream>
#include <cstdio>
#include "sudoku.h"
#include<stdlib.h>
using namespace std;


/*This function uses functions defined in sudoku.h to solve the sudoku boards defined
in the sudoku solver dat files*/
int main() {

  char board[9][9];

  cout << "====================== Part 1 ======================" << endl << endl;

  /*Testing the function to see if a sudoku board is already solved*/
  load_board("easy.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << endl << endl;

  load_board("easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << endl << endl;
  
  cout << "====================== Part 2 ======================" << endl << endl;

  /*Testing the function that checks is a moves on a sudoku board is allowed*/
  load_board("easy.dat", board);

  // Should be OK
  cout << "Putting '1' into I8 is ";
  if (!make_move("I8", '1', board)) 
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);
  
  cout << "====================== Part 3 ======================" << endl << endl;

  /*Testing function that saves a sudoku board to another file*/
  load_board("easy.dat", board);
  if (save_board("easy-copy.dat", board))
    cout << "Save board to 'easy-copy.dat' successful." << endl;
  else
    cout << "Save board failed." << endl;
  cout << endl;
  
  cout << "====================== Part 4 ======================" << endl << endl;
  
  /*Testing function that solves a sudoku board*/
  //easy sudoku board
  load_board("easy.dat", board);
  if (solve_board(board)) {
    cout << "The 'easy' board has a solution:" << endl;
    display_board(board);
  } else 
    cout << "A solution cannot be found." << endl;
   
  //medium sudoku board
    load_board("medium.dat", board);
  if (solve_board(board)) {
    cout << "The 'medium' board has a solution:" << endl;
    display_board(board);
  } else 
    cout << "A solution cannot be found." << endl;
  cout << endl;
 
  //Mystery sudoku boards
  load_board("mystery1.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery1' board has a solution:" << endl;
    display_board(board);
  } else
    cout << "A solution cannot be found." << endl;
  cout << endl;
  
  load_board("mystery2.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery2' board has a solution:" << endl;
    display_board(board);
  } else
    cout << "A solution cannot be found." << endl;
  cout << endl;

  load_board("mystery3.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery3' board has a solution:" << endl;
    display_board(board);
  } else
    cout << "A solution cannot be found." << endl;
  cout << endl;
  
  return 0;
  
}
