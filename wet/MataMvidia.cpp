#include "MataMvidia.h"
#include "Utilities.h"
MataMvidia::MataMvidia(int frameCount, const std::string filmName, const std::string directorName, const Matrix *frames): frameCount(frameCount), filmName(filmName), directorName(directorName) {
    this->frames = new Matrix[frameCount];
    for (int i = 0; i < frameCount; i++) {
        this->frames[i] = frames[i];
    }
}

MataMvidia::MataMvidia(const MataMvidia &other):MataMvidia(other.frameCount,other.filmName,other.directorName,other.frames) {}



Matrix& MataMvidia::operator[](int index){
    if(index < 0 || index >= frameCount){
        throw MatamErrorType(MatamErrorType::OutOfBounds);
    }
    return frames[index];
}

const Matrix& MataMvidia::operator[](int index) const{
    return (*this)[index];
}

std::ostream& operator<<(std::ostream& os, const MataMvidia& film){
    os << "Movie Name:" << film.filmName << std::endl;
    os << "Author:" << film.directorName << std::endl;

    for(int i = 0; i < film.frameCount; i++){
        os << "Frame " << i << ":" << std::endl;
        os << film[i] << std::endl;
    }

    os << "-----End of Movie-----" << std::endl;
}
