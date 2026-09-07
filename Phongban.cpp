#include "phongban.h"
#include <iomanip>

PhongBan PhongBan::danhSachPhongBan[100];
int PhongBan::soLuongPhongBan = 0;

PhongBan::PhongBan() {
    maPhongBan = "";
    tenPhongBan = "";
    soNhanVien = 0;
    diaDiem = "";
}

PhongBan::PhongBan(string maPhongBan, string tenPhongBan, int soNhanVien, string diaDiem) {
    this->maPhongBan = maPhongBan;
    this->tenPhongBan = tenPhongBan;
    this->soNhanVien = soNhanVien;
    this->diaDiem = diaDiem;
}

void PhongBan::nhap() {
    cout << "Nhap ma phong ban: ";
    getline(cin, maPhongBan);
    cout << "Nhap ten phong ban: ";
    getline(cin, tenPhongBan);
    cout << "Nhap so nhan vien: ";
    cin >> soNhanVien;
    cin.ignore();
    cout << "Nhap dia diem: ";
    getline(cin, diaDiem);
}

void PhongBan::xuat() const {
    cout << "Ma phong ban: " << maPhongBan << endl;
    cout << "Ten phong ban: " << tenPhongBan << endl;
    cout << "So nhan vien: " << soNhanVien << endl;
    cout << "Dia diem: " << diaDiem << endl;
}

string PhongBan::getMaPhongBan() const { return maPhongBan; }
string PhongBan::getTenPhongBan() const { return tenPhongBan; }
int PhongBan::getSoNhanVien() const { return soNhanVien; }
string PhongBan::getDiaDiem() const { return diaDiem; }

void PhongBan::setMaPhongBan(string maPhongBan) { this->maPhongBan = maPhongBan; }
void PhongBan::setTenPhongBan(string tenPhongBan) { this->tenPhongBan = tenPhongBan; }
void PhongBan::setSoNhanVien(int soNhanVien) { this->soNhanVien = soNhanVien; }
void PhongBan::setDiaDiem(string diaDiem) { this->diaDiem = diaDiem; }

void PhongBan::themPhongBan(const PhongBan& phongBan) {
    if (soLuongPhongBan < 100) {
        danhSachPhongBan[soLuongPhongBan++] = phongBan;
    } else {
        cout << "Danh sach phong ban da day!" << endl;
    }
}

void PhongBan::xuatDanhSachPhongBan() {
    if (soLuongPhongBan == 0) {
        cout << "Danh sach phong ban trong." << endl;
        return;
    }

    cout << "\n=== DANH SACH PHONG BAN ===\n";
    cout << left << setw(15) << "Ma" << setw(25) << "Ten phong ban" << setw(12) << "So NV" << "Dia diem" << endl;
    cout << string(70, '-') << endl;

    for (int i = 0; i < soLuongPhongBan; i++) {
        cout << left << setw(15) << danhSachPhongBan[i].getMaPhongBan()
             << setw(25) << danhSachPhongBan[i].getTenPhongBan()
             << setw(12) << danhSachPhongBan[i].getSoNhanVien()
             << danhSachPhongBan[i].getDiaDiem() << endl;
    }
}

PhongBan PhongBan::timPhongBanTheoMa(string maPhongBan) {
    for (int i = 0; i < soLuongPhongBan; i++) {
        if (danhSachPhongBan[i].getMaPhongBan() == maPhongBan) {
            return danhSachPhongBan[i];
        }
    }
    return PhongBan();
}

int PhongBan::getSoLuongPhongBan() {
    return soLuongPhongBan;
}
