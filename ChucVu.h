#ifndef CHUCVU_H
#define CHUCVU_H

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "ThucThe.h"

class ChucVu : public ThucThe {
private:
    string maChucVu;
    string tenChucVu;
    double phuCapChucVu;
    string moTa;

    static ChucVu* ds;
    static int soLuong;
    static int sucChua;

public:
    ChucVu(const string& = "", const string& = "", const double& = 0.0, const string& ="");
    void nhap() override;
    void xuat() const override;
    void ghiDong(ofstream& out) const override;
    void docDong(ifstream& in) override;

    string loaiThucThe() const override;

    string GetMaCV() const;
    string GetTenCV() const;
    double GetPhuCapCV() const;
    string GetMoTa() const;

    void SetMaCV(const string&);
    void SetTenCV(const string&);
    void SetPhuCapCV(const double&);
    void SetMoTa(const string&);

    static int SoLuong() { return soLuong; }
    static void Them(const ChucVu& a);
    static bool XoaMot(int idx);
    static ChucVu& LayTai(int idx);
    static void DocTatCa();
    static void GhiTatCa();
};

#endif