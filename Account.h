#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

#include "ThucThe.h"

class Account : public ThucThe {
    private:
        string maTaiKhoan;
        string username;
        string password;
        string role;
        bool trangThai;
        string maCanBo;

        static Account* ds;
        static int soLuong;
        static int sucChua;
    
    public:
        Account(const string& = "", const string& = "", const string& = "",
                const string& = "USER", const bool& = true, const string& = "");

        string getMaTaiKhoan() const;
        string getUsername() const;
        string getPassword() const;
        string getRole() const;
        bool getTrangThai() const;
        string getMaCanBo() const;

        void setMaTaiKhoan(const string&);
        void setUsername(const string&);
        void setPassword(const string&);
        void setRole(const string&);
        void setTrangThai(const bool&);
        void setMaCanBo(const string&);

        void ghiDong(ofstream& out) const override;
        void docDong(ifstream& in) override;

        void input();
        void display() const;

        void nhap() override;
        void xuat() const override;
        string loaiThucThe() const override;

        static int SoLuong() { return soLuong; }
        static void Them(const Account& a);
        static bool XoaMot(int idx);
        static Account& LayTai(int idx);
        static void DocTatCa();
        static void GhiTatCa();
};

#endif
