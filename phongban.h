#ifndef PHONGBAN_H
#define PHONGBAN_H

#include <iostream>
#include <string>
using namespace std;

class PhongBan {
private:
    string maPhongBan;
    string tenPhongBan;
    int soNhanVien;
    string diaDiem;

    static PhongBan danhSachPhongBan[100];
    static int soLuongPhongBan;

public:
    PhongBan();
    PhongBan(string maPhongBan, string tenPhongBan, int soNhanVien, string diaDiem);

    void nhap();
    void xuat() const;

    string getMaPhongBan() const;
    string getTenPhongBan() const;
    int getSoNhanVien() const;
    string getDiaDiem() const;

    void setMaPhongBan(string maPhongBan);
    void setTenPhongBan(string tenPhongBan);
    void setSoNhanVien(int soNhanVien);
    void setDiaDiem(string diaDiem);

    static void themPhongBan(const PhongBan& phongBan);
    static void xuatDanhSachPhongBan();
    static PhongBan timPhongBanTheoMa(string maPhongBan);
    static int getSoLuongPhongBan();
};

#endif