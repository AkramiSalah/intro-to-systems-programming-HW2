#pragma once
#include <iostream>
class Matrix {
public:
    Matrix();

    Matrix(const Matrix& matrix);

    Matrix(const int& rows, const int& columns, const int value = 0);

    ~Matrix();

    friend std::ostream& operator<<(std::ostream&, const Matrix&);

    Matrix& operator=(const Matrix& matrix);

    int& operator()(const int& row, const int& column);

    const int operator()(const int& row, const int& column) const;
    
    Matrix operator-() const;

    Matrix& operator+=(const Matrix& matrix);

    Matrix operator+(const Matrix& matrix) const;

    Matrix& operator-=(const Matrix& matrix);
    
    Matrix operator-(const Matrix& matrix) const;



    Matrix& operator*=(int n);

    Matrix operator*(const Matrix& matrix) const;

    friend Matrix operator*(int scalar, const Matrix& matrix);

    Matrix& operator*=(const Matrix& matrix);

    Matrix operator*(int scalar) const;
    
    

    friend bool operator==(const Matrix& matrix1, const Matrix& matrix2);
   
    friend bool operator!=(const Matrix& matrix1, const Matrix& matrix2);

    Matrix rotateClockwise() const;

    Matrix rotateCounterClockwise() const;

    Matrix transpose() const;

    static int CalcDeterminant(const Matrix& matrix);

    static double CalcFrobeniusNorm(const Matrix& matrix);


private:
    int* data;
    int rows;
    int columns;

    static int CalcDeterminant(const Matrix& matrix, int startRow, int startColumn, int skipColumn);
    static Matrix subMatrix(const Matrix& matrix, int skipRow, int skipColumn);
};

