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

const int  Matrix::getColumns() const {
        return columns;
}

const int  Matrix::getRows() const{
    return this->rows;
}

const int  Matrix::getSize() const{
    return getColumns() * getRows();
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

    for(int i = 0; i < matrix.getRows(); i++){
        os << "|";
        for(int j = 0; j < matrix.getRows(); j++){
            os << matrix(i,j) << "|";
        }
        os << std::endl;
    }

    return os;
}


