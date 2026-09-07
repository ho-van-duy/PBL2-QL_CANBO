#ifndef CANBO_H
#define CANBO_H

#include <iostream>
#include <string>
#include "chucvu.h"
#include "phongban.h"
using namespace std;

class CanBo {
private:
    string maCanBo;
    string hoTen;
    int tuoi;
    string gioiTinh;
    string diaChi;
    double luongCoBan;
    ChucVu chucVu;
    PhongBan phongBan;

    static CanBo danhSachCanBo[200];
    static int soLuongCanBo;

public:
    CanBo();
    CanBo(string maCanBo, string hoTen, int tuoi, string gioiTinh,
          string diaChi, double luongCoBan, const ChucVu& chucVu,
          const PhongBan& phongBan);

    void nhap();
    void xuat() const;

    string getMaCanBo() const;
    string getHoTen() const;
    int getTuoi() const;
    string getGioiTinh() const;
    string getDiaChi() const;
    double getLuongCoBan() const;
    ChucVu getChucVu() const;
    PhongBan getPhongBan() const;

    void setMaCanBo(string maCanBo);
    void setHoTen(string hoTen);
    void setTuoi(int tuoi);
    void setGioiTinh(string gioiTinh);
    void setDiaChi(string diaChi);
    void setLuongCoBan(double luongCoBan);
    void setChucVu(const ChucVu& chucVu);
    void setPhongBan(const PhongBan& phongBan);

    double tinhLuong() const;
    bool coQuyenQuanLy() const;
    bool laCaoHon(const CanBo& other) const;

    static void themCanBo(const CanBo& canBo);
    static void xuatDanhSachCanBo();
    static CanBo timCanBoTheoMa(string maCanBo);
    static int getSoLuongCanBo();
};

#endif
