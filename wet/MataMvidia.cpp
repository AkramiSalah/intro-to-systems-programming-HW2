#include "MataMvidia.h"
#include "Utilities.h"

MataMvidia::MataMvidia(const std::string filmName, const std::string directorName, const Matrix *frames, int frameCount) :
    frameCount(frameCount), filmName(filmName), directorName(directorName){
    this->frames = new Matrix[frameCount];
    for (int i = 0; i < frameCount; i++) {
        this->frames[i] = frames[i];
    }
}

MataMvidia::MataMvidia(const MataMvidia &other) : 
    MataMvidia(other.filmName, other.directorName, other.frames, other.frameCount) {}

MataMvidia::~MataMvidia() {
    delete[] this->frames;
}

MataMvidia &MataMvidia::operator=(const MataMvidia& other) {
    if(this == &other){
        return *this;
    }
    this->frameCount = other.frameCount;
    this->filmName = other.filmName;
    this->directorName = other.directorName;
    Matrix* temp = new Matrix[frameCount];
    delete[] this->frames;
    this->frames = temp;
    for (int i = 0; i < frameCount; i++) {
        this->frames[i] = other.frames[i];
    }
    return *this;
}

Matrix& MataMvidia::operator[](int index){
    if(index < 0 || index >= frameCount){
        exitWithError(MatamErrorType(MatamErrorType::OutOfBounds));
    }
    return frames[index];
}

const Matrix& MataMvidia::operator[](int index) const{
    if(index < 0 || index >= frameCount){
        exitWithError(MatamErrorType(MatamErrorType::OutOfBounds));
    }
    return frames[index];
}

MataMvidia& MataMvidia::operator+=(const Matrix& other){
    Matrix* newFrames = new Matrix[frameCount + 1];
    for (int i = 0; i < frameCount; i++) {
        newFrames[i] = frames[i];
    }

    newFrames[frameCount] = other;

    delete[] frames;
    frames = newFrames;
    frameCount++;

    return *this;
}

MataMvidia& MataMvidia::operator+=(const MataMvidia& other){
    for(int i = 0; i < other.frameCount; i++){
        *this += other[i];
    }
    return *this;
}

MataMvidia MataMvidia::operator+(const MataMvidia& other){
    MataMvidia result = *this;
    result += other;
    return result;
}


std::ostream& operator<<(std::ostream& os, const MataMvidia& film){
    os << "Movie Name: " << film.filmName << std::endl;
    os << "Author: " << film.directorName << std::endl;
    os << std::endl;

    for(int i = 0; i < film.frameCount; i++){
        os << "Frame " << i << ":" << std::endl;
        os << film[i] << std::endl;
    }

    os << "-----End of Movie-----" << std::endl;
    return os;
}
