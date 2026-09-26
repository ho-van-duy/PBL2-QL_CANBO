#ifndef LUONG_H
#define LUONG_H

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "ThucThe.h"

class Luong : public ThucThe {
private:
    string maLuong;
    string maCanBo;
    double heSoLuong;
    double phuCap;
    double anTrua;
    string tuNgay;
    string denNgay;
    string lyDoTangLuong;

    static Luong* ds;
    static int soLuong;
    static int sucChua;

public:
    Luong(const string& = "", const string& = "", const double& = 0.0,
          const double& = 0.0, const double& = 0.0, const string& = "",
          const string& = "", const string& = "");

    void nhap() override;
    void xuat() const override;
    void ghiDong(ofstream& out) const override;
    void docDong(ifstream& in) override;

    string loaiThucThe() const override;

    string getMaLuong() const;
    string getMaCanBo() const;
    double getHeSoLuong() const;
    double getPhuCap() const;
    double getAnTrua() const;
    string getTuNgay() const;
    string getDenNgay() const;
    string getLyDoTangLuong() const;

    void setMaLuong(const string&);
    void setMaCanBo(const string&);
    void setHeSoLuong(const double&);
    void setPhuCap(const double&);
    void setAnTrua(const double&);
    void setTuNgay(const string&);
    void setDenNgay(const string&);
    void setLyDoTangLuong(const string&);

    bool HieuLuc() const;
    double tinhThucLinh() const;

    static int SoLuong() { return soLuong; }
    static void Them(const Luong& a);
    static bool XoaMot(int idx);
    static Luong& LayTai(int idx);
    static void DocTatCa();
    static void GhiTatCa();
};

#endif