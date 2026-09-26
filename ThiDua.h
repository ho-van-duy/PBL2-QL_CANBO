#ifndef THIDUA_H
#define THIDUA_H

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class ThiDua {
private:
    string maSuKien;
    string maCanBo;
    string loaiSuKien;
    string noiDung;
    int nam;
    string lyDo;

    static ThiDua* ds;
    static int soLuong;
    static int sucChua;

public:
    ThiDua(const string& = "", const string& = "", const string& = "",
           const string& = "", const int& = 0, const string& = "");

    void nhap();
    void xuat() const;
    void ghiDong(ofstream& out) const;
    void docDong(ifstream& in);

    string GetMaSK() const;
    string GetMaCanBo() const;
    string GetLoaiSK() const;
    string GetNoiDung() const;
    int GetNam() const;
    string GetLyDo() const;

    void SetMaSK(const string&);
    void SetMaCanBo(const string&);
    void SetLoaiSK(const string&);
    void SetNoiDung(const string&);
    void SetNam(const int&);
    void SetLyDo(const string&);

    static int SoLuong() { return soLuong; }
    static void Them(const ThiDua& a);
    static bool XoaMot(int idx);
    static ThiDua& LayTai(int idx);
    static void DocTatCa();
    static void GhiTatCa();
};

#endif