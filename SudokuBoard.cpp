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
class SudokuBoard 
{
  private:
	int boardSize;												// Size of the board
	matrix<int> sdkMatrix;										// Sudoku Matrix 
	matrix<int> row_conflicts;									// Row Conflict Matrix
	matrix<int> col_conflicts;									// Column Conflict Matrix
	matrix<int> sqr_conflicts;									// Square Conflict Matrix
	int calcSquare(int row, int col);							// Calculates square based on idices
	void updateBoard(int row, int col, int val);			    // Updates conflicts and available on insertion
	vector<int> bestAvailable();								// Finds the most constrained cell
	int calcNumConstraint(int row, int col);					// Finds the number of constraints on a cell
	vector<int> validNums(int row, int col);					// Determines if a placement is legal
	bool isBoardDone();											// Checks whether the board is complete or unsolvable
	bool isValidCell(int row, int col);							// Checks whether anything can be placed at a cell
	void addConflict(int row, int num, int val);



	
  public:
	SudokuBoard(int N = 9);										// Constructor
	void clearBoard();											// Clears the board
	void initializeBoard(ifstream &fin);						// Sets up the board based on a text file
	bool solveSudoku();											// Solves the board
	void printSudoku();											// Prints the board
};


/* Constructor to initialize data */
SudokuBoard::SudokuBoard(int N) : boardSize(N)
{	
	// Resize conflict matricies
	sdkMatrix.resize(N, N);
	row_conflicts.resize(N,boardSize);
	col_conflicts.resize(N,boardSize);
	sqr_conflicts.resize(N,boardSize);
	clearBoard();
}


/* Read a Sudoku board from the input file. */
void SudokuBoard::initializeBoard(ifstream &fin)
{
   int digit;
   char ch;			// holds each value read from file
   clearBoard();	// clear the board first
   int square;
   // filling in sudoku board and inserting conflicts
   for (int i = 0; i < boardSize; i++)
   {
        for (int j = 0; j < boardSize; j++)
	    {
	        fin >> ch;
            // If the read char is not Blank
			if (ch != '.') 
			{
				digit = ch-'0';// Convert char to int
				sdkMatrix[i][j] = digit;
				square = calcSquare(i, j);
				row_conflicts[i][digit - 1] = 1;
				col_conflicts[j][digit - 1] = 1;
				sqr_conflicts[square][digit - 1] = 1;
		  	}
        }
   }
}


//Calculates current square based on indices
int SudokuBoard::calcSquare(int row, int col)
{
	if(row < SquareSize)
	{
		if(col < SquareSize)
		{
			return 0;
		}
		else if((col >= SquareSize) && (col < (SquareSize * 2)))
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	else if((row >= SquareSize) && (row < (SquareSize * 2)))
	{
		if(col < SquareSize)
		{
			return 3;
		}
		else if((col >= SquareSize) && (col < (SquareSize * 2)))
		{
			return 4;
		}
		else
		{
			return 5;
		}
	}
	else
	{
		if(col < SquareSize)
		{
			return 6;
		}
		else if((col >= SquareSize) && (col < (SquareSize * 2)))
		{
			return 7;
		}
		else
		{
			return 8;
		}
	}
}


/* Clear the puzzle by setting every cell to Blank = 0 and reset conflict matrices */
void SudokuBoard::clearBoard()
{
   for (int i = 0; i < boardSize; i++)
      for (int j = 0; j < boardSize; j++)
      {
      	sdkMatrix[i][j] = Blank;
		row_conflicts[i][j] = 0;
		col_conflicts[i][j] = 0;
		sqr_conflicts[i][j] = 0;
      }
}


// Updates the conflict vectors given the index and the inserted value
void SudokuBoard::updateBoard(int row, int col, int val)
{
	int prevVal = sdkMatrix[row][col];
	sdkMatrix[row][col] = val;
	int sqr = calcSquare(row, col);
	if(val != 0)
	{
		row_conflicts[row][val - 1] = 1;
		col_conflicts[col][val - 1] = 1;
		sqr_conflicts[sqr][val - 1] = 1;
	}
	else
	{
		row_conflicts[row][prevVal - 1] = 0;
		col_conflicts[col][prevVal - 1] = 0;
		sqr_conflicts[sqr][prevVal - 1] = 0;
	}
}


// Looks through the matrix and finds the most constrained available index
vector<int> SudokuBoard::bestAvailable()
{
	vector<int> bestIndex;
	bestIndex.push_back(0);
	bestIndex.push_back(0);
	int numConstraints;
	int maxConstraint = 0;
	for(int row = 0; row < boardSize; row++)
	{
		for(int col = 0; col < boardSize; col++)
		{
			numConstraints = calcNumConstraint(row, col);
			if(numConstraints > maxConstraint)
			{
				bestIndex.clear();
				bestIndex[0] = row;
				bestIndex[1] = col;
			}
		}
	}
	return bestIndex;
}


// Finds the number of constraints on a given cell
int SudokuBoard::calcNumConstraint(int row, int col)
{
	int num_constraints = 0;
	int sqr = calcSquare(row, col);
	for(int i = 0; i < boardSize; i++)
	{
		num_constraints += row_conflicts[row][i] + col_conflicts[col][i] + sqr_conflicts[sqr][i];
	}
	return num_constraints;
}


// Determines possible numbers at a cell
vector<int> SudokuBoard::validNums(int row, int col)
{
	vector<int> valid;
	int sqr = calcSquare(row, col);
	for(int i = 0; i < boardSize; i++)
	{
		if((row_conflicts[row][i] ==  0) && (col_conflicts[col][i] == 0) && (sqr_conflicts[sqr][i] == 0))
		{
			valid.push_back(i+1);
		}
	}
	return valid;
}


// Determines if a cell is valid
bool SudokuBoard::isValidCell(int row, int col)
{
	int sqr = calcSquare(row, col);
	for(int i = 0; i < boardSize; i++)
	{
		if((row_conflicts[row][i] ==  0) && (col_conflicts[col][i] == 0) && (sqr_conflicts[sqr][i] == 0) && (sdkMatrix[row][col] == 0))
		{
			return true;
		}
	}
	return false;
}

// Determines if board is solved or unsolvable
bool SudokuBoard::isBoardDone()
{
	for(int row = 0; row < boardSize; row++)
	{
		for(int col = 0; col < boardSize; col++)
		{
			if(isValidCell(row, col))
			{
				return false;
			}
		}
	}
	return true;
}

void SudokuBoard::addConflict(int row, int col, int val)
{
	int sqr = calcSquare(row, col);
	row_conflicts[row][val - 1] = 1;
	col_conflicts[col][val - 1] = 1;
	sqr_conflicts[sqr][val - 1] = 1;
}

/* Recursive function to solve the sudoku puzzle.  */
bool SudokuBoard::solveSudoku() 
{
	cout << "8-- 1" << endl;
	if(isBoardDone())
	{
		cout << "8-- 2" << endl;
		for(int row = 0; row < boardSize; row++)
		{
			for(int col = 0; col < boardSize; col++)
			{
				cout << "8-- 3" << endl;
				if(sdkMatrix[row][col] == 0)
				{
					cout << "8-- 4" << endl;
					return false;
				}
			}
		}
		cout << "8-- 5" << endl;
		return true;
	}
	else
	{
		cout << "8-- 6" << endl;
		vector<int> index = bestAvailable();
		cout << "8-- 7" << endl;
		cout << index[0] << ", " << index[1] << endl;
		int row = index[0];
		int col = index[1];
		vector<int> numberChoices = validNums(row, col);
		cout << numberChoices.size() << endl;
		cout << "8-- 8" << endl;
		for(int i = 0; i < numberChoices.size(); i++)
		{
			cout << "8-- 9" << endl;
			if(isValidCell(row, col))
			{
				cout << "8-- 10" << endl;
				updateBoard(row, col, numberChoices[i]);
				cout << "8-- 11" << endl;
				printSudoku();
				addConflict(row, col, numberChoices[i]);
				cout << "Pre Recursive Call" << endl;
				bool valid = solveSudoku();
				cout << "Post Recursive Call" << endl;
				if(valid)
				{
					cout << "8-- 12" << endl;
					return true;
					cout << "8-- 13" << endl;
				}
				else
				{
					cout << "8-- 14" << endl;
					if(sdkMatrix[row][col] != 0)
					{
						cout << "8-- 15" << endl;
						updateBoard(row, col, 0);
						printSudoku();
					}
					return solveSudoku();
				}
			}
		}
		return false;
	}
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
	fin.open("Sudoku1.txt");
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
			cout << "\nComplete Solution Found." << endl;	
			cout << "\nCompleted board ..." << endl;
			sdk->printSudoku();
			/*  Print completed board */
			/*  print the conflicts */
			/*  print # of recursive calls */
			/*  print # of backtrack calls */
			
			// If no solution found, print out the incomplete sudoku
		} else {
			cout << "\nNo Solution Found...!" << endl;
			cout << "\nIncomplete board ..." << endl;
			sdk->printSudoku();
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