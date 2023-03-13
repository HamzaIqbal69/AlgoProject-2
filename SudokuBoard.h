#include <iostream>
#include <cstdlib>
#include "d_matrix-1.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
const int Blank = 0; // Indicates that a cell is blank
const int SquareSize = 3; // Size of small squares
/*
* class SudokuBoard to solve sudoku puzzles
* The class is incomplete
*/
class SudokuBoard 
{
    private:
        int boardSize; // Size of the board
        matrix<int> sdkMatrix; // Sudoku Matrix
    public:
        SudokuBoard(int N = 9); // Constructor
        void clearBoard();
        void initializeBoard(ifstream &fin);
        bool solveSudoku();
        void printSudoku();
};