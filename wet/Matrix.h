#pragma once
#include <iostream>
class Matrix {
public:
    Matrix();

    Matrix(const Matrix& matrix);

    Matrix(const int& rows, const int& columns, int value = 0);

    ~Matrix();


    const int getSize() const;

    Matrix& operator=(const Matrix& matrix);

    int& operator()(const int& row, const int& column);

    const int operator()(const int& row, const int& column) const;

    Matrix& operator+(const Matrix& matrix);

    Matrix& operator-(const Matrix& matrix);

    Matrix& operator*(const Matrix& matrix);

    Matrix& operator*(int n);
    
    Matrix operator-() const;

    Matrix& operator+=(const Matrix& matrix);

    Matrix& operator-=(const Matrix& matrix);

    Matrix& operator*=(const Matrix& matrix);

    Matrix& operator*=(int n);

    Matrix& rotateClockwise() const;

    Matrix& rotateCounterClockwise() const;



    
private:
    int* data;
    int rows;
    int columns;
    friend bool operator==(const Matrix& matrix1, const Matrix& matrix2);
    friend bool operator!=(const Matrix& matrix1, const Matrix& matrix2);
    friend std::ostream& operator<<(std::ostream&, const Matrix&);
};

