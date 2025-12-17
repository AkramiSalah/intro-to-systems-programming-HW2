#pragma once
#include "Matrix.h"
#include <string>

class MataMvidia {
public:
    MataMvidia(const std::string filmName, const std::string directorName, const Matrix* frames, int frameCount);

    MataMvidia(const MataMvidia& other);

    MataMvidia& operator=(const MataMvidia& other);

    const Matrix& operator[](int index) const;

    ~MataMvidia();

    Matrix& operator[](int index);

    MataMvidia& operator+=(const MataMvidia& other);

    MataMvidia& operator+=(const Matrix& other);

    MataMvidia operator+(const MataMvidia& other);

    friend std::ostream& operator<<(std::ostream&, const MataMvidia&);


private:
    int frameCount;
    std::string filmName;
    std::string directorName;
    Matrix* frames;
};


