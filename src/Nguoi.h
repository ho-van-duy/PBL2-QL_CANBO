#ifndef NGUOI_H
#define NGUOI_H

#include <iostream>
#include <string>

using namespace std;

class Nguoi {
protected:
    string hoTen;
    string gioiTinh;
    string queQuan;
    int    namSinh;

public:
    Nguoi();
    Nguoi(const string& ht, const string& gt, const string& qq, int ns);
    virtual ~Nguoi();

    string getHoTen() const;
    string getGioiTinh() const;
    string getQueQuan() const;
    int    getNamSinh() const;

    virtual void   nhap(istream& in) = 0;
    virtual void   xuat(ostream& out) const = 0;
    virtual double thucLinh() const = 0;
};

#endif
