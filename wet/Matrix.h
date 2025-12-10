#pragma once
#include <iostream>
class Matrix {
    int* data;
    int rows;
    int columns;

public:
    Matrix();

    Matrix(const Matrix& matrix);

    Matrix(const int& rows, const int& columns, int value = 0);

    ~Matrix();

    const int getColumns() const;

    const int getRows() const;

    const int getSize() const;

    Matrix& operator=(const Matrix& matrix);

    int& operator()(const int& row, const int& column);

    const int operator()(const int& row, const int& column) const;

    friend std::ostream& operator<<(std::ostream&, const Matrix&);

};

