#include <iostream>
#include <exception>
#include <cmath>
#include "Vector.h"

Vector::Vector() {
    fDimension = defaultVectorDimSize;
    allocSize = defaultVectorDimSize;
    initialize(allocSize);
}

Vector::Vector(int dimension) {
    fDimension = dimension;
    allocSize = dimension;
    initialize(allocSize);
}

Vector::Vector(int size, const double elements[]) {
    fDimension = size;
    allocSize = size;
    initialize(allocSize);
    forEachDim([elements, this](int index) {
        this->fElements[index] = elements[index];
    });
}

Vector::Vector(const Vector &source) {
    fDimension = source.fDimension;
    allocSize = source.fDimension;
    initialize(allocSize);
    forEachDim([&source, this](int index) {
        this->fElements[index] = source.fElements[index];
    });
}

Vector::~Vector() {
    delete [] fElements;
}

void Vector::initialize(int size) {
    fElements = new double[size];
    forEachAlloc([this](int index) {
        this->fElements[index] = 0;
    });
}

int Vector::getDimension() const {
    return fDimension;
}

void Vector::setDimension(int dim) {
    if(dim > fDimension) {
        double *temp = fElements;
        allocSize = dim;
        initialize(dim);
        forEachDim([this, temp](int index) {
            fElements[index] = temp[index];
        });
    }
    fDimension = dim;
}

double Vector::length() const {
    double length = 0;
    forEachDim([&length, this](int index) {
        length += fElements[index] * fElements[index];
    });
    return sqrt(length);
}

Vector Vector::operator+(const Vector &other) const {
    int biggerDim = fDimension > other.fDimension ? fDimension : other.fDimension;
    double *temp = new double[biggerDim];
    for(int i = 0; i < biggerDim; i++) {
        temp[i] = (i < fDimension ? fElements[i] : 0) + 
                  (i < other.fDimension ? other.fElements[i] : 0);
    }
    return Vector(biggerDim, temp);
}

Vector Vector::operator-(const Vector &other) const {
    return (*this + (-other));
}

Vector operator-(const Vector &self) {
    return (self * -1.0);
}

Vector Vector::operator*(const double scalar) const {
    double *temp = new double[fDimension];
    forEachDim([temp, this, scalar](int index) {
        temp[index] = scalar * fElements[index];
    });
    return Vector(fDimension, temp);
}

Vector operator*(const double scalar, const Vector & v) {
    return v * scalar;
}

Vector& Vector::operator=(const Vector &other) {
    if(this == &other) return *this;
    delete [] fElements;
    allocSize = other.fDimension;
    fDimension = other.fDimension;
    initialize(allocSize);
    forEachDim([&other, this](int index) {
        this->fElements[index] = other.fElements[index];
    });
    return *this;
}

Vector& Vector::operator+=(const Vector &other) {
    return (*this) = (*this) + other;
}

Vector& Vector::operator-=(const Vector &other) {
    return (*this) = (*this) - other;
}

Vector& Vector::operator*=(const double scalar) {
    return (*this) = (*this) * scalar;
}

double Vector::operator[](const int index) const {
    if(index < 0 || index >= fDimension) return 0.0;
    else return fElements[index];
}

bool Vector::operator==(const Vector &other) const {
    if(other.fDimension != fDimension) return false;
    bool check = true;
    forEachDim([this, &other, &check](int index) {
        check = check && (this->fElements[index] == other.fElements[index]);
    });
    return check;
}

bool Vector::operator!=(const Vector &other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Vector &v) {
    os << "(";
    v.forEachDim([&v, &os](int index) {
        os << v.fElements[index];
        if(index != v.fDimension - 1)
            os << ", "; 
    });
    os << ")";
    return os;
}

template<class _FUNC>
void Vector::forEachDim(_FUNC func) const {
    for(int i = 0; i < fDimension; i++) {
        func(i);
    }
}

template<class _FUNC>
void Vector::forEachAlloc(_FUNC func) const {
    for(int i = 0; i < allocSize; i++) {
        func(i);
    }
}