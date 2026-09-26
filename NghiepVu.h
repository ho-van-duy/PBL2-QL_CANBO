#ifndef NGHIEPVU_H
#define NGHIEPVU_H

#include <string>
using namespace std;

class NghiepVu {
public:
    // Khởi tạo & đăng nhập
    static void khoiTao();
    static bool dangNhap(string& vaiTro, string& maCanBo);

    // Hàm tiện ích
    static string sinhMaTuDong(const string& loai);

    // 10 chức năng đề bài
    static void themNhieuCanBo();
    static void hienThiDanhSach();
    static void lietKeDenHanTangLuong();
    static void demCanBoNu();
    static void tongThuNhap();
    static void lietKeCanBoCNTT();
    static void lietKeCanBoGioi();
    static void sapXepTheoMa(bool tang);
    static void xoaCanBoTheoMa();
    static void themMotCanBo();
    static void suaThongTinCanBo();

    // Xem thông tin theo mã cán bộ (dùng cho menu USER)
    static void xemThongTinCaNhan(const string& maCanBo);
    static void xemLuongCaNhan(const string& maCanBo);
    static void xemDanhGiaCaNhan(const string& maCanBo);
    static void xemPhanCongCaNhan(const string& maCanBo);

    // Tìm kiếm theo tên
    static void timKiemCanBoTheoTen();

    // Quản lý cho menu ADMIN
    static void themPhongBan();
    static void xemPhongBan();
    static void xoaPhongBanTheoMa();
    static void themChucVu();
    static void xemChucVu();
    static void xoaChucVuTheoMa();
    static void themPhanCong();
    static void xemPhanCong();
    static void themLuong();
    static void xemLuongTheoCanBo();
    static void themDanhGia();
    static void xemDanhGiaTheoCanBo();
    static void themThiDua();
    static void xemThiDuaTheoCanBo();
    static void themTaiKhoan();
    static void khoaMoKhoaTaiKhoan();
    static void xemTaiKhoan();
    static void thongKeBaoCao();

private:
    // Trợ giúp nội bộ
    static string dinhDangMa(const string& prefix, int so, int beRong);
    static string dateThanhSo(const string& ngay);
    static bool giaoNhau(const string& tu1, const string& den1,
                         const string& tu2, const string& den2);
    static int timCanBoTheoMa(const string& ma);
    static int timPhongTheoMa(const string& ma);
    static int timChucVuTheoMa(const string& ma);
    static int timPhanCongTheoMa(const string& ma);
    static int timLuongTheoMa(const string& ma);
    static int timDanhGiaTheoMa(const string& ma);
    static int timThiDuaTheoMa(const string& ma);
    static int timTaiKhoanTheoMa(const string& ma);
};

#endif