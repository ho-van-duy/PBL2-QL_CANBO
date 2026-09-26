#ifndef DANHGIA_H
#define DANHGIA_H

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "ThucThe.h"

class DanhGia : public ThucThe {
private:
    string maDanhGia;
    string maCanBo;
    string xepLoai;
    string nhanXet;
    string ngayDanhGia;

    static DanhGia* ds;
    static int soLuong;
    static int sucChua;

public:
    DanhGia(const string& = "", const string& = "", const string& = "", const string& = "", const string& = "");

    void nhap() override;
    void xuat() const override;
    void ghiDong(ofstream& out) const override;
    void docDong(ifstream& in) override;

    string loaiThucThe() const override;

    string GetMaDG() const;
    string GetMaCanBo() const;
    string GetXepLoai() const;
    string GetNhanXet() const;
    string GetNgayDanhGia() const;

    void SetMaDG(const string&);
    void SetMaCanBo(const string&);
    void SetXepLoai(const string&);
    void SetNhanXet(const string&);
    void SetNgayDanhGia(const string&);

    static int SoLuong() { return soLuong; }
    static void Them(const DanhGia& a);
    static bool XoaMot(int idx);
    static DanhGia& LayTai(int idx);
    static void DocTatCa();
    static void GhiTatCa();
};

#endif
