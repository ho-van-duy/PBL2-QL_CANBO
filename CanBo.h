#ifndef CANBO_H
#define CANBO_H

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "ThucThe.h"

class CanBo : public ThucThe {
private:
    string MaCanBo;
    string HoTen;
    string NgaySinh;
    string GioiTinh;
    string QueQuan;
    string ChuyenMon;
    string TrinhDo;
    string NgayVao;
    string TrangThai;

    static CanBo* ds;
    static int soLuong;
    static int sucChua;

public:
    CanBo(const string& = "", const string& = "", const string& = "", 
        const string& = "", const string& = "", const string& = "", 
        const string& = "", const string& = "", const string& = "");

    void nhap() override;
    void xuat() const override;
    void ghiDong(ofstream& out) const override;
    void docDong(ifstream& in) override;

    string loaiThucThe() const override;

    string GetMaCB() const;
    string GetTen() const;
    string GetNgaySinh() const;
    string GetGioiTinh() const;
    string GetQueQuan() const;
    string GetChuyenMon() const;
    string GetTrinhDo() const;
    string GetNgayVao() const;
    string GetTrangThai() const;

    void SetMaCB(const string&);
    void SetTen(const string&);
    void SetNgaySinh(const string&);
    void SetGioiTinh(const string&);
    void SetQueQuan(const string&);
    void SetChuyenMon(const string&);
    void SetTrinhDo(const string&);
    void SetNgayVao(const string&);
    void SetTrangThai(const string&);

    int LayNamSinh() const;
    int TinhTuoi() const;
    int TinhNamLam() const;

    static int SoLuong() { return soLuong; }
    static void Them(const CanBo& a);
    static bool XoaMot(int idx);
    static CanBo& LayTai(int idx);
    static void DocTatCa();
    static void GhiTatCa();
};

bool NgayHopLe(const string& ngay);

#endif