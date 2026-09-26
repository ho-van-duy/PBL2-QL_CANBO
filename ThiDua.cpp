#include "ThiDua.h"

ThiDua* ThiDua::ds = nullptr;
int ThiDua::soLuong = 0;
int ThiDua::sucChua = 0;

ThiDua::ThiDua(const string& maSuKien, const string& maCanBo, const string& loaiSuKien,
               const string& noiDung, const int& nam, const string& lyDo)
    : maSuKien(maSuKien), maCanBo(maCanBo), loaiSuKien(loaiSuKien),
      noiDung(noiDung), nam(nam), lyDo(lyDo) { }

void ThiDua::nhap() {
    cout << "Nhap ma can bo: ";
    getline(cin, maCanBo);
    do {
        cout << "Nhap loai su kien (KHEN_THUONG/KY_LUAT): ";
        getline(cin, loaiSuKien);
    } while (loaiSuKien != "KHEN_THUONG" && loaiSuKien != "KY_LUAT");
    cout << "Nhap noi dung: ";
    getline(cin, noiDung);
    do {
        cout << "Nhap nam su kien: ";
        if (!(cin >> nam)) {
            cin.clear();
            cin.ignore(1000, '\n');
            nam = 0;
            continue;
        }
        cin.ignore(1000, '\n');
    } while (nam <= 0);
    cout << "Nhap ly do: ";
    getline(cin, lyDo);
}

void ThiDua::xuat() const {
    ThucThe::xuat();
    cout << "Ma su kien: " << maSuKien
         << " | Ma can bo: " << maCanBo
         << " | Loai: " << loaiSuKien
         << " | Noi dung: " << noiDung
         << " | Nam: " << nam
         << " | Ly do: " << lyDo << endl;
}

string ThiDua::loaiThucThe() const { return "KHEN_THUONG_KY_LUAT"; }

void ThiDua::ghiDong(ofstream& out) const {
    out << maSuKien << '|' << maCanBo << '|' << loaiSuKien << '|'
        << noiDung << '|' << nam << '|' << lyDo << endl;
}

void ThiDua::docDong(ifstream& in) {
    getline(in, maSuKien, '|');
    getline(in, maCanBo, '|');
    getline(in, loaiSuKien, '|');
    getline(in, noiDung, '|');
    string namStr;
    getline(in, namStr, '|');
    if (!namStr.empty()) nam = stoi(namStr);
    getline(in, lyDo);
}

string ThiDua::GetMaSK() const { return maSuKien; }
string ThiDua::GetMaCanBo() const { return maCanBo; }
string ThiDua::GetLoaiSK() const { return loaiSuKien; }
string ThiDua::GetNoiDung() const { return noiDung; }
int ThiDua::GetNam() const { return nam; }
string ThiDua::GetLyDo() const { return lyDo; }

void ThiDua::SetMaSK(const string& maSuKien) { this->maSuKien = maSuKien; }
void ThiDua::SetMaCanBo(const string& maCanBo) { this->maCanBo = maCanBo; }
void ThiDua::SetLoaiSK(const string& loaiSuKien) { this->loaiSuKien = loaiSuKien; }
void ThiDua::SetNoiDung(const string& noiDung) { this->noiDung = noiDung; }
void ThiDua::SetNam(const int& nam) { this->nam = nam; }
void ThiDua::SetLyDo(const string& lyDo) { this->lyDo = lyDo; }

void ThiDua::Them(const ThiDua& a) {
    if (soLuong == sucChua) {
        sucChua = (sucChua == 0) ? 2 : sucChua * 2;
        ThiDua* moi = new ThiDua[sucChua];
        for (int i = 0; i < soLuong; i++) moi[i] = ds[i];
        delete[] ds;
        ds = moi;
    }
    ds[soLuong++] = a;
}

bool ThiDua::XoaMot(int idx) {
    if (idx < 0 || idx >= soLuong) return false;
    for (int i = idx; i < soLuong - 1; i++) ds[i] = ds[i + 1];
    soLuong--;
    return true;
}

ThiDua& ThiDua::LayTai(int idx) { return ds[idx]; }

void ThiDua::DocTatCa() {
    ifstream in("data/thidua.txt");
    if (!in) return;
    soLuong = 0;
    while (true) {
        ThiDua a;
        a.docDong(in);
        if (!in) break;
        Them(a);
    }
    in.close();
}

void ThiDua::GhiTatCa() {
    ofstream out("data/thidua.txt");
    if (!out) return;
    for (int i = 0; i < soLuong; i++) ds[i].ghiDong(out);
    out.close();
}