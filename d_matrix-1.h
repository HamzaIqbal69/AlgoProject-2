/****************************************************************************
* author          :John Kimani
* Date            :February 5, 2023
* File name       :d_matrix.h  - Matrix class header file 
* Purpose         :Declares an interface for the Matrix class providing
*				   data and the necessary operations
 ****************************************************************************/
#ifndef _MATRIX_CLASS
#define _MATRIX_CLASS

/* System Libraries */
#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

template <typename T>
class matrix
{
	private:
      int nRows, nCols;  		// number of rows and columns
      vector<vector<T> > mat; 	// matrix is implemented as Row vectors
								// each having nCols elements (columns)
	public:
		/** constructor.
		*  Postcondition: create array having numRows x numCols elements
		*  all of whose elements have value initVal */
		matrix(int numRows = 1, int numCols = 1, const T& initVal = T());

		/**index operator.
		*  Precondition: 0 <= i < nRows. a violation of this
		*  precondition throws the indexRangeError exception.
		*  Postcondition: if the operator is used on the left-hand
		*  side of an assignment statement, an element of row i 
		*  is changed  */
		vector<T>& operator[] (int i);

		/** version for constant objects  */
		const vector<T>& operator[](int i) const;
			
		/** return number of rows */
		int rows() const;

		/** return number of columns */
		int cols() const;
			
		/** modify the matrix size.
		* Postcondition: the matrix has size numRows x numCols.
		*  any new elements are filled with the default value of type T */
		void resize(int numRows, int numCols);
};

/****************************************************************************
* Purpose         :Implements the Matrix class functions
 ****************************************************************************/

/** constructor.
*  Postcondition: create array having numRows x numCols elements
*  all of whose elements have value initVal 
*/
template <typename T>
matrix<T>::matrix(int numRows, int numCols, const T& initVal):
	nRows(numRows), nCols(numCols),
	mat(numRows, vector<T>(numCols,initVal))
{}

/**index operator.
*  Precondition: 0 <= i < nRows. a violation of this
*  precondition throws the indexRangeError exception.
*  Postcondition: if the operator is used on the left-hand
*  side of an assignment statement, an element of row i 
*  is changed  */
template <typename T>
vector<T>& matrix<T>::operator[] (int i)
{
	if (i < 0 || i >= nRows)
		throw out_of_range (
			"matrix: invalid row index out of bounds");
   
   return mat[i];
}

/**constant version.  can be used with a constant object.
*  does not allow modification of a matrix element
*/
template <typename T>
const vector<T>& matrix<T>::operator[] (int i) const
{
	if (i < 0 || i >= nRows)
		throw out_of_range (
			"matrix: invalid row index out of bounds");

   return mat[i];
}

/** version for constant objects  */
template <typename T>
int matrix<T>::rows() const
{
   return nRows;
}

/** return number of columns */
template <typename T>
int matrix<T>::cols() const
{
   return nCols;
}

/** modify the matrix size.
* Postcondition: the matrix has size numRows x numCols.
*  any new elements are filled with the default value of type T 
*/
template <typename T>
void matrix<T>::resize(int numRows, int numCols)
{
   int i;
   
   // Handle case of no size change with a return
   if (numRows == nRows && numCols == nCols)
      return;

	// Assign the new matrix size
	nRows = numRows;
	nCols = numCols;

	// Resize to nRows rows
	mat.resize(nRows);

	// Resize each row to have nCols columns
	for (i=0; i < nRows; i++)
		mat[i].resize(nCols);
}

#endif	// MATRIX_CLASS