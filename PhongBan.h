#ifndef PHONGBAN_H
#define PHONGBAN_H

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "ThucThe.h"

class PhongBan : public ThucThe {
private:
    string maPhong;
    string tenPhong;
    string moTa;

    static PhongBan* ds;
    static int soLuong;
    static int sucChua;

public:
    PhongBan(const string& = "", const string& = "", const string& = "");

    void nhap() override;
    void xuat() const override;
    void ghiDong(ofstream& out) const override;
    void docDong(ifstream& in) override;

    string loaiThucThe() const override;

    string GetMaPhong() const;
    string GetTenPhong() const;
    string GetMoTa() const;

    void SetMaPhong(const string&);
    void SetTenPhong(const string&);
    void SetMoTa(const string&);

    static int SoLuong() { return soLuong; }
    static void Them(const PhongBan& a);
    static bool XoaMot(int idx);
    static PhongBan& LayTai(int idx);
    static void DocTatCa();
    static void GhiTatCa();
};

#endif