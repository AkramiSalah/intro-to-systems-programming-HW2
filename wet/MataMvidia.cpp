#include "MataMvidia.h"
#include "Utilities.h"

const Matrix& MataMvidia::operator[](int index) const{
    if(index < 0 || index >= frameCount){
        throw MatamErrorType(MatamErrorType::OutOfBounds);
    }
    return frames[index];
}