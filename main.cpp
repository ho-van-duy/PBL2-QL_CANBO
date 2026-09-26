#include "NghiepVu.h"
#include <iostream>
using namespace std;

int chonMenu(const string& ten, int min, int max) {
    while (true) {
        cout << ten << ": ";
        int chon;
        if (!(cin >> chon)) {
            cin.clear();
            cin.ignore(1000, '\n');
            return -1;
        }
        cin.ignore(1000, '\n');
        if (chon >= min && chon <= max) return chon;
        cout << "Lua chon khong hop le!\n";
    }
}

void menuQuanLyCanBo() {
    while (true) {
        cout << "\n--- QUAN LY CAN BO ---\n"
             << "1. Them mot can bo\n"
             << "2. Them nhieu can bo\n"
             << "3. Xem danh sach can bo\n"
             << "4. Sua thong tin can bo\n"
             << "5. Xoa can bo theo ma\n"
             << "0. Quay lai\n";
        int chon = chonMenu("Chon", 0, 5);
        if (chon == -1 || chon == 0) return;
        if (chon == 1) NghiepVu::themMotCanBo();
        else if (chon == 2) NghiepVu::themNhieuCanBo();
        else if (chon == 3) NghiepVu::hienThiDanhSach();
        else if (chon == 4) NghiepVu::suaThongTinCanBo();
        else if (chon == 5) NghiepVu::xoaCanBoTheoMa();
    }
}

void menuQuanLyPhongBan() {
    while (true) {
        cout << "\n--- QUAN LY PHONG BAN ---\n"
             << "1. Them phong ban\n"
             << "2. Xem danh sach phong ban\n"
             << "3. Xoa phong ban theo ma\n"
             << "0. Quay lai\n";
        int chon = chonMenu("Chon", 0, 3);
        if (chon == -1 || chon == 0) return;
        if (chon == 1) NghiepVu::themPhongBan();
        else if (chon == 2) NghiepVu::xemPhongBan();
        else NghiepVu::xoaPhongBanTheoMa();
    }
}

void menuQuanLyChucVu() {
    while (true) {
        cout << "\n--- QUAN LY CHUC VU ---\n"
             << "1. Them chuc vu\n"
             << "2. Xem danh sach chuc vu\n"
             << "3. Xoa chuc vu theo ma\n"
             << "0. Quay lai\n";
        int chon = chonMenu("Chon", 0, 3);
        if (chon == -1 || chon == 0) return;
        if (chon == 1) NghiepVu::themChucVu();
        else if (chon == 2) NghiepVu::xemChucVu();
        else NghiepVu::xoaChucVuTheoMa();
    }
}

void menuPhanCong() {
    while (true) {
        cout << "\n--- PHAN CONG PHONG BAN & CHUC VU ---\n"
             << "1. Them phan cong\n"
             << "2. Xem danh sach phan cong\n"
             << "0. Quay lai\n";
        int chon = chonMenu("Chon", 0, 2);
        if (chon == -1 || chon == 0) return;
        if (chon == 1) NghiepVu::themPhanCong();
        else NghiepVu::xemPhanCong();
    }
}

void menuQuanLyLuong() {
    while (true) {
        cout << "\n--- QUAN LY LUONG ---\n"
             << "1. Them ban luong\n"
             << "2. Xem luong theo can bo\n"
             << "0. Quay lai\n";
        int chon = chonMenu("Chon", 0, 2);
        if (chon == -1 || chon == 0) return;
        if (chon == 1) NghiepVu::themLuong();
        else NghiepVu::xemLuongTheoCanBo();
    }
}

void menuDanhGia() {
    while (true) {
        cout << "\n--- DANH GIA CAN BO ---\n"
             << "1. Them danh gia\n"
             << "2. Xem danh gia theo can bo\n"
             << "0. Quay lai\n";
        int chon = chonMenu("Chon", 0, 2);
        if (chon == -1 || chon == 0) return;
        if (chon == 1) NghiepVu::themDanhGia();
        else NghiepVu::xemDanhGiaTheoCanBo();
    }
}

void menuKhenThuong() {
    while (true) {
        cout << "\n--- KHEN THUONG / KY LUAT ---\n"
             << "1. Them su kien\n"
             << "2. Xem su kien theo can bo\n"
             << "0. Quay lai\n";
        int chon = chonMenu("Chon", 0, 2);
        if (chon == -1 || chon == 0) return;
        if (chon == 1) NghiepVu::themThiDua();
        else NghiepVu::xemThiDuaTheoCanBo();
    }
}

void menuSapXep() {
    while (true) {
        cout << "\n--- SAP XEP CAN BO THEO MA ---\n"
             << "1. Tang dan\n"
             << "2. Giam dan\n"
             << "0. Quay lai\n";
        int chon = chonMenu("Chon", 0, 2);
        if (chon == -1 || chon == 0) return;
        NghiepVu::sapXepTheoMa(chon == 1);
        NghiepVu::hienThiDanhSach();
    }
}

void menuQuanLyTaiKhoan() {
    while (true) {
        cout << "\n--- QUAN LY TAI KHOAN ---\n"
             << "1. Tao tai khoan moi\n"
             << "2. Xem danh sach tai khoan\n"
             << "3. Khoa / mo khoa tai khoan\n"
             << "0. Quay lai\n";
        int chon = chonMenu("Chon", 0, 3);
        if (chon == -1 || chon == 0) return;
        if (chon == 1) NghiepVu::themTaiKhoan();
        else if (chon == 2) NghiepVu::xemTaiKhoan();
        else NghiepVu::khoaMoKhoaTaiKhoan();
    }
}

void menuAdmin() {
    while (true) {
        cout << "\n============ MENU ADMIN ============\n"
             << "1. Quan ly can bo (them, xem, xoa, sua)\n"
             << "2. Quan ly phong ban\n"
             << "3. Quan ly chuc vu\n"
             << "4. Phan cong phong ban & chuc vu\n"
             << "5. Quan ly luong (lich su luong)\n"
             << "6. Danh gia can bo\n"
             << "7. Khen thuong / Ky luat\n"
             << "8. Tim kiem\n"
             << "9. Sap xep\n"
             << "10. Thong ke / Bao cao\n"
             << "11. Quan ly tai khoan\n"
             << "0. Dang xuat / Thoat\n";
        int chon = chonMenu("Chon", 0, 11);
        if (chon == -1 || chon == 0) return;
        if (chon == 1) menuQuanLyCanBo();
        else if (chon == 2) menuQuanLyPhongBan();
        else if (chon == 3) menuQuanLyChucVu();
        else if (chon == 4) menuPhanCong();
        else if (chon == 5) menuQuanLyLuong();
        else if (chon == 6) menuDanhGia();
        else if (chon == 7) menuKhenThuong();
        else if (chon == 8) NghiepVu::timKiemCanBoTheoTen();
        else if (chon == 9) menuSapXep();
        else if (chon == 10) NghiepVu::thongKeBaoCao();
        else menuQuanLyTaiKhoan();
    }
}

void menuUser(const string& maCanBo) {
    while (true) {
        cout << "\n============ MENU USER =============\n"
             << "1. Xem thong tin ca nhan\n"
             << "2. Xem luong cua ban than\n"
             << "3. Xem danh gia cua ban than\n"
             << "4. Xem phan cong / phong ban cua ban than\n"
             << "5. Tim kiem can bo\n"
             << "6. Xem danh sach phong ban\n"
             << "0. Dang xuat\n";
        int chon = chonMenu("Chon", 0, 6);
        if (chon == -1 || chon == 0) return;
        if (chon == 1) NghiepVu::xemThongTinCaNhan(maCanBo);
        else if (chon == 2) NghiepVu::xemLuongCaNhan(maCanBo);
        else if (chon == 3) NghiepVu::xemDanhGiaCaNhan(maCanBo);
        else if (chon == 4) NghiepVu::xemPhanCongCaNhan(maCanBo);
        else if (chon == 5) NghiepVu::timKiemCanBoTheoTen();
        else NghiepVu::xemPhongBan();
    }
}

int main() {
    cout << "============================================\n"
         << "      HE THONG QUAN LY CAN BO\n"
         << "============================================\n"
         << "Dang nhap bang tai khoan (qua NghiepVu)\n"
         << "   -> ADMIN: toan quyen / USER: xem thong tin\n"
         << "============================================\n";

    NghiepVu::khoiTao();

    string vaiTro, maCanBo;
    int soLan = 0;
    bool ok = false;
    while (!ok && soLan < 3) {
        ok = NghiepVu::dangNhap(vaiTro, maCanBo);
        soLan++;
    }
    if (!ok) {
        cout << "Dang nhap that bai sau 3 lan. Thoat chuong trinh.\n";
        return 0;
    }

    while (true) {
        if (vaiTro == "ADMIN") menuAdmin();
        else menuUser(maCanBo);
        cout << "\nBan da dang xuat. Nhap lai tai khoan de tiep tuc (Ctrl+C de thoat).\n";
        ok = false;
        soLan = 0;
        while (!ok && soLan < 3) {
            ok = NghiepVu::dangNhap(vaiTro, maCanBo);
            soLan++;
        }
        if (!ok) {
            cout << "Ket thuc chuong trinh.\n";
            return 0;
        }
    }
}
