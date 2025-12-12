#include "Matrix.h"
#include "Utilities.h"
Matrix::Matrix() : rows(0), columns(0) {
    data = nullptr;
}

Matrix::Matrix(const int& rows, const int& columns, int value) : rows(rows), columns(columns) {
    if (rows < 1 || columns < 1)
        throw MatamErrorType(MatamErrorType::UnmatchedSizes);
    data = new int[rows*columns];
    for(int i = 0; i < rows*columns; i++) {
        data[i] = value;
    }
}

Matrix::Matrix(const Matrix& matrix) : rows(matrix.rows), columns(matrix.columns) {
    this->data = new int[rows*columns];
    for(int i = 0; i < rows*columns; i++) {
        this->data[i] = matrix.data[i] ;
    }
}

Matrix::~Matrix() {
    delete[] data;
}


const int  Matrix::getSize() const{
    return columns * rows;
}


Matrix& Matrix::operator=(const Matrix& matrix) {
    if(this == &matrix) {
        return *this;
    }
    int* temp = new int[matrix.rows*matrix.columns];
    delete[] this->data;
    this->data = temp;
    rows = matrix.rows;
    columns = matrix.columns;
    for(int i = 0; i < rows*columns; i++) {
        this->data[i] = matrix.data[i];
    }
    return *this;
}

int& Matrix::operator()(const int& row, const int& column) {
    if(row < 0 || row >= rows || column < 0 || column >= columns)
        throw MatamErrorType(MatamErrorType::OutOfBounds);
    return this->data[row*(this->columns) + column];
}

const int Matrix::operator()(const int& row, const int& column) const {
    if(row < 0 || row >= rows || column < 0 || column >= columns)
        throw MatamErrorType(MatamErrorType::OutOfBounds);
    return this->data[row*(this->columns) + column];
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix){
    if(matrix.getSize() == 0){
        os << "||" << std::endl;
        return os;
    }

    for(int i = 0; i < matrix.rows; i++){
        os << "|";
        for(int j = 0; j < matrix.columns; j++){
            os << matrix(i,j) << "|";
        }
        os << std::endl;
    }

    return os;
}


Matrix& Matrix::operator+=(const Matrix& matrix){
    if( matrix.rows != this->rows|| matrix.columns != this->columns){
        throw MatamErrorType(MatamErrorType::UnmatchedSizes);
    }
    
    for(int row = 0; row < matrix.rows; row++){
        for(int column = 0; column < matrix.columns; column++){
            this->data[ row*(this->columns) + column] += matrix(row,column);
        }
    }
    
    return *this;
}


Matrix& Matrix::operator*=(int n){
    for(int row = 0; row < this->rows; row++){
        for(int column = 0; column < this->columns; column++){
            (*this)(row,column) *= n;
        }
    }

    return *this;
}

Matrix &Matrix::operator*=(const Matrix &matrix) {
    if(matrix.rows != this->columns) {
        throw MatamErrorType(MatamErrorType::UnmatchedSizes);
    }
    for(int row = 0; row < this->rows; row++) {
        for(int column = 0; column < this->columns; column++) {
            (*this)(row,column)=0;
            for(int i = 0; i < matrix.rows; i++) {
                (*this)(row,column) += (*this)(row,i) * matrix(i,column);
            }
        }
    }
    return *this;
}


Matrix Matrix::operator-() const{
    Matrix matrix(*this);
    matrix *= -1;
    return matrix;
}

Matrix& Matrix::operator-=(const Matrix& matrix){
    *this += -matrix;
    return *this;
}

Matrix& Matrix::operator+(const Matrix& matrix) {
    Matrix temp(*this);
    return (temp += matrix);
}

Matrix& Matrix::operator-(const Matrix& matrix) {
    Matrix temp(*this);
    return (temp -= matrix);
}

Matrix &Matrix::operator*(int n) {
    Matrix temp(*this);
    return (temp *= n);
}


Matrix& Matrix::operator*(const Matrix& matrix) {
    Matrix temp(*this);
    return (temp *= matrix);
}

bool operator==(const Matrix& matrix1, const Matrix& matrix2) {
    if(matrix1.rows != matrix2.rows|| matrix1.columns != matrix2.columns) {
        return false;
    }
    for(int row = 0; row < matrix1.rows; row++) {
        for(int column = 0; column < matrix1.columns; column++) {
            if(matrix1(row,column) != matrix2(row,column))
                return false;
        }
    }
    return true;
}

bool operator!=(const Matrix& matrix1, const Matrix& matrix2) {
    return !(matrix1==matrix2);
}

