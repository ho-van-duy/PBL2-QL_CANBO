#include "NghiepVu.h"
#include "CanBo.h"
#include "PhongBan.h"
#include "ChucVu.h"
#include "PhanCong.h"
#include "Luong.h"
#include "DanhGia.h"
#include "ThiDua.h"
#include "Account.h"
#include <iomanip>
#include <cctype>
#include <algorithm>

const int CHU_KY_NANG_LUONG = 3;
const int NAM_HIEN_TAI = 2026;

static bool chuaChuoi(const string& lon, const string& con) {
    string a = lon, b = con;
    for (size_t i = 0; i < a.size(); i++) a[i] = (char)tolower((unsigned char)a[i]);
    for (size_t i = 0; i < b.size(); i++) b[i] = (char)tolower((unsigned char)b[i]);
    return a.find(b) != string::npos;
}

// ============ Khởi tạo & đăng nhập ============

void NghiepVu::khoiTao() {
    CanBo::DocTatCa();
    PhongBan::DocTatCa();
    ChucVu::DocTatCa();
    PhanCong::DocTatCa();
    Luong::DocTatCa();
    DanhGia::DocTatCa();
    ThiDua::DocTatCa();
    Account::DocTatCa();

    if (Account::SoLuong() == 0) {
        Account a;
        a.setMaTaiKhoan("TK001");
        a.setUsername("admin");
        a.setPassword("admin");
        a.setRole("ADMIN");
        a.setTrangThai(true);
        Account::Them(a);

        Account b;
        b.setMaTaiKhoan("TK002");
        b.setUsername("user");
        b.setPassword("user");
        b.setRole("USER");
        b.setTrangThai(true);
        Account::Them(b);

        Account::GhiTatCa();
    }
}

bool NghiepVu::dangNhap(string& vaiTro, string& maCanBo) {
    string username, password;
    cout << "Nhap ten dang nhap: ";
    cin >> username;
    cout << "Nhap mat khau: ";
    cin >> password;
    cin.ignore(1000, '\n');

    for (int i = 0; i < Account::SoLuong(); i++) {
        Account& a = Account::LayTai(i);
        if (a.getUsername() == username && a.getPassword() == password) {
            if (!a.getTrangThai()) {
                cout << "Tai khoan dang bi khoa!\n";
                return false;
            }
            vaiTro = a.getRole();
            maCanBo = a.getMaCanBo();
            return true;
        }
    }
    cout << "Sai ten dang nhap hoac mat khau!\n";
    return false;
}

// ============ Hàm tiện ích ============

string NghiepVu::dinhDangMa(const string& prefix, int so, int beRong) {
    string s = to_string(so);
    while ((int)s.size() < beRong) s = "0" + s;
    return prefix + s;
}

string NghiepVu::sinhMaTuDong(const string& loai) {
    string prefix;
    int beRong = 0;
    int batDauSo = 0;

    if (loai == "CAN_BO")              { prefix = "CB"; beRong = 3; batDauSo = 2; }
    else if (loai == "PHONG_BAN")      { prefix = "P";  beRong = 2; batDauSo = 1; }
    else if (loai == "CHUC_VU")        { prefix = "CV"; beRong = 2; batDauSo = 2; }
    else if (loai == "PHAN_CONG")      { prefix = "PC"; beRong = 3; batDauSo = 2; }
    else if (loai == "LICH_SU_LUONG")  { prefix = "ML"; beRong = 3; batDauSo = 2; }
    else if (loai == "DANH_GIA")       { prefix = "DG"; beRong = 3; batDauSo = 2; }
    else if (loai == "KHEN_THUONG_KY_LUAT") { prefix = "SK"; beRong = 3; batDauSo = 2; }
    else if (loai == "TAI_KHOAN")      { prefix = "TK"; beRong = 3; batDauSo = 2; }
    else return "";

    int maxSo = 0;
    for (int i = 0; i < CanBo::SoLuong(); i++) {
        if (loai == "CAN_BO" &&
            CanBo::LayTai(i).GetMaCB().substr(0, 2) == "CB") {
            maxSo = max(maxSo, stoi(CanBo::LayTai(i).GetMaCB().substr(batDauSo)));
        }
    }
    for (int i = 0; i < PhongBan::SoLuong(); i++) {
        if (loai == "PHONG_BAN" &&
            PhongBan::LayTai(i).GetMaPhong().substr(0, 1) == "P") {
            maxSo = max(maxSo, stoi(PhongBan::LayTai(i).GetMaPhong().substr(batDauSo)));
        }
    }
    for (int i = 0; i < ChucVu::SoLuong(); i++) {
        if (loai == "CHUC_VU" &&
            ChucVu::LayTai(i).GetMaCV().substr(0, 2) == "CV") {
            maxSo = max(maxSo, stoi(ChucVu::LayTai(i).GetMaCV().substr(batDauSo)));
        }
    }
    for (int i = 0; i < PhanCong::SoLuong(); i++) {
        if (loai == "PHAN_CONG" &&
            PhanCong::LayTai(i).getMaPhanCong().substr(0, 2) == "PC") {
            maxSo = max(maxSo, stoi(PhanCong::LayTai(i).getMaPhanCong().substr(batDauSo)));
        }
    }
    for (int i = 0; i < Luong::SoLuong(); i++) {
        if (loai == "LICH_SU_LUONG" &&
            Luong::LayTai(i).getMaLuong().substr(0, 2) == "ML") {
            maxSo = max(maxSo, stoi(Luong::LayTai(i).getMaLuong().substr(batDauSo)));
        }
    }
    for (int i = 0; i < DanhGia::SoLuong(); i++) {
        if (loai == "DANH_GIA" &&
            DanhGia::LayTai(i).GetMaDG().substr(0, 2) == "DG") {
            maxSo = max(maxSo, stoi(DanhGia::LayTai(i).GetMaDG().substr(batDauSo)));
        }
    }
    for (int i = 0; i < ThiDua::SoLuong(); i++) {
        if (loai == "KHEN_THUONG_KY_LUAT" &&
            ThiDua::LayTai(i).GetMaSK().substr(0, 2) == "SK") {
            maxSo = max(maxSo, stoi(ThiDua::LayTai(i).GetMaSK().substr(batDauSo)));
        }
    }
    for (int i = 0; i < Account::SoLuong(); i++) {
        if (loai == "TAI_KHOAN" &&
            Account::LayTai(i).getMaTaiKhoan().substr(0, 2) == "TK") {
            maxSo = max(maxSo, stoi(Account::LayTai(i).getMaTaiKhoan().substr(batDauSo)));
        }
    }

    return dinhDangMa(prefix, maxSo + 1, beRong);
}

string NghiepVu::dateThanhSo(const string& ngay) {
    if (ngay.length() < 10) return "";
    return ngay.substr(6, 4) + ngay.substr(3, 2) + ngay.substr(0, 2);
}

bool NghiepVu::giaoNhau(const string& tu1, const string& den1,
                        const string& tu2, const string& den2) {
    string a1 = dateThanhSo(tu1);
    string b1 = den1.empty() ? "99991231" : dateThanhSo(den1);
    string a2 = dateThanhSo(tu2);
    string b2 = den2.empty() ? "99991231" : dateThanhSo(den2);
    return (a1 <= b2) && (a2 <= b1);
}

int NghiepVu::timCanBoTheoMa(const string& ma) {
    for (int i = 0; i < CanBo::SoLuong(); i++)
        if (CanBo::LayTai(i).GetMaCB() == ma) return i;
    return -1;
}

int NghiepVu::timPhongTheoMa(const string& ma) {
    for (int i = 0; i < PhongBan::SoLuong(); i++)
        if (PhongBan::LayTai(i).GetMaPhong() == ma) return i;
    return -1;
}

int NghiepVu::timChucVuTheoMa(const string& ma) {
    for (int i = 0; i < ChucVu::SoLuong(); i++)
        if (ChucVu::LayTai(i).GetMaCV() == ma) return i;
    return -1;
}

int NghiepVu::timPhanCongTheoMa(const string& ma) {
    for (int i = 0; i < PhanCong::SoLuong(); i++)
        if (PhanCong::LayTai(i).getMaPhanCong() == ma) return i;
    return -1;
}

int NghiepVu::timLuongTheoMa(const string& ma) {
    for (int i = 0; i < Luong::SoLuong(); i++)
        if (Luong::LayTai(i).getMaLuong() == ma) return i;
    return -1;
}

int NghiepVu::timDanhGiaTheoMa(const string& ma) {
    for (int i = 0; i < DanhGia::SoLuong(); i++)
        if (DanhGia::LayTai(i).GetMaDG() == ma) return i;
    return -1;
}

int NghiepVu::timThiDuaTheoMa(const string& ma) {
    for (int i = 0; i < ThiDua::SoLuong(); i++)
        if (ThiDua::LayTai(i).GetMaSK() == ma) return i;
    return -1;
}

int NghiepVu::timTaiKhoanTheoMa(const string& ma) {
    for (int i = 0; i < Account::SoLuong(); i++)
        if (Account::LayTai(i).getMaTaiKhoan() == ma) return i;
    return -1;
}

// ============ 10 chức năng đề bài ============

void NghiepVu::themMotCanBo() {
    CanBo c;
    c.nhap();
    c.SetMaCB(sinhMaTuDong("CAN_BO"));
    CanBo::Them(c);
    CanBo::GhiTatCa();
    cout << "Da them can bo " << c.GetMaCB() << "!\n";
}

void NghiepVu::themNhieuCanBo() {
    int n = 0;
    cout << "Nhap so can bo: ";
    cin >> n;
    cin.ignore(1000, '\n');
    if (n <= 0) return;
    for (int i = 0; i < n; i++) {
        cout << "\n----- Can bo thu " << i + 1 << " -----\n";
        CanBo c;
        c.nhap();
        c.SetMaCB(sinhMaTuDong("CAN_BO"));
        CanBo::Them(c);
    }
    CanBo::GhiTatCa();
    cout << "Da them " << n << " can bo!\n";
}

void NghiepVu::hienThiDanhSach() {
    if (CanBo::SoLuong() == 0) {
        cout << "Danh sach can bo rong!\n";
        return;
    }
    for (int i = 0; i < CanBo::SoLuong(); i++) {
        CanBo& cb = CanBo::LayTai(i);
        cb.xuat();
        for (int j = 0; j < PhanCong::SoLuong(); j++) {
            PhanCong& pc = PhanCong::LayTai(j);
            if (pc.getMaCanBo() == cb.GetMaCB() && pc.HieuLuc())
                pc.xuat();
        }
    }
}

void NghiepVu::lietKeDenHanTangLuong() {
    int dem = 0;
    for (int i = 0; i < CanBo::SoLuong(); i++) {
        CanBo& cb = CanBo::LayTai(i);
        string maxTu = "";
        for (int j = 0; j < Luong::SoLuong(); j++) {
            Luong& l = Luong::LayTai(j);
            if (l.getMaCanBo() == cb.GetMaCB())
                maxTu = max(maxTu, dateThanhSo(l.getTuNgay()));
        }
        int namCuoi = 0;
        if (!maxTu.empty()) {
            namCuoi = stoi(maxTu.substr(0, 4));
        } else if (cb.GetNgayVao().length() >= 10) {
            namCuoi = stoi(cb.GetNgayVao().substr(6, 4));
        }
        if (namCuoi > 0 && NAM_HIEN_TAI - namCuoi >= CHU_KY_NANG_LUONG) {
            cb.xuat();
            dem++;
        }
    }
    if (dem == 0) cout << "Khong co can bo den han nang luong.\n";
}

void NghiepVu::demCanBoNu() {
    int dem = 0;
    for (int i = 0; i < CanBo::SoLuong(); i++)
        if (CanBo::LayTai(i).GetGioiTinh() == "Nu") dem++;
    cout << "So can bo nu: " << dem << " / " << CanBo::SoLuong() << endl;
}

void NghiepVu::tongThuNhap() {
    double tong = 0;
    for (int i = 0; i < CanBo::SoLuong(); i++) {
        string ma = CanBo::LayTai(i).GetMaCB();
        for (int j = 0; j < Luong::SoLuong(); j++) {
            Luong& l = Luong::LayTai(j);
            if (l.getMaCanBo() == ma && l.HieuLuc())
                tong += l.tinhThucLinh();
        }
    }
    cout << "Tong thu nhap toan bo can bo: "
         << fixed << setprecision(0) << tong << " dong\n";
}

void NghiepVu::lietKeCanBoCNTT() {
    int dem = 0;
    for (int i = 0; i < CanBo::SoLuong(); i++) {
        CanBo& cb = CanBo::LayTai(i);
        if (cb.GetChuyenMon() == "Cong nghe thong tin") {
            cb.xuat();
            dem++;
        }
    }
    if (dem == 0) cout << "Khong co can bo chuyen mon Cong nghe thong tin.\n";
}

void NghiepVu::lietKeCanBoGioi() {
    int dem = 0;
    for (int i = 0; i < CanBo::SoLuong(); i++) {
        CanBo& cb = CanBo::LayTai(i);
        string best = "", xl = "";
        for (int j = 0; j < DanhGia::SoLuong(); j++) {
            DanhGia& d = DanhGia::LayTai(j);
            if (d.GetMaCanBo() == cb.GetMaCB()) {
                string s = dateThanhSo(d.GetNgayDanhGia());
                if (s > best) {
                    best = s;
                    xl = d.GetXepLoai();
                }
            }
        }
        if (xl == "Gioi") {
            cb.xuat();
            dem++;
        }
    }
    if (dem == 0) cout << "Khong co can bo xep loai Gioi.\n";
}

void NghiepVu::sapXepTheoMa(bool tang) {
    int n = CanBo::SoLuong();
    if (n <= 1) return;

    int lo = 0, hi = n - 1;
    int* stack = new int[2 * n + 2];
    int top = 0;
    stack[top++] = lo;
    stack[top++] = hi;

    while (top > 0) {
        int h = stack[--top];
        int l = stack[--top];
        int i = l - 1;
        for (int j = l; j <= h - 1; j++) {
            const string& maJ = CanBo::LayTai(j).GetMaCB();
            const string& maH = CanBo::LayTai(h).GetMaCB();
            bool canHoan = (tang ? maJ < maH : maJ > maH);
            if (canHoan) {
                i++;
                CanBo tmp = CanBo::LayTai(i);
                CanBo::LayTai(i) = CanBo::LayTai(j);
                CanBo::LayTai(j) = tmp;
            }
        }
        CanBo tmp = CanBo::LayTai(i + 1);
        CanBo::LayTai(i + 1) = CanBo::LayTai(h);
        CanBo::LayTai(h) = tmp;
        int p = i + 1;

        if (p - 1 > l) { stack[top++] = l; stack[top++] = p - 1; }
        if (p + 1 < h) { stack[top++] = p + 1; stack[top++] = h; }
    }
    delete[] stack;

    CanBo::GhiTatCa();
    cout << "Da sap xep theo ma " << (tang ? "tang" : "giam") << " dan.\n";
}

void NghiepVu::xoaCanBoTheoMa() {
    string ma;
    cout << "Nhap ma can bo can xoa: ";
    cin >> ma;
    cin.ignore(1000, '\n');
    int idx = timCanBoTheoMa(ma);
    if (idx < 0) {
        cout << "Khong tim thay can bo " << ma << "!\n";
        return;
    }
    CanBo::LayTai(idx).SetTrangThai("NghiViec");
    CanBo::GhiTatCa();
    cout << "Da xoa mem can bo " << ma << " (trang thai NghiViec).\n";
}

void NghiepVu::suaThongTinCanBo() {
    string ma;
    cout << "Nhap ma can bo can sua: ";
    cin >> ma;
    cin.ignore(1000, '\n');
    int idx = timCanBoTheoMa(ma);
    if (idx < 0) {
        cout << "Khong tim thay can bo " << ma << "!\n";
        return;
    }
    cout << "Nhap lai thong tin (giu nguyen ma " << ma << "):\n";
    CanBo c;
    c.nhap();
    c.SetMaCB(ma);
    CanBo::LayTai(idx) = c;
    CanBo::GhiTatCa();
    cout << "Da cap nhat thong tin can bo " << ma << "!\n";
}

void NghiepVu::xemThongTinCaNhan(const string& maCanBo) {
    int idx = timCanBoTheoMa(maCanBo);
    if (idx < 0) {
        cout << "Tai khoan nay chua lien ket can bo nao!\n";
        return;
    }
    CanBo& cb = CanBo::LayTai(idx);
    cb.xuat();
    for (int j = 0; j < PhanCong::SoLuong(); j++) {
        PhanCong& pc = PhanCong::LayTai(j);
        if (pc.getMaCanBo() == maCanBo && pc.HieuLuc())
            pc.xuat();
    }
}

void NghiepVu::xemLuongCaNhan(const string& maCanBo) {
    int dem = 0;
    for (int i = 0; i < Luong::SoLuong(); i++) {
        if (Luong::LayTai(i).getMaCanBo() == maCanBo) {
            Luong::LayTai(i).xuat();
            dem++;
        }
    }
    if (dem == 0) cout << "Chua co ban luong nao!\n";
}

void NghiepVu::xemDanhGiaCaNhan(const string& maCanBo) {
    int dem = 0;
    for (int i = 0; i < DanhGia::SoLuong(); i++) {
        if (DanhGia::LayTai(i).GetMaCanBo() == maCanBo) {
            DanhGia::LayTai(i).xuat();
            dem++;
        }
    }
    if (dem == 0) cout << "Chua co danh gia nao!\n";
}

void NghiepVu::xemPhanCongCaNhan(const string& maCanBo) {
    int dem = 0;
    for (int i = 0; i < PhanCong::SoLuong(); i++) {
        if (PhanCong::LayTai(i).getMaCanBo() == maCanBo) {
            PhanCong::LayTai(i).xuat();
            dem++;
        }
    }
    if (dem == 0) cout << "Chua co phan cong nao!\n";
}

void NghiepVu::timKiemCanBoTheoTen() {
    string ten;
    cout << "Nhap ten can tim: ";
    getline(cin, ten);
    if (ten.empty()) {
        cout << "Ten tim khong duoc rong!\n";
        return;
    }
    int dem = 0;
    for (int i = 0; i < CanBo::SoLuong(); i++) {
        CanBo& cb = CanBo::LayTai(i);
        if (chuaChuoi(cb.GetTen(), ten)) {
            cb.xuat();
            dem++;
        }
    }
    if (dem == 0) cout << "Khong tim thay can bo nao.\n";
    else cout << "Tim thay " << dem << " can bo.\n";
}

// ============ Quản lý tài nguyên ============

void NghiepVu::themPhongBan() {
    PhongBan p;
    p.nhap();
    p.SetMaPhong(sinhMaTuDong("PHONG_BAN"));
    PhongBan::Them(p);
    PhongBan::GhiTatCa();
    cout << "Da them phong ban " << p.GetMaPhong() << "!\n";
}

void NghiepVu::xemPhongBan() {
    if (PhongBan::SoLuong() == 0) {
        cout << "Danh sach phong ban rong!\n";
        return;
    }
    for (int i = 0; i < PhongBan::SoLuong(); i++)
        PhongBan::LayTai(i).xuat();
}

void NghiepVu::xoaPhongBanTheoMa() {
    string ma;
    cout << "Nhap ma phong can xoa: ";
    cin >> ma;
    cin.ignore(1000, '\n');
    for (int i = 0; i < PhanCong::SoLuong(); i++) {
        if (PhanCong::LayTai(i).getMaPhong() == ma) {
            cout << "Khong xoa duoc - phong dang duoc phan cong!\n";
            return;
        }
    }
    int idx = timPhongTheoMa(ma);
    if (idx < 0) {
        cout << "Khong tim thay phong " << ma << "!\n";
        return;
    }
    PhongBan::XoaMot(idx);
    PhongBan::GhiTatCa();
    cout << "Da xoa phong ban " << ma << "!\n";
}

void NghiepVu::themChucVu() {
    ChucVu c;
    c.nhap();
    c.SetMaCV(sinhMaTuDong("CHUC_VU"));
    ChucVu::Them(c);
    ChucVu::GhiTatCa();
    cout << "Da them chuc vu " << c.GetMaCV() << "!\n";
}

void NghiepVu::xemChucVu() {
    if (ChucVu::SoLuong() == 0) {
        cout << "Danh sach chuc vu rong!\n";
        return;
    }
    for (int i = 0; i < ChucVu::SoLuong(); i++)
        ChucVu::LayTai(i).xuat();
}

void NghiepVu::xoaChucVuTheoMa() {
    string ma;
    cout << "Nhap ma chuc vu can xoa: ";
    cin >> ma;
    cin.ignore(1000, '\n');
    for (int i = 0; i < PhanCong::SoLuong(); i++) {
        if (PhanCong::LayTai(i).getMaChucVu() == ma) {
            cout << "Khong xoa duoc - chuc vu dang duoc phan cong!\n";
            return;
        }
    }
    int idx = timChucVuTheoMa(ma);
    if (idx < 0) {
        cout << "Khong tim thay chuc vu " << ma << "!\n";
        return;
    }
    ChucVu::XoaMot(idx);
    ChucVu::GhiTatCa();
    cout << "Da xoa chuc vu " << ma << "!\n";
}

void NghiepVu::themPhanCong() {
    PhanCong pc;
    pc.nhap();
    pc.setMaPhanCong(sinhMaTuDong("PHAN_CONG"));

    if (timCanBoTheoMa(pc.getMaCanBo()) < 0) {
        cout << "Ma can bo khong ton tai!\n";
        return;
    }
    if (timPhongTheoMa(pc.getMaPhong()) < 0) {
        cout << "Ma phong khong ton tai!\n";
        return;
    }
    if (timChucVuTheoMa(pc.getMaChucVu()) < 0) {
        cout << "Ma chuc vu khong ton tai!\n";
        return;
    }

    if (pc.getLaPhongChinh()) {
        for (int i = 0; i < PhanCong::SoLuong(); i++) {
            PhanCong& x = PhanCong::LayTai(i);
            if (x.getMaCanBo() == pc.getMaCanBo() &&
                x.getLaPhongChinh() &&
                giaoNhau(pc.getTuNgay(), pc.getDenNgay(), x.getTuNgay(), x.getDenNgay())) {
                cout << "Vi pham C2 - can bo da co phong chinh trong thoi gian nay!\n";
                return;
            }
        }
    }

    PhanCong::Them(pc);
    PhanCong::GhiTatCa();
    cout << "Da them phan cong " << pc.getMaPhanCong() << "!\n";
}

void NghiepVu::xemPhanCong() {
    if (PhanCong::SoLuong() == 0) {
        cout << "Khong co phan cong nao!\n";
        return;
    }
    for (int i = 0; i < PhanCong::SoLuong(); i++)
        PhanCong::LayTai(i).xuat();
}

void NghiepVu::themLuong() {
    Luong l;
    l.nhap();
    l.setMaLuong(sinhMaTuDong("LICH_SU_LUONG"));

    if (timCanBoTheoMa(l.getMaCanBo()) < 0) {
        cout << "Ma can bo khong ton tai!\n";
        return;
    }
    for (int i = 0; i < Luong::SoLuong(); i++) {
        Luong& x = Luong::LayTai(i);
        if (x.getMaCanBo() == l.getMaCanBo() &&
            giaoNhau(l.getTuNgay(), l.getDenNgay(), x.getTuNgay(), x.getDenNgay())) {
            cout << "Vi pham C3 - trung thoi gian voi ban luong da co!\n";
            return;
        }
    }

    Luong::Them(l);
    Luong::GhiTatCa();
    cout << "Da them luong " << l.getMaLuong() << "!\n";
}

void NghiepVu::xemLuongTheoCanBo() {
    string ma;
    cout << "Nhap ma can bo: ";
    cin >> ma;
    cin.ignore(1000, '\n');
    xemLuongCaNhan(ma);
}

void NghiepVu::themDanhGia() {
    DanhGia d;
    d.nhap();
    d.SetMaDG(sinhMaTuDong("DANH_GIA"));

    if (timCanBoTheoMa(d.GetMaCanBo()) < 0) {
        cout << "Ma can bo khong ton tai!\n";
        return;
    }

    DanhGia::Them(d);
    DanhGia::GhiTatCa();
    cout << "Da them danh gia " << d.GetMaDG() << "!\n";
}

void NghiepVu::xemDanhGiaTheoCanBo() {
    string ma;
    cout << "Nhap ma can bo: ";
    cin >> ma;
    cin.ignore(1000, '\n');
    xemDanhGiaCaNhan(ma);
}

void NghiepVu::themThiDua() {
    ThiDua t;
    t.nhap();
    t.SetMaSK(sinhMaTuDong("KHEN_THUONG_KY_LUAT"));

    if (timCanBoTheoMa(t.GetMaCanBo()) < 0) {
        cout << "Ma can bo khong ton tai!\n";
        return;
    }

    ThiDua::Them(t);
    ThiDua::GhiTatCa();
    cout << "Da them su kien " << t.GetMaSK() << "!\n";
}

void NghiepVu::xemThiDuaTheoCanBo() {
    string ma;
    cout << "Nhap ma can bo: ";
    cin >> ma;
    cin.ignore(1000, '\n');
    int dem = 0;
    for (int i = 0; i < ThiDua::SoLuong(); i++) {
        if (ThiDua::LayTai(i).GetMaCanBo() == ma) {
            ThiDua::LayTai(i).xuat();
            dem++;
        }
    }
    if (dem == 0) cout << "Chua co khen thuong/ky luat nao!\n";
}

void NghiepVu::themTaiKhoan() {
    Account a;
    a.input();
    a.setMaTaiKhoan(sinhMaTuDong("TAI_KHOAN"));
    a.setTrangThai(true);

    for (int i = 0; i < Account::SoLuong(); i++) {
        if (Account::LayTai(i).getUsername() == a.getUsername()) {
            cout << "Ten dang nhap da ton tai!\n";
            return;
        }
    }

    string vaiTro;
    do {
        cout << "Nhap vai tro (ADMIN/USER): ";
        getline(cin, vaiTro);
    } while (vaiTro != "ADMIN" && vaiTro != "USER");
    a.setRole(vaiTro);

    string maCanBo;
    cout << "Nhap ma can bo lien ket (bo trong neu chua co): ";
    getline(cin, maCanBo);
    if (!maCanBo.empty()) {
        if (timCanBoTheoMa(maCanBo) < 0) {
            cout << "Ma can bo khong ton tai!\n";
            return;
        }
        a.setMaCanBo(maCanBo);
    }

    Account::Them(a);
    Account::GhiTatCa();
    cout << "Da tao tai khoan " << a.getUsername() << "!\n";
}

void NghiepVu::khoaMoKhoaTaiKhoan() {
    string username;
    cout << "Nhap ten dang nhap: ";
    getline(cin, username);
    int idx = -1;
    for (int i = 0; i < Account::SoLuong(); i++) {
        if (Account::LayTai(i).getUsername() == username) {
            idx = i;
            break;
        }
    }
    if (idx < 0) {
        cout << "Khong tim thay tai khoan " << username << "!\n";
        return;
    }
    Account& a = Account::LayTai(idx);
    a.setTrangThai(!a.getTrangThai());
    Account::GhiTatCa();
    cout << "Trang thai tai khoan " << username << " la: "
         << (a.getTrangThai() ? "HoatDong" : "BiKhoa") << endl;
}

void NghiepVu::xemTaiKhoan() {
    if (Account::SoLuong() == 0) {
        cout << "Chua co tai khoan nao!\n";
        return;
    }
    for (int i = 0; i < Account::SoLuong(); i++)
        Account::LayTai(i).xuat();
}

void NghiepVu::thongKeBaoCao() {
    int nu = 0, cntt = 0, gioi = 0, denHan = 0;
    double tong = 0;

    for (int i = 0; i < CanBo::SoLuong(); i++) {
        CanBo& cb = CanBo::LayTai(i);
        if (cb.GetGioiTinh() == "Nu") nu++;
        if (cb.GetChuyenMon() == "Cong nghe thong tin") cntt++;

        string best = "", xl = "";
        for (int j = 0; j < DanhGia::SoLuong(); j++) {
            DanhGia& d = DanhGia::LayTai(j);
            if (d.GetMaCanBo() == cb.GetMaCB()) {
                string s = dateThanhSo(d.GetNgayDanhGia());
                if (s > best) { best = s; xl = d.GetXepLoai(); }
            }
        }
        if (xl == "Gioi") gioi++;

        string maxTu = "";
        for (int j = 0; j < Luong::SoLuong(); j++) {
            Luong& l = Luong::LayTai(j);
            if (l.getMaCanBo() == cb.GetMaCB()) {
                maxTu = max(maxTu, dateThanhSo(l.getTuNgay()));
                if (l.HieuLuc()) tong += l.tinhThucLinh();
            }
        }
        int namCuoi = 0;
        if (!maxTu.empty()) namCuoi = stoi(maxTu.substr(0, 4));
        else if (cb.GetNgayVao().length() >= 10) namCuoi = stoi(cb.GetNgayVao().substr(6, 4));
        if (namCuoi > 0 && NAM_HIEN_TAI - namCuoi >= CHU_KY_NANG_LUONG) denHan++;
    }

    cout << "===== BAO CAO THONG KE =====\n";
    cout << "Tong can bo:            " << CanBo::SoLuong() << endl;
    cout << "So can bo nu:           " << nu << endl;
    cout << "So can bo chuyen CNTT:  " << cntt << endl;
    cout << "So can bo xep loai Gioi: " << gioi << endl;
    cout << "So can bo den han tang luong (>= " << CHU_KY_NANG_LUONG << " nam): " << denHan << endl;
    cout << "Tong thu nhap:          " << fixed << setprecision(0) << tong << " dong" << endl;
    cout << "So phong ban:           " << PhongBan::SoLuong() << endl;
    cout << "So chuc vu:             " << ChucVu::SoLuong() << endl;
    cout << "So phan cong:           " << PhanCong::SoLuong() << endl;
    cout << "So ban luong:           " << Luong::SoLuong() << endl;
    cout << "So danh gia:            " << DanhGia::SoLuong() << endl;
    cout << "So khen thuong/ky luat: " << ThiDua::SoLuong() << endl;
    cout << "So tai khoan:           " << Account::SoLuong() << endl;
}