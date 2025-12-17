#include "MataMvidia.h"
#include "Utilities.h"


Matrix& MataMvidia::operator[](int index){
    if(index < 0 || index >= frameCount){
        throw MatamErrorType(MatamErrorType::OutOfBounds);
    }
    return frames[index];
}

const Matrix& MataMvidia::operator[](int index) const{
    return (*this)[index];
}
