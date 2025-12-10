#pragma once
class Matrix {
    int* matrix;
    const int rows;
    const int columns;
public:
    Matrix() = default;

    Matrix(const int& rows, const int& columns, int value = 0);
    
};

