#pragma once



class Matrix {
    int* matrix;
    const int rows;
    const int columns;
public:
    Matrix(const int& rows, const int& columns);
    Matrix(const int& rows, const int& columns,int value);
    Matrix();
};

