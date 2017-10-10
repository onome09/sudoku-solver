
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"


using namespace std;


/* function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {
  
  cout << "Loading Sudoku board from file '" << filename << "'... ";
  
  ifstream in(filename);
  if (!in)
    cout << "Failed!" << endl;
  assert(in);
  
  char buffer[512];
  
  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << endl;
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3))
    cout << "  +===========+===========+===========+" << endl;
  else
    cout << "  +---+---+---+---+---+---+---+---+---+" << endl;
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << endl;
}

/* function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) 
    cout << (char) ('1'+r) << "   ";
  cout << endl;
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/*THIS FUNCTION RETURNS TRUE IF THE SUDOKU BOARD IS COMPLETE AND FALSE OTHERWISE*/
bool is_complete(const char board[9][9])
{
  for (int row_index = 0; row_index < 9; row_index++)
    {
      for(int column_index = 0; column_index < 9; column_index++)
	{
	  if (is_blank(row_index, column_index, board))// check for any blank squares 
	    return false;
	}     
    }
  return true;// no blank spaces found
}
/*END OF FUNCTION*/

/* This function checks if a given digit can be placed in a specified square and if true it returns true and places the digit in the square and returns false otherwise 
   The function operates by using individual functions that logically check the validity of the move according to each of the sudoku rules */
bool make_move(const char* position, char digit, char board[9][9])
{
  int row_index, column_index; // declaration of board coordinates
  bool possible_move, legal_move; // boolean variables that say whether a move is possible and whether it is allowed
  row_index = letter_to_index(position[0]);
  column_index = number_to_index(position[1]);
  
  possible_move = (coordinates_check(row_index, column_index) && is_blank(row_index, column_index, board)); // validity checks according to state of the board
  legal_move = (row_check(row_index, digit, board) && column_check(column_index, digit, board) && box_check(row_index, column_index, digit, board)); // validity checks according to the rules of sudoku
  
  if (possible_move && legal_move) // determine if all validity checks have been satisfied and if so place the digit on the sudoku board and return true
    { 
      board[row_index][column_index] = digit;      
      return true;
    }
  return false;
}

/* This Function that solves a 9 by 9 sudoku board. Returns true if there is a solution and false otherwise */
bool solve_board(char board[9][9])
{
  char position[2];
  int row_index, column_index;
  
  if (is_complete(board)) // check if all the board is complete in which case the function should cease                                      
    {
      return true;
    }
  else
    {
      move_to_blank_space(board, row_index, column_index, position);// find new blank square using the function move_to_blank_space(...) and update the coordinates.
      
      for (char digit = '1'; digit <= '9'; digit++)
	{
	  if (make_move(position, digit, board)) //check if move is valid and make the move with that digit.
	    {
	      if (solve_board(board))//check solve_board again but with the new digit already placed in
		return true;
	      else
		board[row_index][column_index] = '.';// digit does not work so reset square to blank again.
	    }
	}
      return false;
    }// no feasible digit found so return false so it goes to the previous digit testing on the blank square before. If there is no previous blank square and all the digits from 1 to 9 have been tried on it then the function returns false and there is no solution. 
}
/* End of function */

/* This function saves a sudoku board that is described as a 9 by 9 character array to the file (filename) */
bool save_board(const char* filename, const char board[9][9])
{
  char character;
  ofstream out; 

  out.open(filename);//open file with the name (filename) 
  if (out.fail()) 
    return false;

  for (int row_index = 0; row_index < 9; row_index++)// loop to copy each charater from the board array to the file.
    {
      for(int column_index = 0; column_index < 9; column_index++)
        {
          character = board[row_index][column_index];
          out.put(character);
        }
      out.put('\n');
    }
  out.close();
  return true;
}
/* End of function */

/* This function adjusts the values of row_index, column index and position coordinates to the next blank square on the sudoku board */
void move_to_blank_space(const char board[9][9], int &row_index, int &column_index, char *position)
{
  for (int i = 0; i < 9; i++)
    {
      for (int j = 0; j < 9; j++)
        {
          if (is_blank(i,j,board))
            {
              row_index = i;
              column_index = j;
	      position[0] = index_to_letter(i);
	      position[1] = index_to_number(j);
              return;
            }
        }
    }
}
/* End of function */

/* VALID MOVE CHECKING FUNCTIONS *******************************************************************************/
/* These function are to check the validity of placing a given digit in a given square. */

/*Function to determine if the digit to be placed already exists in the row it is to be placed in*/
bool row_check(int row_index, char digit, const char board[9][9])
{
  for(int column_index = 0; column_index < 9; column_index++)
    {
      if (board[row_index][column_index] == digit)
	return false;
    }     
  return true;
}
/*End of function*/

/*Function to determine if the digit to be placed already exists in the column it is to be placed in*/
bool column_check(int column_index, char digit, const char board[9][9])
{
  for(int row_index = 0; row_index < 9; row_index++)
    {
      if (board[row_index][column_index] == digit)
        return false;
    }
  return true;
}
/*End of function*/

/*Function to determine if the digit to be placed already exists in the 3 by 3 box it is to be placed in*/
bool box_check(int row_index, int column_index, char digit, const char board[9][9])
{
  int row_start, row_end, column_start, column_end;
  //First half of the function determines coordinates of the 3 by 3 box to inspect*/
  row_start = (row_index / 3) * 3;
  row_end = row_start + 3;
  column_start = (column_index / 3) * 3;
  column_end = column_start + 3;
 
  // begin checking the 3 by 3 box for a copy of the digit and return true is no copy is found
  for (row_index = row_start; row_index < row_end; row_index++)
    {
      for (column_index = column_start; column_index < column_end; column_index++)
	{
	  if (board[row_index][column_index] == digit)
	    return false;
	}     
    }
  return true;
}
/*End of function*/

/* This function checks that the coordinates specified are within the range of the sudoku board */
bool coordinates_check(int row_index, int column_index)
{
  return !(row_index > 8 || column_index > 8 || row_index < 0 ||column_index < 0);
}
/* End of function */

/* This function checks that the coordinates specified correspond to a blank space on the sudoku board */ 
bool is_blank(int row_index, int column_index, const char board[9][9])
{
  return (board[row_index][column_index] == '.');
}
/* End of function */
/********************************************************************************************************/

/* CONVERTING FUNCTIONS *********************************************************************************/

/*These functions are to convert from the character letters or number function converts from a letter coordinate to a nummerical coordinate integer to be used as its corresponding index on the sudoku board array by incrementing or decrementing the required amount according to the ascii table*/

int letter_to_index(char character)
{
  return (character - 65);
}
int number_to_index(char character)
{
  return (character - 49);
}
char index_to_letter(int number)
{
  return (number + 65);
}
char index_to_number(int number)
{
  return (number + 49);
}
/* End of functions */
/********************************************************************************************************/


