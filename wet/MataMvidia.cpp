#include "MataMvidia.h"
#include "Utilities.h"
MataMvidia::MataMvidia(int frameCount, const std::string filmName, const std::string directorName, const Matrix *frames): frameCount(frameCount), filmName(filmName), directorName(directorName) {
    this->frames = new Matrix[frameCount];
    for (int i = 0; i < frameCount; i++) {
        this->frames[i] = frames[i];
    }
}


Matrix& MataMvidia::operator[](int index){
    if(index < 0 || index >= frameCount){
        throw MatamErrorType(MatamErrorType::OutOfBounds);
    }
    return frames[index];
}

const Matrix& MataMvidia::operator[](int index) const{
    return (*this)[index];
}
