/****************************************************************************
* author          : EECE 2560 Your name here
* Date            : February 20, 2023
* File name       : SodukoBoard.cpp  - Solve Sudoku Puzzles using 
*				  : recursive algorithms
* Purpose         : Reads in a puzzle of more from a files and solves them
* Usage			  : g++ SudokuBoard.cpp -o output
*				  : ./output    (No Makefile required)
 ****************************************************************************/
#include <iostream>
#include <cstdlib>
#include "d_matrix-1.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

const int Blank = 0;  		// Indicates that a cell is blank
const int SquareSize = 3;	// Size of small squares

/*
*  	class SudokuBoard to solve sudoku puzzles
*   The class is incomplete
*/
class SudokuBoard {
  private:
	int boardSize;			// Size of the board
	matrix<int> sdkMatrix;	// Sudoku Matrix 
	
  public:
	SudokuBoard(int N = 9);		// Constructor
	void clearBoard();	
	void initializeBoard(ifstream &fin);
	bool solveSudoku();
	void printSudoku();
};

/* Constructor to initialize data */
SudokuBoard::SudokuBoard(int N) : boardSize(N)
{	
	// Resize conflict matricies
	sdkMatrix.resize(N, N);
	clearBoard();
}
/* Read a Sudoku board from the input file. */
void SudokuBoard::initializeBoard(ifstream &fin)
{
   int digit;
   char ch;			// holds each value read from file
   clearBoard();	// clear the board first
   for (int i = 0; i < boardSize; i++)
   {
      for (int j = 0; j < boardSize; j++)
	    {
	       fin >> ch;
          // If the read char is not Blank
			if (ch != '.') {
				digit = ch-'0';// Convert char to int
				sdkMatrix[i][j] = digit; 
		  }
        }
   }
}

/* Clear the puzzle by setting every cell to Blank = 0 */
void SudokuBoard::clearBoard()
{
   for (int i = 0; i < boardSize; i++)
      for (int j = 0; j < boardSize; j++)
      {
         sdkMatrix[i][j] = Blank;
      }
}

/* Recursive function to solve the sudoku puzzle.  */
bool SudokuBoard::solveSudoku() {
	//***** To be completed ************
	// returns true if solution found, otherwise, false
    return false;
}


/* Prints the current board */
void SudokuBoard::printSudoku()
{
	for (int i = 1; i <= boardSize; i++)
	{
		if ((i-1) % SquareSize == 0)
		{
			for (int j = 1; j <= boardSize+1; j++)
				cout << "---";
			cout << endl;
		}
		for (int j = 1; j < boardSize+1; j++)
		{
			if ((j-1) % SquareSize == 0)
				cout << "|";
			if (sdkMatrix[i-1][j-1] != Blank)
				cout << " " << sdkMatrix[i-1][j-1] << " ";
			else
				cout << " - ";
		}
		cout << "|";
		cout << endl;
	}
	cout << " -";
	for (int j = 1; j <= boardSize; j++)
		cout << "---";
	cout << "-";
	cout << endl;
}

/*
*  	main() function to solve sudoku puzzles from a file
*/
int main() 
{
	int recursiveCount;		// # of recursive calls
	int backtracksCount;	// # of backtracks involved for each board
	int boardCount = 0; 	// # of Boards from file solved
	int boardSize = 9;

	// Create SudokuBoard object
    SudokuBoard *sdk = new SudokuBoard(boardSize);
	
	// Open the data file and verify it opens successfully
	ifstream fin;
	fin.open("Sudoku3Puzzles.txt");
	if (!fin)
	{
		cerr << "Cannot open 'sudoku1.txt'" << endl;
		exit(1);
	}

	// Each iterations solves a NEW board from the input file
	while (fin && fin.peek() != 'Z') {
		recursiveCount = 0;		// Reset # of recursive calls 
		backtracksCount = 0;	// Reset # of backtrack calls
		boardCount++;			// New board to be solved
		// Initialize sudoku matrix
		sdk->initializeBoard(fin);  	// reads Sudoku from file
		
		// Print sudoku
		cout <<"\n*****  NEW SUDOKU PUZZLE... ******"  << endl;
		sdk->printSudoku(); // print the board on the terminal

		
		// ********  Evaluate and print conflicts *****

		// If found, print out the resulting solution and final conflicts
		if (sdk->solveSudoku()) {
			// Print on the terminal
			// cout << "\nComplete Solution Found." << endl;	
			// cout << "\nCompleted board ..." << endl;
			/*  Print completed board */
			/*  print the conflicts */
			/*  print # of recursive calls */
			/*  print # of backtrack calls */
			
			// If no solution found, print out the incomplete sudoku
		} else {
			// cout << "\nNo Solution Found...!" << endl;
			// cout << "\nIncomplete board ..." << endl;
			/*  Print incompleted board */		
		}
	}
	//cout << "Number of boards solved: " << boardCount << endl;
	// ****** Post processing  **********
	// Determine the min, max, and average of the recursives calls and backtract 
	// calls for the boards solved and print this information into the 
	// file as well.
	cout <<"\n*****  Solver Terminating... ******"  << endl;

	fin.close();
	delete sdk;
    return 0;
}