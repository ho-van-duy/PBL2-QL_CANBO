#include <iostream>
#include <limits>
#include "phongban.h"
#include "chucvu.h"
#include "canbo.h"
using namespace std;

void khoiTaoDuLieu() {
    PhongBan p1("PB01", "Phong Ke Toan", 10, "Tang 2");
    PhongBan p2("PB02", "Phong Nhan Su", 8, "Tang 3");
    PhongBan p3("PB03", "Phong Kinh Doanh", 12, "Tang 5");

    PhongBan::themPhongBan(p1);
    PhongBan::themPhongBan(p2);
    PhongBan::themPhongBan(p3);

    ChucVu cv1("CV01", "Giam Doc", 5, 5, "Quyen ra quyet dinh", "Quan ly toan bo cong ty");
    ChucVu cv2("CV02", "Truong Phong", 4, 4, "Quyen quan ly phong ban", "Quan ly nhan su va workplan");
    ChucVu cv3("CV03", "Nhan Vien", 2, 2, "Thuc hien cong viec", "Lam theo ke hoach");

    ChucVu::themChucVu(cv1);
    ChucVu::themChucVu(cv2);
    ChucVu::themChucVu(cv3);

    CanBo cb1("CB01", "An", 30, "Nam", "Ha Noi", 15000000, cv1, p1);
    CanBo cb2("CB02", "Binh", 28, "Nu", "Da Nang", 12000000, cv2, p2);
    CanBo cb3("CB03", "Chi", 26, "Nu", "HCM", 9000000, cv3, p3);

    CanBo::themCanBo(cb1);
    CanBo::themCanBo(cb2);
    CanBo::themCanBo(cb3);
}

void xuatMenu() {
    cout << "\n===== QUAN LY CAN BO =====\n";
    cout << "1. Xem danh sach phong ban\n";
    cout << "2. Xem danh sach chuc vu\n";
    cout << "3. Xem danh sach can bo\n";
    cout << "4. Tim phong ban theo ma\n";
    cout << "5. Tim chuc vu theo ma\n";
    cout << "6. Tim can bo theo ma\n";
    cout << "7. So sanh cap bac hai chuc vu\n";
    cout << "8. Tinh luong can bo\n";
    cout << "0. Thoat\n";
    cout << "Chon: ";
}

int main() {
    khoiTaoDuLieu();
    int luaChon = -1;

    while (luaChon != 0) {
        xuatMenu();
        cin >> luaChon;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (luaChon) {
            case 1: {
                cout << "\n=== DANH SACH PHONG BAN ===\n";
                PhongBan::xuatDanhSachPhongBan();
                break;
            }
            case 2: {
                cout << "\n=== DANH SACH CHUC VU ===\n";
                ChucVu::xuatDanhSachChucVu();
                break;
            }
            case 3: {
                cout << "\n=== DANH SACH CAN BO ===\n";
                CanBo::xuatDanhSachCanBo();
                break;
            }
            case 4: {
                string ma;
                cout << "Nhap ma phong ban: ";
                getline(cin, ma);
                PhongBan pb = PhongBan::timPhongBanTheoMa(ma);
                if (pb.getMaPhongBan() != "") pb.xuat();
                else cout << "Khong tim thay phong ban!\n";
                break;
            }
            case 5: {
                string ma;
                cout << "Nhap ma chuc vu: ";
                getline(cin, ma);
                ChucVu cv = ChucVu::timChucVuTheoMa(ma);
                if (cv.getMaChucVu() != "") cv.xuat();
                else cout << "Khong tim thay chuc vu!\n";
                break;
            }
            case 6: {
                string ma;
                cout << "Nhap ma can bo: ";
                getline(cin, ma);
                CanBo cb = CanBo::timCanBoTheoMa(ma);
                if (cb.getMaCanBo() != "") cb.xuat();
                else cout << "Khong tim thay can bo!\n";
                break;
            }
            case 7: {
                ChucVu cv1("CV01", "Giam Doc", 5, 5, "Quyen ra quyet dinh", "Quan ly toan bo cong ty");
                ChucVu cv2("CV02", "Truong Phong", 4, 4, "Quyen quan ly phong ban", "Quan ly nhan su va workplan");
                if (cv1.laCaoHon(cv2)) {
                    cout << "Giam Doc co cap bac cao hon Truong Phong.\n";
                } else {
                    cout << "Truong Phong co cap bac cao hon Giam Doc.\n";
                }
                break;
            }
            case 8: {
                string ma;
                cout << "Nhap ma can bo: ";
                getline(cin, ma);
                CanBo cb = CanBo::timCanBoTheoMa(ma);
                if (cb.getMaCanBo() != "") {
                    cout << "Luong cua can bo " << cb.getHoTen() << ": " << cb.tinhLuong() << endl;
                } else {
                    cout << "Khong tim thay can bo!\n";
                }
                break;
            }
            case 0:
                cout << "Ket thuc chuong trinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le!\n";
                break;
        }
    }

    return 0;
}
