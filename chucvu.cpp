#include "chucvu.h"
#include <iomanip>

ChucVu ChucVu::danhSachChucVu[100];
int ChucVu::soLuongChucVu = 0;

ChucVu::ChucVu() {
    maChucVu = "";
    tenChucVu = "";
    heSoLuong = 0;
    capBac = 0;
    quyenHan = "";
    moTa = "";
}

ChucVu::ChucVu(string maChucVu, string tenChucVu, int heSoLuong, int capBac,
               string quyenHan, string moTa) {
    this->maChucVu = maChucVu;
    this->tenChucVu = tenChucVu;
    this->heSoLuong = heSoLuong;
    this->capBac = capBac;
    this->quyenHan = quyenHan;
    this->moTa = moTa;
}

void ChucVu::nhap() {
    cout << "Nhap ma chuc vu: ";
    getline(cin, maChucVu);
    cout << "Nhap ten chuc vu: ";
    getline(cin, tenChucVu);
    cout << "Nhap he so luong: ";
    cin >> heSoLuong;
    cout << "Nhap cap bac: ";
    cin >> capBac;
    cin.ignore();
    cout << "Nhap quyen han: ";
    getline(cin, quyenHan);
    cout << "Nhap mo ta: ";
    getline(cin, moTa);
}

void ChucVu::xuat() const {
    cout << "Ma chuc vu: " << maChucVu << endl;
    cout << "Ten chuc vu: " << tenChucVu << endl;
    cout << "He so luong: " << heSoLuong << endl;
    cout << "Cap bac: " << capBac << endl;
    cout << "Quyen han: " << quyenHan << endl;
    cout << "Mo ta: " << moTa << endl;
}

string ChucVu::getMaChucVu() const { return maChucVu; }
string ChucVu::getTenChucVu() const { return tenChucVu; }
int ChucVu::getHeSoLuong() const { return heSoLuong; }
int ChucVu::getCapBac() const { return capBac; }
string ChucVu::getQuyenHan() const { return quyenHan; }
string ChucVu::getMoTa() const { return moTa; }

void ChucVu::setMaChucVu(string maChucVu) { this->maChucVu = maChucVu; }
void ChucVu::setTenChucVu(string tenChucVu) { this->tenChucVu = tenChucVu; }
void ChucVu::setHeSoLuong(int heSoLuong) { this->heSoLuong = heSoLuong; }
void ChucVu::setCapBac(int capBac) { this->capBac = capBac; }
void ChucVu::setQuyenHan(string quyenHan) { this->quyenHan = quyenHan; }
void ChucVu::setMoTa(string moTa) { this->moTa = moTa; }

bool ChucVu::laCaoHon(const ChucVu& other) const {
    return capBac > other.capBac;
}

bool ChucVu::coQuyenQuanLy() const {
    return capBac >= 3;
}

double ChucVu::tinhLuong(double luongCoBan) const {
    return luongCoBan * heSoLuong;
}

void ChucVu::themChucVu(const ChucVu& chucVu) {
    if (soLuongChucVu < 100) {
        danhSachChucVu[soLuongChucVu++] = chucVu;
    } else {
        cout << "Danh sach chuc vu da day!" << endl;
    }
}

void ChucVu::xuatDanhSachChucVu() {
    if (soLuongChucVu == 0) {
        cout << "Danh sach chuc vu trong." << endl;
        return;
    }

    cout << "\n=== DANH SACH CHUC VU ===\n";
    cout << left << setw(15) << "Ma" << setw(20) << "Ten chuc vu"
         << setw(12) << "He so" << setw(8) << "Cap bac" << "Quyen han" << endl;
    cout << string(70, '-') << endl;

    for (int i = 0; i < soLuongChucVu; i++) {
        cout << left << setw(15) << danhSachChucVu[i].getMaChucVu()
             << setw(20) << danhSachChucVu[i].getTenChucVu()
             << setw(12) << danhSachChucVu[i].getHeSoLuong()
             << setw(8) << danhSachChucVu[i].getCapBac()
             << danhSachChucVu[i].getQuyenHan() << endl;
    }
}

ChucVu ChucVu::timChucVuTheoMa(string maChucVu) {
    for (int i = 0; i < soLuongChucVu; i++) {
        if (danhSachChucVu[i].getMaChucVu() == maChucVu) {
            return danhSachChucVu[i];
        }
    }
    return ChucVu();
}

int ChucVu::getSoLuongChucVu() {
    return soLuongChucVu;
}
