#include "PhongBan.h"

PhongBan* PhongBan::ds = nullptr;
int PhongBan::soLuong = 0;
int PhongBan::sucChua = 0;

PhongBan::PhongBan(const string& maPhong, const string& tenPhong, const string& moTa)
    : maPhong(maPhong), tenPhong(tenPhong), moTa(moTa) { }

void PhongBan::nhap() {
    cout << "Nhap ma phong: ";
    getline(cin, maPhong);
    cout << "Nhap ten phong: ";
    getline(cin, tenPhong);
    cout << "Nhap mo ta: ";
    getline(cin, moTa);
}

void PhongBan::xuat() const {
    cout << "Ma phong: " << maPhong
         << " | Ten phong: " << tenPhong
         << " | Mo ta: " << moTa << endl;
}

void PhongBan::ghiDong(ofstream& out) const {
    out << maPhong << '|' << tenPhong << '|' << moTa << endl;
}

void PhongBan::docDong(ifstream& in) {
    getline(in, maPhong, '|');
    getline(in, tenPhong, '|');
    getline(in, moTa);
}

string PhongBan::GetMaPhong() const { return maPhong; }
string PhongBan::GetTenPhong() const { return tenPhong; }
string PhongBan::GetMoTa() const { return moTa; }

void PhongBan::SetMaPhong(const string& maPhong) { this->maPhong = maPhong; }
void PhongBan::SetTenPhong(const string& tenPhong) { this->tenPhong = tenPhong; }
void PhongBan::SetMoTa(const string& moTa) { this->moTa = moTa; }

void PhongBan::Them(const PhongBan& a) {
    if (soLuong == sucChua) {
        sucChua = (sucChua == 0) ? 2 : sucChua * 2;
        PhongBan* moi = new PhongBan[sucChua];
        for (int i = 0; i < soLuong; i++) moi[i] = ds[i];
        delete[] ds;
        ds = moi;
    }
    ds[soLuong++] = a;
}

bool PhongBan::XoaMot(int idx) {
    if (idx < 0 || idx >= soLuong) return false;
    for (int i = idx; i < soLuong - 1; i++) ds[i] = ds[i + 1];
    soLuong--;
    return true;
}

PhongBan& PhongBan::LayTai(int idx) { return ds[idx]; }

void PhongBan::DocTatCa() {
    ifstream in("data/phongban.txt");
    if (!in) return;
    soLuong = 0;
    while (true) {
        PhongBan a;
        a.docDong(in);
        if (!in) break;
        Them(a);
    }
    in.close();
}

void PhongBan::GhiTatCa() {
    ofstream out("data/phongban.txt");
    if (!out) return;
    for (int i = 0; i < soLuong; i++) ds[i].ghiDong(out);
    out.close();
}