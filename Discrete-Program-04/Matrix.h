#pragma once
#include<iostream>
#include<sstream>
#include<cmath>
#include<iomanip>

class Matrix {
public:
    //Name: Matrix
    //purpose: Default Constructor
    Matrix();
    
    //Name: Matrix
    //Input: number of Rows and Columns
    //purpose: Parameterized constructor
    Matrix(int,int);
    
    //Name: Matrix
    //Input: A Matrix object
    //purpose: Copy constructor
    Matrix(const Matrix &);
    
    //Name: Matrix
    //purpose: Destructor
    ~Matrix();

    //Name:checkRows
    //output: out puts the number of rows
    //purpose: returns the number of rows
    int checkRows();

    //Name:checkColumns
    //output: out puts the number of columns
    //purpose: returns the number of columns
    int checkColumns();

    //Name:checkElement
    //input: specifies the row and column of the intended element
    //output: out puts the specified element
    //purpose: returns the value of the specified element
    int checkElement(int,int);

    //Name:setElement
    //input: first two specifies the row and column of the 
    //intended element, last is the value to change the 
    //element to
    //purpose: sets the value of the specified element
    //see alternative MatrixObject[][] syntax below at Operator[]
    void setElement(int,int,int);

    //Name:symmetric
    //output: true if the matrix is symmetric and false otherwise
    //purpose: checks if the matrix is square if it is it tells weather
    //or not the matrix is symmetric, if not it just returns false since
    //a matrix must be square to be symmetric
    bool symmetric();

    //Name:transpose
    //output: The Matrix transposed
    //purpose: Transposes a copy of the current matrix and returns the result
    //Note: Does not affect the original matrix
    Matrix transpose();

    //Name: toString
    //Output: a string version of the matrix
    //Purpose: Returns a string version of the matrix
    std::string toString();

    //Name: operator +
    //Input: Matrix to add
    //output: added together matrix
    //purpose: checks if the current matric and passed in matrix are the same
    //size, if they are addes together the current matrix and a passed in matrix
    //using the plus operator so matrix + matrix, return the result, else it
    //throws an error that will need to caught on the user's side if they want to
    //prevent crashing
    Matrix operator +(Matrix);

    //Name: operator *
    //Input: Matrix to multiply
    //output: multiplied together matrix
    //purpose: checks if the current matrix's number of rows and the passed in 
    //matrix's number of columns are the same size, if they are multiplies 
    //together the current matrix and a passed in matrix using the astrix 
    //operator so matrix * matrix, returns the result, else it sends an 
    //error and returns an empty matrix
    Matrix operator *(Matrix);

    //Name: operator <<
    //Input: empty ostream
    //output: ostream with matrix string in it, kinda acts like a wrapper
    //purpose: outputs the matrix in a neat and concise format as a string object
    friend std::ostream& operator <<(std::ostream&, Matrix);

    //Name: Operator []
    //Input: Index
    //output: return a pointer to an array
    //purpose: returns a pointer to an array allowing us to both get the value
    //and set the value of elements using the syntax MatrixObject[r][c]. This is
    //posible due to operations going from left to right (with a few exceptions
    //like '='s operator), so we return a pointer to a array of the row indicated
    //and the the second sub indexes the returned matrix giving us that elements
    //location/address
    int* operator[] (int);

protected:
    int rows = 0;
    int columns = 0;
    int **ptrArray;

};