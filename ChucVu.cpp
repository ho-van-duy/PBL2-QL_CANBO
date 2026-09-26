#include "ChucVu.h"
#include <string>

ChucVu* ChucVu::ds = nullptr;
int ChucVu::soLuong = 0;
int ChucVu::sucChua = 0;

ChucVu::ChucVu(const string& maChucVu, const string& tenChucVu, const double& phuCapChucVu, const string& moTa)
    : maChucVu(maChucVu), tenChucVu(tenChucVu), phuCapChucVu(phuCapChucVu), moTa(moTa) { }

void ChucVu::nhap() {
    cout << "Nhap ten chuc vu: ";
    getline(cin, tenChucVu);
    do {
        cout << "Nhap phu cap chuc vu (>= 0): ";
        if (!(cin >> phuCapChucVu)) {
            cin.clear();
            cin.ignore(1000, '\n');
            phuCapChucVu = -1;
            continue;
        }
        cin.ignore(1000, '\n');
    } while (phuCapChucVu < 0);
    cout << "Nhap mo ta: ";
    getline(cin, moTa);
}

void ChucVu::xuat() const {
    ThucThe::xuat();
    cout << "Ma chuc vu: " << maChucVu
         << " | Ten chuc vu: " << tenChucVu
         << " | Phu cap chuc vu: " << phuCapChucVu
         << " | Mo ta: " << moTa << endl;
}

string ChucVu::loaiThucThe() const { return "CHUC_VU"; }

void ChucVu::ghiDong(ofstream& out) const {
    out << maChucVu << '|' << tenChucVu << '|' << phuCapChucVu << '|' << moTa << endl;
}

void ChucVu::docDong(ifstream& in) {
    getline(in, maChucVu, '|');
    getline(in, tenChucVu, '|');
    string phuCapStr;
    getline(in, phuCapStr, '|');
    if (!phuCapStr.empty()) phuCapChucVu = stod(phuCapStr);
    getline(in, moTa);
}

string ChucVu::GetMaCV() const { return maChucVu; }
string ChucVu::GetTenCV() const { return tenChucVu; }
double ChucVu::GetPhuCapCV() const { return phuCapChucVu; }
string ChucVu::GetMoTa() const { return moTa; }

void ChucVu::SetMaCV(const string& maChucVu) { this->maChucVu = maChucVu; }
void ChucVu::SetTenCV(const string& tenChucVu) { this->tenChucVu = tenChucVu; }
void ChucVu::SetPhuCapCV(const double& phuCapChucVu) { this->phuCapChucVu = phuCapChucVu; }
void ChucVu::SetMoTa(const string& moTa) { this->moTa = moTa; }

void ChucVu::Them(const ChucVu& a) {
    if (soLuong == sucChua) {
        sucChua = (sucChua == 0) ? 2 : sucChua * 2;
        ChucVu* moi = new ChucVu[sucChua];
        for (int i = 0; i < soLuong; i++) moi[i] = ds[i];
        delete[] ds;
        ds = moi;
    }
    ds[soLuong++] = a;
}

bool ChucVu::XoaMot(int idx) {
    if (idx < 0 || idx >= soLuong) return false;
    for (int i = idx; i < soLuong - 1; i++) ds[i] = ds[i + 1];
    soLuong--;
    return true;
}

ChucVu& ChucVu::LayTai(int idx) { return ds[idx]; }

void ChucVu::DocTatCa() {
    ifstream in("data/chucvu.txt");
    if (!in) return;
    soLuong = 0;
    while (true) {
        ChucVu a;
        a.docDong(in);
        if (!in) break;
        Them(a);
    }
    in.close();
}

void ChucVu::GhiTatCa() {
    ofstream out("data/chucvu.txt");
    if (!out) return;
    for (int i = 0; i < soLuong; i++) ds[i].ghiDong(out);
    out.close();
}