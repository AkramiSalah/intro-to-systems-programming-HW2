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
    data = new int[rows*columns];
    for(int i = 0; i < rows*columns; i++) {
        data[i] = matrix.data[i] ;
    }
}

Matrix::~Matrix() {
    delete[] data;
}

Matrix& Matrix::operator=(const Matrix& matrix) {
    if(this == &matrix) {
        return *this;
    }
    int* temp = new int[matrix.rows*matrix.columns];
    delete[] data;
    data = temp;
    rows = matrix.rows;
    columns = matrix.columns;
    for(int i = 0; i < rows*columns; i++) {
        data[i] = matrix.data[i];
    }
    return *this;
}

int& Matrix::operator()(const int& row, const int& column) {
    if(row < 0 || row >= rows || column < 0 || column >= columns)
        throw MatamErrorType(MatamErrorType::OutOfBounds);
    return data[row*(columns) + column];
}

const int Matrix::operator()(const int& row, const int& column) const {
    if(row < 0 || row >= rows || column < 0 || column >= columns)
        throw MatamErrorType(MatamErrorType::OutOfBounds);
    return data[row*(columns) + column];
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix){
    if(matrix.rows * matrix.columns == 0){
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
    if( matrix.rows != rows || matrix.columns != columns){
        throw MatamErrorType(MatamErrorType::UnmatchedSizes);
    }
    
    for(int row = 0; row < matrix.rows; row++){
        for(int column = 0; column < matrix.columns; column++){
            (*this)(row,column) += matrix(row,column);
        }
    }
    
    return *this;
}


Matrix& Matrix::operator*=(int n){
    for(int row = 0; row < rows; row++){
        for(int column = 0; column < columns; column++){
            (*this)(row,column) *= n;
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

Matrix Matrix::operator+(const Matrix& matrix) const {
    Matrix temp(*this);
    return (temp += matrix);
}

Matrix Matrix::operator-(const Matrix& matrix) const {
    Matrix temp(*this);
    return (temp -= matrix);
}

Matrix Matrix::operator*(int n) const{
    Matrix temp(*this);
    temp *= n;
    return temp;
}

Matrix operator*(int scalar, const Matrix& matrix){
    return matrix * scalar;
}


Matrix Matrix::operator*(const Matrix& matrix) const{
    if(columns != matrix.rows){
        throw MatamErrorType(MatamErrorType::UnmatchedSizes);
    }

    Matrix result(rows, matrix.columns);
    for(int row = 0; row < rows; row++){
        for(int column = 0; column < columns; column++){
            for(int vectorIndex = 0; vectorIndex < row; vectorIndex++){
                result(row,column) += (*this)(row,vectorIndex) * matrix(vectorIndex,column);
            }
        }
    }
}

Matrix& Matrix::operator*=(const Matrix& matrix){
    Matrix temp;
    temp = (*this)*matrix;
    return temp;
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

Matrix Matrix::rotateClockwise() const {
    Matrix temp(columns,rows);
    for(int row = 0; row < rows; row++) {
        for(int column = 0; column < columns; column++) {
            temp(row,column)=(*this)(column,columns-1-row);
        }
    }
    return temp;
}

Matrix Matrix::rotateCounterClockwise() const {
    return rotateClockwise().rotateClockwise().rotateClockwise();
}
