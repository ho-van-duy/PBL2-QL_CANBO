#include <cstdlib>
#include <iostream>
#include <limits>
#include "QuanLyCanBo.h"

using namespace std;

#ifdef _WIN32
#include <windows.h>
#endif

void hienMenu() {
    cout << "\n==============================================================\n";
    cout << "|        CHƯƠNG TRÌNH QUẢN LÝ CÁN BỘ - PBL2 (Đề tài 21)       |\n";
    cout << "==============================================================\n";
    cout << "|  1. Tạo và nhập danh sách cán bộ                           |\n";
    cout << "|  2. Hiển thị danh sách cán bộ                              |\n";
    cout << "|  3. Liệt kê cán bộ đến thời điểm nâng lương                |\n";
    cout << "|  4. Đếm số cán bộ nữ trong cơ quan                         |\n";
    cout << "|  5. Tổng thu nhập của toàn bộ cán bộ                       |\n";
    cout << "|  6. Liệt kê cán bộ chuyên môn Công nghệ thông tin          |\n";
    cout << "|  7. Liệt kê cán bộ xếp loại lao động Giỏi                  |\n";
    cout << "|  8. Sắp xếp danh sách theo mã cán bộ                       |\n";
    cout << "|  9. Loại bỏ một cán bộ theo mã                             |\n";
    cout << "| 10. Thêm một cán bộ vào danh sách                          |\n";
    cout << "|  0. Thoát (tự động lưu dữ liệu)                            |\n";
    cout << "==============================================================\n";
}

void xoaManHinh() {
#ifdef _WIN32
    system("cls");
#else
    cout << "\033[2J\033[H";
#endif
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    QuanLyCanBo quanLy(duongDanDuLieu());
    quanLy.docFile();

    while (true) {
        hienMenu();
        cout << "Nhấn phím số tương ứng để thực hiện: ";

        int luaChon = -1;
        if (!(cin >> luaChon)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (cin.eof()) break;
            xoaManHinh();
            cout << "Lua chon khong hop le, hay nhap lai!\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (luaChon == 0) {
            quanLy.ghiFile();
            break;
        }

        xoaManHinh();

        switch (luaChon) {
            case 1:  quanLy.nhapDanhSach();    break;
            case 2:  quanLy.hienThi();         break;
            case 3:  quanLy.lietKeNangLuong(); break;
            case 4:  quanLy.demCanBoNu();      break;
            case 5:  quanLy.tongThuNhap();     break;
            case 6:  quanLy.lietKeCNTT();      break;
            case 7:  quanLy.lietKeLoaiGioi();  break;
            case 8:  quanLy.sapXepTheoMa();    break;
            case 9:  quanLy.xoaTheoMa();       break;
            case 10: quanLy.themCanBo();       break;
            default:
                cout << "Khong co chuc nang nay, hay chon 1-10 hoac 0!\n";
                break;
        }
        cout << "\n";
    }
    return 0;
}
