#ifndef CHUCVU_H
#define CHUCVU_H

#include <iostream>
#include <string>
using namespace std;

class ChucVu {
private:
    string maChucVu;
    string tenChucVu;
    int heSoLuong;
    int capBac;
    string quyenHan;
    string moTa;

    static ChucVu danhSachChucVu[100];
    static int soLuongChucVu;

public:
    ChucVu();
    ChucVu(string maChucVu, string tenChucVu, int heSoLuong, int capBac,
           string quyenHan, string moTa);

    void nhap();
    void xuat() const;

    string getMaChucVu() const;
    string getTenChucVu() const;
    int getHeSoLuong() const;
    int getCapBac() const;
    string getQuyenHan() const;
    string getMoTa() const;

    void setMaChucVu(string maChucVu);
    void setTenChucVu(string tenChucVu);
    void setHeSoLuong(int heSoLuong);
    void setCapBac(int capBac);
    void setQuyenHan(string quyenHan);
    void setMoTa(string moTa);

    bool laCaoHon(const ChucVu& other) const;
    bool coQuyenQuanLy() const;
    double tinhLuong(double luongCoBan) const;

    static void themChucVu(const ChucVu& chucVu);
    static void xuatDanhSachChucVu();
    static ChucVu timChucVuTheoMa(string maChucVu);
    static int getSoLuongChucVu();
};

#endif
