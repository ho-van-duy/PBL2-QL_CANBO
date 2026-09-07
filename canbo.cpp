#include "canbo.h"
#include <iomanip>

CanBo CanBo::danhSachCanBo[200];
int CanBo::soLuongCanBo = 0;

CanBo::CanBo() {
    maCanBo = "";
    hoTen = "";
    tuoi = 0;
    gioiTinh = "";
    diaChi = "";
    luongCoBan = 0;
    chucVu = ChucVu();
    phongBan = PhongBan();
}

CanBo::CanBo(string maCanBo, string hoTen, int tuoi, string gioiTinh,
             string diaChi, double luongCoBan, const ChucVu& chucVu,
             const PhongBan& phongBan) {
    this->maCanBo = maCanBo;
    this->hoTen = hoTen;
    this->tuoi = tuoi;
    this->gioiTinh = gioiTinh;
    this->diaChi = diaChi;
    this->luongCoBan = luongCoBan;
    this->chucVu = chucVu;
    this->phongBan = phongBan;
}

void CanBo::nhap() {
    cout << "Nhap ma can bo: ";
    getline(cin, maCanBo);
    cout << "Nhap ho ten: ";
    getline(cin, hoTen);
    cout << "Nhap tuoi: ";
    cin >> tuoi;
    cin.ignore();
    cout << "Nhap gioi tinh: ";
    getline(cin, gioiTinh);
    cout << "Nhap dia chi: ";
    getline(cin, diaChi);
    cout << "Nhap luong co ban: ";
    cin >> luongCoBan;
    cin.ignore();

    cout << "Nhap thong tin chuc vu: " << endl;
    chucVu.nhap();
    cout << "Nhap thong tin phong ban: " << endl;
    phongBan.nhap();
}

void CanBo::xuat() const {
    cout << "Ma can bo: " << maCanBo << endl;
    cout << "Ho ten: " << hoTen << endl;
    cout << "Tuoi: " << tuoi << endl;
    cout << "Gioi tinh: " << gioiTinh << endl;
    cout << "Dia chi: " << diaChi << endl;
    cout << "Luong co ban: " << luongCoBan << endl;
    cout << "Chuc vu: " << chucVu.getTenChucVu() << endl;
    cout << "Phong ban: " << phongBan.getTenPhongBan() << endl;
    cout << "Luong thuc nhan: " << tinhLuong() << endl;
}

string CanBo::getMaCanBo() const { return maCanBo; }
string CanBo::getHoTen() const { return hoTen; }
int CanBo::getTuoi() const { return tuoi; }
string CanBo::getGioiTinh() const { return gioiTinh; }
string CanBo::getDiaChi() const { return diaChi; }
double CanBo::getLuongCoBan() const { return luongCoBan; }
ChucVu CanBo::getChucVu() const { return chucVu; }
PhongBan CanBo::getPhongBan() const { return phongBan; }

void CanBo::setMaCanBo(string maCanBo) { this->maCanBo = maCanBo; }
void CanBo::setHoTen(string hoTen) { this->hoTen = hoTen; }
void CanBo::setTuoi(int tuoi) { this->tuoi = tuoi; }
void CanBo::setGioiTinh(string gioiTinh) { this->gioiTinh = gioiTinh; }
void CanBo::setDiaChi(string diaChi) { this->diaChi = diaChi; }
void CanBo::setLuongCoBan(double luongCoBan) { this->luongCoBan = luongCoBan; }
void CanBo::setChucVu(const ChucVu& chucVu) { this->chucVu = chucVu; }
void CanBo::setPhongBan(const PhongBan& phongBan) { this->phongBan = phongBan; }

double CanBo::tinhLuong() const {
    return luongCoBan * chucVu.getHeSoLuong();
}

bool CanBo::coQuyenQuanLy() const {
    return chucVu.coQuyenQuanLy();
}

bool CanBo::laCaoHon(const CanBo& other) const {
    return chucVu.laCaoHon(other.chucVu);
}

void CanBo::themCanBo(const CanBo& canBo) {
    if (soLuongCanBo < 200) {
        danhSachCanBo[soLuongCanBo++] = canBo;
    } else {
        cout << "Danh sach can bo da day!" << endl;
    }
}

void CanBo::xuatDanhSachCanBo() {
    if (soLuongCanBo == 0) {
        cout << "Danh sach can bo trong." << endl;
        return;
    }

    cout << "\n=== DANH SACH CAN BO ===\n";
    cout << left << setw(12) << "Ma" << setw(18) << "Ho ten" << setw(8) << "Tuoi"
         << setw(12) << "Gioi tinh" << setw(18) << "Chuc vu" << "Luong" << endl;
    cout << string(80, '-') << endl;

    for (int i = 0; i < soLuongCanBo; i++) {
        cout << left << setw(12) << danhSachCanBo[i].getMaCanBo()
             << setw(18) << danhSachCanBo[i].getHoTen()
             << setw(8) << danhSachCanBo[i].getTuoi()
             << setw(12) << danhSachCanBo[i].getGioiTinh()
             << setw(18) << danhSachCanBo[i].getChucVu().getTenChucVu()
             << danhSachCanBo[i].tinhLuong() << endl;
    }
}

CanBo CanBo::timCanBoTheoMa(string maCanBo) {
    for (int i = 0; i < soLuongCanBo; i++) {
        if (danhSachCanBo[i].getMaCanBo() == maCanBo) {
            return danhSachCanBo[i];
        }
    }
    return CanBo();
}

int CanBo::getSoLuongCanBo() {
    return soLuongCanBo;
}
