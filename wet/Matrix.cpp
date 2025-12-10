#include "Matrix.h"
Matrix::Matrix() : rows(0), columns(0) {
    matrix = new int[rows*columns];
}

Matrix::Matrix(const int& rows, const int& columns, int value) : rows(rows), columns(columns) {
    matrix = new int[rows*columns];
    for(int i = 0; i< rows*columns; i++) {
        matrix[i] = value;
    }
}

