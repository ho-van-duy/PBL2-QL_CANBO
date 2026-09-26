#ifndef PHANCONG_H
#define PHANCONG_H

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "ThucThe.h"

class PhanCong : public ThucThe {
private:
    string maPhanCong;
    string maCanBo;
    string maPhong;
    string maChucVu;
    string tuNgay;
    string denNgay;
    string loaiPhanCong;
    bool laPhongChinh;

    static PhanCong* ds;
    static int soLuong;
    static int sucChua;

public:
    PhanCong(const string& = "", const string& = "", const string& = "",
             const string& = "", const string& = "", const string& = "",
             const string& = "", const bool& = false);

    void nhap() override;
    void xuat() const override;
    void ghiDong(ofstream& out) const override;
    void docDong(ifstream& in) override;

    string loaiThucThe() const override;

    string getMaPhanCong() const;
    string getMaCanBo() const;
    string getMaPhong() const;
    string getMaChucVu() const;
    string getTuNgay() const;
    string getDenNgay() const;
    string getLoaiPhanCong() const;
    bool getLaPhongChinh() const;

    void setMaPhanCong(const string&);
    void setMaCanBo(const string&);
    void setMaPhong(const string&);
    void setMaChucVu(const string&);
    void setTuNgay(const string&);
    void setDenNgay(const string&);
    void setLoaiPhanCong(const string&);
    void setLaPhongChinh(const bool&);

    bool HieuLuc() const;
    bool operator==(const PhanCong& other) const;

    static int SoLuong() { return soLuong; }
    static void Them(const PhanCong& a);
    static bool XoaMot(int idx);
    static PhanCong& LayTai(int idx);
    static void DocTatCa();
    static void GhiTatCa();
};

#endif