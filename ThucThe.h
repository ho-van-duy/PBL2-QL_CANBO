#ifndef THUCTHE_H
#define THUCTHE_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class ThucThe {
public:
    virtual void nhap() = 0;
    virtual void xuat() const {
        cout << "----- " << loaiThucThe() << " -----" << endl;
    }
    virtual void ghiDong(ofstream& out) const = 0;
    virtual void docDong(ifstream& in) = 0;
    virtual string loaiThucThe() const = 0;
    virtual ~ThucThe() {}
};

#endif