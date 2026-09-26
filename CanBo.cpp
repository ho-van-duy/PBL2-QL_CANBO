#include "CanBo.h"
#include <cctype>

CanBo* CanBo::ds = nullptr;
int CanBo::soLuong = 0;
int CanBo::sucChua = 0;

bool NgayHopLe(const string& ngay) {
    if (ngay.length() != 10) return false;
    if (ngay[2] != '-' || ngay[5] != '-') return false;
    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue;
        if (!isdigit((unsigned char)ngay[i])) return false;
    }
    return true;
}

CanBo::CanBo(const string& MaCB, const string& HoTen, const string& NgaySinh, const string& GioiTinh,
             const string& QueQuan, const string& ChuyenMon, const string& TrinhDo,
             const string& NgayVao, const string& TrangThai)
    : MaCanBo(MaCB), HoTen(HoTen), NgaySinh(NgaySinh), GioiTinh(GioiTinh),
      QueQuan(QueQuan), ChuyenMon(ChuyenMon), TrinhDo(TrinhDo),
      NgayVao(NgayVao), TrangThai(TrangThai) { }

void CanBo::nhap() {
    cout << "Nhap ho ten: ";
    getline(cin, HoTen);
    do {
        cout << "Nhap ngay sinh (dd-MM-yyyy): ";
        getline(cin, NgaySinh);
    } while (!NgayHopLe(NgaySinh));
    do {
        cout << "Nhap gioi tinh (Nam/Nu): ";
        getline(cin, GioiTinh);
    } while (GioiTinh != "Nam" && GioiTinh != "Nu");
    cout << "Nhap que quan: ";
    getline(cin, QueQuan);
    cout << "Nhap chuyen mon: ";
    getline(cin, ChuyenMon);
    cout << "Nhap trinh do: ";
    getline(cin, TrinhDo);
    do {
        cout << "Nhap ngay vao lam (dd-MM-yyyy): ";
        getline(cin, NgayVao);
    } while (!NgayHopLe(NgayVao));
    TrangThai = "DangLamViec";
}

void CanBo::xuat() const {
    ThucThe::xuat();
    cout << "Ma can bo: " << MaCanBo
         << " | Ho ten: " << HoTen
         << " | Gioi tinh: " << GioiTinh
         << " | Nam sinh: " << LayNamSinh()
         << " | Que quan: " << QueQuan
         << " | Chuyen mon: " << ChuyenMon
         << " | Trinh do: " << TrinhDo
         << " | Ngay vao lam: " << NgayVao
         << " | Trang thai: " << TrangThai << endl;
}

string CanBo::loaiThucThe() const { return "CAN_BO"; }

void CanBo::ghiDong(ofstream& out) const {
    out << MaCanBo << '|' << HoTen << '|' << NgaySinh << '|' << GioiTinh << '|'
        << QueQuan << '|' << ChuyenMon << '|' << TrinhDo << '|' << NgayVao << '|'
        << TrangThai << endl;
}

void CanBo::docDong(ifstream& in) {
    getline(in, MaCanBo, '|');
    getline(in, HoTen, '|');
    getline(in, NgaySinh, '|');
    getline(in, GioiTinh, '|');
    getline(in, QueQuan, '|');
    getline(in, ChuyenMon, '|');
    getline(in, TrinhDo, '|');
    getline(in, NgayVao, '|');
    getline(in, TrangThai);
}

string CanBo::GetMaCB() const { return MaCanBo; }
string CanBo::GetTen() const { return HoTen; }
string CanBo::GetNgaySinh() const { return NgaySinh; }
string CanBo::GetGioiTinh() const { return GioiTinh; }
string CanBo::GetQueQuan() const { return QueQuan; }
string CanBo::GetChuyenMon() const { return ChuyenMon; }
string CanBo::GetTrinhDo() const { return TrinhDo; }
string CanBo::GetNgayVao() const { return NgayVao; }
string CanBo::GetTrangThai() const { return TrangThai; }

void CanBo::SetMaCB(const string& MaCanBo) { this->MaCanBo = MaCanBo; }
void CanBo::SetTen(const string& HoTen) { this->HoTen = HoTen; }
void CanBo::SetNgaySinh(const string& NgaySinh) { this->NgaySinh = NgaySinh; }
void CanBo::SetGioiTinh(const string& GioiTinh) { this->GioiTinh = GioiTinh; }
void CanBo::SetQueQuan(const string& QueQuan) { this->QueQuan = QueQuan; }
void CanBo::SetChuyenMon(const string& ChuyenMon) { this->ChuyenMon = ChuyenMon; }
void CanBo::SetTrinhDo(const string& TrinhDo) { this->TrinhDo = TrinhDo; }
void CanBo::SetNgayVao(const string& NgayVao) { this->NgayVao = NgayVao; }
void CanBo::SetTrangThai(const string& TrangThai) { this->TrangThai = TrangThai; }

int CanBo::LayNamSinh() const {
    if (NgaySinh.length() < 10) return 0;
    return stoi(NgaySinh.substr(6, 4));
}

int CanBo::TinhTuoi() const {
    return 2026 - LayNamSinh();
}

int CanBo::TinhNamLam() const {
    if (NgayVao.length() < 10) return 0;
    return 2026 - stoi(NgayVao.substr(6, 4));
}

void CanBo::Them(const CanBo& a) {
    if (soLuong == sucChua) {
        sucChua = (sucChua == 0) ? 2 : sucChua * 2;
        CanBo* moi = new CanBo[sucChua];
        for (int i = 0; i < soLuong; i++) moi[i] = ds[i];
        delete[] ds;
        ds = moi;
    }
    ds[soLuong++] = a;
}

bool CanBo::XoaMot(int idx) {
    if (idx < 0 || idx >= soLuong) return false;
    for (int i = idx; i < soLuong - 1; i++) ds[i] = ds[i + 1];
    soLuong--;
    return true;
}

CanBo& CanBo::LayTai(int idx) { return ds[idx]; }

void CanBo::DocTatCa() {
    ifstream in("data/canbo.txt");
    if (!in) return;
    soLuong = 0;
    while (true) {
        CanBo a;
        a.docDong(in);
        if (!in) break;
        Them(a);
    }
    in.close();
}

void CanBo::GhiTatCa() {
    ofstream out("data/canbo.txt");
    if (!out) return;
    for (int i = 0; i < soLuong; i++) ds[i].ghiDong(out);
    out.close();
}