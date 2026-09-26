#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

using namespace std;

class Vector {
  private:
    int n;
    int *p;

  public:
    Vector(const int& n = 0);
    Vector(const Vector&);
    ~Vector();
    const Vector& operator=(const Vector&);
    friend ostream& operator<<(ostream&, const Vector&);
    friend istream& operator>>(istream&, Vector&);
    int& operator[](const int&);
    const int& operator[](const int&) const;
};

#endif