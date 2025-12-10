#include "Matrix.h"
Matrix::Matrix() : rows(0), columns(0) {
    matrix = nullptr;
}

Matrix::Matrix(const int& rows, const int& columns, int value) : rows(rows), columns(columns) {
    matrix = new int[rows*columns];
    for(int i = 0; i< rows*columns; i++) {
        matrix[i] = value;
    }
}
Matrix::Matrix(const Matrix& matrix) : rows(matrix.rows), columns(matrix.columns) {
    this->matrix=new int[rows*columns];
    for(int i = 0; i< rows*columns; i++) {
        this->matrix[i] = matrix.matrix[i] ;
    }
}
Matrix::~Matrix() {
    delete[] matrix;
}
Matrix& Matrix::operator=(const Matrix& matrix) {
    if(this == &matrix) {
        return *this;
    }
    int* temp=new int[matrix.rows*matrix.columns];
    delete[] this->matrix;
    this->matrix=temp;
    rows=matrix.rows;
    columns=matrix.columns;
    for(int i = 0; i< rows*columns; i++) {
        this->matrix[i] = matrix.matrix[i];
    }
    return *this;
}




