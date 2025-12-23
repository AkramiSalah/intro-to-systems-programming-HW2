#include "Matrix.h"
#include "Utilities.h"
#include <cmath>

Matrix::Matrix() : rows(0), columns(0) {
    data = nullptr;
}

Matrix::Matrix(const int& rows, const int& columns, int value) : rows(rows), columns(columns) {
    if (rows <= 0 || columns <= 0){
        data = nullptr;
        return;
    }

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
        exitWithError(MatamErrorType(MatamErrorType::OutOfBounds));
    return data[row*(columns) + column];
}

const int Matrix::operator()(const int& row, const int& column) const {
    if(row < 0 || row >= rows || column < 0 || column >= columns)
        exitWithError(MatamErrorType(MatamErrorType::OutOfBounds));
    return data[row*(columns) + column];
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix){
    if(matrix.rows * matrix.columns == 0){
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
        exitWithError(MatamErrorType(MatamErrorType::UnmatchedSizes));
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
        exitWithError(MatamErrorType(MatamErrorType::UnmatchedSizes));
    }

    Matrix result(rows, matrix.columns);
    for(int row = 0; row < rows; row++){
        for(int column = 0; column < matrix.columns; column++){
            for(int vectorIndex = 0; vectorIndex < columns; vectorIndex++){
                result(row,column) += (*this)(row,vectorIndex) * matrix(vectorIndex,column);
            }
        }
    }

    return result;
}

Matrix& Matrix::operator*=(const Matrix& matrix){
    *this = (*this)*matrix;
    return *this;
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
    for(int column = 0; column < columns; column++) {
        for(int row = 0; row < rows; row++) {
            temp(column, rows - row - 1)=(*this)(row,column);
        }
    }
    return temp;
}

Matrix Matrix::rotateCounterClockwise() const {
    return rotateClockwise().rotateClockwise().rotateClockwise();
}

Matrix Matrix::transpose() const{
    Matrix temp(columns,rows);
    for(int column = 0; column < columns; column++) {
        for(int row = 0; row < rows; row++) {
            temp(column, row)=(*this)(row,column);
        }
    }
    return temp;
}


Matrix Matrix::subMatrix(const Matrix& matrix, int skipRow, int skipColumn){
    int subMatrixRow = 0;
    int subMatrixColumn = 0;
    Matrix result(matrix.rows-1, matrix.columns-1);
    for(int row = 0; row < matrix.rows; row++){
        if(row == skipRow){
                continue;
        }
        for(int column = 0; column < matrix.columns; column++){
            if(column == skipColumn){
                continue;
            }
            result(subMatrixRow,subMatrixColumn) = matrix(row,column);
            subMatrixColumn++;
        }
        subMatrixRow++;
        subMatrixColumn = 0;
    }

    return result;
}

double Matrix::CalcDeterminant(const Matrix& matrix){
    if(matrix.columns != matrix.rows){
        exitWithError(MatamErrorType(MatamErrorType::NotSquareMatrix));
    }

    if(matrix.data == nullptr){
        return 0;
    }
    
    if(matrix.rows == 1 && matrix.columns == 1){
        return matrix.data[0];
    }

    double sign = 1;
    double result = 0;

    for(int column = 0; column < matrix.columns; column++){
        Matrix currentSubMatrix = subMatrix(matrix, 0, column);
        result += sign * matrix(0,column) * CalcDeterminant(currentSubMatrix);
        sign *= -1;
    }
    return result;
}

double Matrix::CalcFrobeniusNorm(const Matrix& matrix){
    int matrixSize = matrix.rows * matrix.columns;
    double result = 0;
    for(int i = 0; i < matrixSize; i++){
        result += matrix.data[i] * matrix.data[i];
    }
    return std::sqrt(result);
}