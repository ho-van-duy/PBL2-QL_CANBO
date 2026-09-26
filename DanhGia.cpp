#include "DanhGia.h"
#include "CanBo.h"

DanhGia* DanhGia::ds = nullptr;
int DanhGia::soLuong = 0;
int DanhGia::sucChua = 0;

DanhGia::DanhGia(const string& maDanhGia, const string& maCanBo, const int& namDanhGia,
                 const string& xepLoai, const string& nhanXet, const string& ngayDanhGia)
    : maDanhGia(maDanhGia), maCanBo(maCanBo), namDanhGia(namDanhGia),
      xepLoai(xepLoai), nhanXet(nhanXet), ngayDanhGia(ngayDanhGia) { }

void DanhGia::nhap() {
    cout << "Nhap ma can bo: ";
    getline(cin, maCanBo);
    do {
        cout << "Nhap nam danh gia: ";
        if (!(cin >> namDanhGia)) {
            cin.clear();
            cin.ignore(1000, '\n');
            namDanhGia = 0;
            continue;
        }
        cin.ignore(1000, '\n');
    } while (namDanhGia <= 0);
    do {
        cout << "Nhap xep loai (Gioi/Kha/TrungBinh/Yeu): ";
        getline(cin, xepLoai);
    } while (xepLoai != "Gioi" && xepLoai != "Kha" &&
             xepLoai != "TrungBinh" && xepLoai != "Yeu");
    cout << "Nhap nhan xet: ";
    getline(cin, nhanXet);
    do {
        cout << "Nhap ngay danh gia (dd-MM-yyyy): ";
        getline(cin, ngayDanhGia);
    } while (!NgayHopLe(ngayDanhGia));
}

void DanhGia::xuat() const {
    cout << "Ma danh gia: " << maDanhGia
         << " | Ma can bo: " << maCanBo
         << " | Nam: " << namDanhGia
         << " | Xep loai: " << xepLoai
         << " | Nhan xet: " << nhanXet
         << " | Ngay danh gia: " << ngayDanhGia
         << endl;
}

void DanhGia::ghiDong(ofstream& out) const {
    out << maDanhGia << '|' << maCanBo << '|' << namDanhGia << '|'
        << xepLoai << '|' << nhanXet << '|' << ngayDanhGia << endl;
}

void DanhGia::docDong(ifstream& in) {
    getline(in, maDanhGia, '|');
    getline(in, maCanBo, '|');
    string namStr;
    getline(in, namStr, '|');
    if (!namStr.empty()) namDanhGia = stoi(namStr);
    getline(in, xepLoai, '|');
    getline(in, nhanXet, '|');
    getline(in, ngayDanhGia);
}

string DanhGia::GetMaDG() const { return maDanhGia; }
string DanhGia::GetMaCanBo() const { return maCanBo; }
int DanhGia::GetNamDG() const { return namDanhGia; }
string DanhGia::GetXepLoai() const { return xepLoai; }
string DanhGia::GetNhanXet() const { return nhanXet; }
string DanhGia::GetNgayDanhGia() const { return ngayDanhGia; }

void DanhGia::SetMaDG(const string& maDanhGia) { this->maDanhGia = maDanhGia; }
void DanhGia::SetMaCanBo(const string& maCanBo) { this->maCanBo = maCanBo; }
void DanhGia::SetNamDG(const int& namDanhGia) { this->namDanhGia = namDanhGia; }
void DanhGia::SetXepLoai(const string& xepLoai) { this->xepLoai = xepLoai; }
void DanhGia::SetNhanXet(const string& nhanXet) { this->nhanXet = nhanXet; }
void DanhGia::SetNgayDanhGia(const string& ngayDanhGia) { this->ngayDanhGia = ngayDanhGia; }

void DanhGia::Them(const DanhGia& a) {
    if (soLuong == sucChua) {
        sucChua = (sucChua == 0) ? 2 : sucChua * 2;
        DanhGia* moi = new DanhGia[sucChua];
        for (int i = 0; i < soLuong; i++) moi[i] = ds[i];
        delete[] ds;
        ds = moi;
    }
    ds[soLuong++] = a;
}

bool DanhGia::XoaMot(int idx) {
    if (idx < 0 || idx >= soLuong) return false;
    for (int i = idx; i < soLuong - 1; i++) ds[i] = ds[i + 1];
    soLuong--;
    return true;
}

DanhGia& DanhGia::LayTai(int idx) { return ds[idx]; }

void DanhGia::DocTatCa() {
    ifstream in("data/danhgia.txt");
    if (!in) return;
    soLuong = 0;
    while (true) {
        DanhGia a;
        a.docDong(in);
        if (!in) break;
        Them(a);
    }
    in.close();
}

void DanhGia::GhiTatCa() {
    ofstream out("data/danhgia.txt");
    if (!out) return;
    for (int i = 0; i < soLuong; i++) ds[i].ghiDong(out);
    out.close();
}