#include "Vector.h"
#include <stdexcept>

Vector::Vector(const int& n) : n(n) {
  this->p = new int[this->n];
  cin >> *this;
}

Vector::Vector(const Vector& v) : n(v.n) {
  this->p = new int[this->n];
  for (int i = 0; i < this->n; i++)
    *(this->p + i) = *(v.p + i);
} 

Vector::~Vector() { delete [] this->p; }

const Vector& Vector::operator=(const Vector& v) {
  if (this != &v) {
    delete [] this->p;
    this->n = v.n;
    this->p = new int[this->n];
    for (int i = 0; i < this->n; i++) 
      *(this->p + i) = *(v.p + i);
  }
  return *this;
}

ostream& operator<<(ostream& o, const Vector& v) {
  for (int i = 0 ; i < v.n; i++)
    o << *(v.p + i) << " ";
  o << endl;
  return o;
}

istream& operator>>(istream& in, Vector& v) {
  for (int i = 0; i < v.n; i++) {
    cout << "p[" << i << "] = ";
    in >> *(v.p + i);
  }
  return in;
}

int& Vector::operator[](const int& index) {
  if (index >= 0 && index < this->n) return *(this->p + index);
  throw out_of_range("Vector::operator[] - chi so ngoai pham vi");
}

const int& Vector::operator[](const int& index) const {
  if (index >= 0 && index < this->n) return *(this->p + index);
  throw out_of_range("Vector::operator[] - chi so ngoai pham vi");
}