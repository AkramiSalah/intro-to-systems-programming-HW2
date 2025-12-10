#pragma once
class Matrix {
    int* matrix;
    int rows;
    int columns;
public:
    Matrix();
    Matrix(const Matrix& matrix);
    Matrix(const int& rows, const int& columns, int value = 0);
    ~Matrix();
    Matrix& operator=(const Matrix& matrix);
    int& operator()(const int& row, const int& column);
};

