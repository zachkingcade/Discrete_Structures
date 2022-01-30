#include "Matrix.h"
#include <string>
#include <sstream>


//Name:Matrix
//purpose:Default Constructor
Matrix::Matrix(){
    rows = 1;
    columns = 1;
    ptrArray = new int*[rows];
    ptrArray[1] = new int[columns];
    ptrArray[1][1] = 0;
}

//Name: Matrix
//Input: number of Rows and Columns
//purpose: Parameterized constructor
Matrix::Matrix(int rows,int columns){
    //create a row x column matrix of garbage
    this->rows = rows;
    this->columns = columns;
    ptrArray = new int*[rows];
    for (int i = 0; i < rows; i++){
        ptrArray[i] = new int[columns];
    }

    //replace the garbage with 0's
    for (int r = 0; r < rows; r++){
        for (int c = 0; c < columns; c++){
            ptrArray[r][c] = 0;
        }
    }
}

//Name: Matrix
//Input: A Matrix object
//purpose: Copy constructor
Matrix::Matrix(const Matrix & original){

    //set our rows and columns to match our original object
    rows = original.rows;
    columns = original.columns;

    //create our new Internal Matrix
    ptrArray = new int*[rows];
    for (int i = 0; i < rows; i++){
        ptrArray[i] = new int[columns];
    }

    //Set the values to match the values of our original object
    for (int r = 0; r < rows; r++){
        for (int c = 0; c < columns; c++){
            ptrArray[r][c] = original.ptrArray[r][c];
        }
    }
}

//Name: Matrix
//purpose: Destructor
Matrix::~Matrix(){
    for (int r = 0; r < rows; r++){
        delete[] ptrArray[r];
    }
    delete[] ptrArray;
}

//Name:checkRows
//output: out puts the number of rows
//purpose: returns the number of rows
int Matrix::checkRows(){return rows;}

//Name:checkColumns
//output: out puts the number of columns
//purpose: returns the number of columns
int Matrix::checkColumns(){return columns;}

//Name:checkElement
//input: specifies the row and column of the intended element
//output: out puts the specified element
//purpose: returns the value of the specified element
int Matrix::checkElement(int row,int column){
    return ptrArray[row][column];
}

//Name:setElement
//input: first two specifies the row and column of the 
//intended element, last is the value to change the 
//element to
//purpose: sets the value of the specified element
//see alternative MatrixObject[][] syntax below at Operator[]
void Matrix::setElement(int row,int column,int value){
    ptrArray[row][column] = value;
}

//Name:symmetric
//output: true if the matrix is symmetric and false otherwise
//purpose: checks if the matrix is square if it is it tells weather
//or not the matrix is symmetric, if not it just returns false since
//a matrix must be square to be symmetric
bool Matrix::symmetric(){
    bool result = true;
    if (rows == columns){
        for (int r = 0; r < rows; r++){
            for (int c = 0; c < columns; c++){
                if (r != c && ptrArray[r][c] != ptrArray[c][r]){
                    result = false;
                }
            }
        }
    } else {
        //only square matrixes can be symmetric
        result = false;
    }
    return result;
}

//Name:transpose
//output: The Matrix transposed
//purpose: Transposes a copy of the current matrix and returns the result
//Does not affect the original matrix
Matrix Matrix::transpose(){
    //create the matrix we're going to return with the number of columns
    //and rows swapped
    Matrix resultingMatrix(columns,rows);
    for (int c = 0; c < columns; c++){
        for (int r = 0; r < rows; r++){
            resultingMatrix.setElement(c,r,ptrArray[r][c]);
        }
    }
    return resultingMatrix;
}

//Name: toString
//Output: a string version of the matrix
//Purpose: Returns a string version of the matrix
std::string Matrix::toString(){
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

//Name: operator +
//Input: Matrix to add
//output: added together matrix
//purpose: checks if the current matric and passed in matrix are the same
//size, if they are addes together the current matrix and a passed in matrix
//using the plus operator so matrix + matrix, return the result, else it
//throws an error that will need to caught on the user's side if they want to
//prevent crashing
Matrix Matrix::operator +(Matrix rightSide){
    if(rows == rightSide.checkRows() && columns == rightSide.checkColumns()){
        Matrix resultingMatrix(rows,columns);
        int value;
        for (int r = 0; r < rows; r++){
            for (int c = 0; c < columns; c++){
                value = ptrArray[r][c] + rightSide.checkElement(r, c);
                resultingMatrix.setElement(r,c,value);
            }
        }
        return resultingMatrix;
    }else {
        throw "Error:Matrix addition- matrixes not of the same size";
    }
}

//Name: operator *
//Input: Matrix to multiply
//output: multiplied together matrix
//purpose: checks if the current matrix's number of rows and the passed in 
//matrix's number of columns are the same size, if they are multiplies 
//together the current matrix and a passed in matrix using the astrix 
//operator so matrix * matrix, returns the result, else it throws an 
//error that will need to be caught on the user's side if they wish
//to prevent crashing
Matrix Matrix::operator *(Matrix rightSide){
    if (columns == rightSide.rows){
        Matrix resultingMatrix(rows, rightSide.columns);
        //i = leftside matrix's rows
        //j = leftSide matrix's columns
        //k = each row element in j
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < rightSide.columns; j++){
                for(int k = 0; k < columns; k++){
                    resultingMatrix[i][j] += ptrArray[i][k] * rightSide[k][j];    
                }
            }
        }
        return resultingMatrix;
    }else {
        throw "Error:Matrix Multiplication-Number of rows and columns do not match";
    }
}

//Name: operator <<
//Input: empty ostream
//output: ostream with matrix string in it
//purpose: outputs the matrix in a neat and concise format as a string object

std::ostream& operator <<(std::ostream& out, Matrix mat){
    //for padding we need to figure out what the largest/longest number in our
    //matrix is, no accounting for negatives since -111 is still longer but no
    //larger then 10
    int longestNum = 0;
    int padding;
    for (int r = 0; r < mat.rows; r++){
        for (int c = 0; c < mat.columns; c++){
            if (abs(mat.ptrArray[r][c]) > longestNum){
                longestNum = abs(mat.ptrArray[r][c]);
            }
        }
    }
    //now we check the actual length of that number and use it as our padding
    padding = std::to_string(longestNum).size(); 
    
    for (int r = 0; r < mat.rows; r++){
        for (int c = 0; c < mat.columns; c++){
            out << std::setw(padding) << mat.ptrArray[r][c] << ' ';
        }
        //the if makes it not print a new line on the very last row leaving
        //that up to the user
        if (r != mat.rows - 1) {out << '\n';}
    } 
        return out;
}

//Name: Operator []
//Input: Index
//output: return a pointer to an array
//purpose: returns a pointer to an array allowing us to both get the value
//and set the value of elements using the syntax MatrixObject[r][c]. This is
//posible due to operations going from left to right (with a few exceptions
//like '='s operator), so we return a pointer to a array of the row indicated
//and the the second sub indexes the returned matrix giving us that elements
//location/address
int* Matrix::operator [] (int index){
    return ptrArray[index];
}
