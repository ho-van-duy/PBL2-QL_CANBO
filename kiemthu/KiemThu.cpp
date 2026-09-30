// ================================================================
//  KIEM THU TU DONG - PBL2 QL_CANBO
//
//  main.cpp da chiem main(), nen harness nay nam trong thu muc rieng
//  va duoc bien dich chung voi cac file nguon cua du an:
//
//      g++ -std=c++11 -Wall -Wextra CanBo.cpp PhongBan.cpp ChucVu.cpp PhanCong.cpp Luong.cpp DanhGia.cpp ThiDua.cpp Account.cpp Vector.cpp NghiepVu.cpp kiemthu\KiemThu.cpp -o KT.exe
//      KT.exe            (chay tu thu muc goc du an, can data/ rong)
//
//  Exit code: 0 = tat ca PASS, 1 = co FAIL, 2 = data/ khong rong.
//  Luu y: harness GHI DEM LAI 8 file trong data/ roi dua ve rong luc
//  ket thuc, nen khong chay khi du an dang co du lieu that.
// ================================================================
#include "../NghiepVu.h"
#include "../Vector.h"
#include "../ThucThe.h"
#include "../CanBo.h"
#include "../PhongBan.h"
#include "../ChucVu.h"
#include "../PhanCong.h"
#include "../Luong.h"
#include "../DanhGia.h"
#include "../ThiDua.h"
#include "../Account.h"
#include <sstream>
#include <fstream>
#include <stdexcept>

// ---------- Bo dem ket qua ----------

static int soKiem = 0;
static int soLoi = 0;
static string kqGanNhat;

static void kiemTra(bool dk, const string& ten) {
    soKiem++;
    if (dk) {
        cout << "   [PASS] " << ten << endl;
    } else {
        soLoi++;
        cout << "   [FAIL] " << ten << endl;
        cout << "          --- output nhan duoc tu ham vua goi ---" << endl;
        istringstream ss(kqGanNhat);
        string dong;
        int dem = 0;
        while (getline(ss, dong) && dem < 6) {
            cout << "          | " << dong << endl;
            dem++;
        }
        cout << "          ------------------------------------------" << endl;
    }
}

static void tieuDe(const string& ten) {
    cout << "\n=== " << ten << " ===" << endl;
}

// ---------- Cung cap du lieu cho cac ham doc cin ----------

static istringstream* banLenh = NULL;

static void cungCapLenh(const string& duLieu) {
    if (banLenh != NULL) delete banLenh;
    banLenh = new istringstream(duLieu);
    cin.clear();
    cin.rdbuf(banLenh->rdbuf());
}

// ---------- Bat output cua ham void() de kiem tra thong bao ----------

typedef void (*Ham)();

static string chayVaBat(Ham ham) {
    ostringstream oss;
    streambuf* cu = cout.rdbuf(oss.rdbuf());
    ham();
    cout.rdbuf(cu);
    kqGanNhat = oss.str();
    return kqGanNhat;
}

static bool coChu(const string& s, const string& tu) {
    return s.find(tu) != string::npos;
}

static int demLan(const string& s, const string& tu) {
    int dem = 0;
    size_t vi = s.find(tu);
    while (vi != string::npos) {
        dem++;
        vi = s.find(tu, vi + 1);
    }
    return dem;
}

// ---------- Wrapper cho NghiepVu::dangNhap (tra ve bool) ----------

static string vaiTro, maCanBo;
static bool okDangNhap = false;

static void goiDangNhap() {
    vaiTro = "";
    maCanBo = "";
    okDangNhap = NghiepVu::dangNhap(vaiTro, maCanBo);
}

// ---------- Xuat qua con tro lop co so: kiem chung da hinh ----------

static string chayXuat(const ThucThe* p) {
    ostringstream oss;
    streambuf* cu = cout.rdbuf(oss.rdbuf());
    (p->*(&ThucThe::xuat))();
    cout.rdbuf(cu);
    kqGanNhat = oss.str();
    return kqGanNhat;
}

// ---------- data/ ----------

static const char* FILE_DATA[8] = {
    "data/canbo.txt", "data/phongban.txt", "data/chucvu.txt", "data/phancong.txt",
    "data/luong.txt", "data/danhgia.txt", "data/thidua.txt", "data/account.txt"
};

static bool dataRong() {
    for (int i = 0; i < 8; i++) {
        ifstream in(FILE_DATA[i]);
        string t;
        bool coDuLieu = (bool)(in >> t);
        in.close();
        if (coDuLieu) return false;
    }
    return true;
}

static void lamRongData() {
    for (int i = 0; i < 8; i++) {
        ofstream out(FILE_DATA[i], ios::trunc);
        out.close();
    }
}

static int demDong(const char* duongDan) {
    ifstream in(duongDan);
    int n = 0;
    string dong;
    while (getline(in, dong)) {
        if (!dong.empty()) n++;
    }
    in.close();
    return n;
}

// ---------- Du lieu kiem thu ----------

static const string CB1 =
    "Nguyen Van A\n01-01-1990\nNam\nHa Noi\nCong nghe thong tin\nDai hoc\n15-03-2018\n";
static const string CB2 =
    "Tran Thi B\n05-05-1995\nNu\nDa Nang\nCong nghe thong tin\nThac si\n01-09-2022\n";
static const string CB3 =
    "Le Thi C\n10-10-1992\nNu\nHue\nKinh te\nCao dang\n01-01-2020\n";
static const string CB4 =
    "Nguyen Van D\n01-01-1988\nNam\nBac Ninh\nAn ninh\nDai hoc\n01-01-2015\n";

int main() {
    cout << "============================================\n"
         << "   KIEM THU TU DONG - HE THONG QUAN LY CAN BO\n"
         << "============================================" << endl;

    if (!dataRong()) {
        cout << "\n[STOP] Thu muc data/ dang co du lieu that.\n"
             << "       Hay dua data/ ve trang thai rong truoc khi chay kiem thu\n"
             << "       (vi du: xoa het noi dung trong 8 file .txt)." << endl;
        return 2;
    }

    // ============ 1. Khoi tao & sinh ma tu dong ============
    tieuDe("1. Khoi tao & sinh ma tu dong");
    NghiepVu::khoiTao();
    kiemTra(Account::SoLuong() == 2, "khoiTao: tao 2 tai khoan demo khi data/ rong");
    kiemTra(NghiepVu::sinhMaTuDong("CAN_BO") == "CB001", "sinhMaTuDong(CAN_BO) -> CB001");
    kiemTra(NghiepVu::sinhMaTuDong("PHONG_BAN") == "P01", "sinhMaTuDong(PHONG_BAN) -> P01");
    kiemTra(NghiepVu::sinhMaTuDong("CHUC_VU") == "CV01", "sinhMaTuDong(CHUC_VU) -> CV01");
    kiemTra(NghiepVu::sinhMaTuDong("PHAN_CONG") == "PC001", "sinhMaTuDong(PHAN_CONG) -> PC001");
    kiemTra(NghiepVu::sinhMaTuDong("LICH_SU_LUONG") == "ML001", "sinhMaTuDong(LICH_SU_LUONG) -> ML001");
    kiemTra(NghiepVu::sinhMaTuDong("DANH_GIA") == "DG001", "sinhMaTuDong(DANH_GIA) -> DG001");
    kiemTra(NghiepVu::sinhMaTuDong("KHEN_THUONG_KY_LUAT") == "SK001", "sinhMaTuDong(KHEN_THUONG_KY_LUAT) -> SK001");
    kiemTra(NghiepVu::sinhMaTuDong("TAI_KHOAN") == "TK003", "sinhMaTuDong(TAI_KHOAN) -> TK003 (da co TK001, TK002)");
    kiemTra(NghiepVu::sinhMaTuDong("LOAI_SAI") == "", "sinhMaTuDong(loai la) -> chuoi rong");

    // ============ 2. Vector int-array tu viet ============
    tieuDe("2. Vector: mang int dong tu viet");
    cungCapLenh("7\n8\n9\n");
    {
        ostringstream oss;
        streambuf* cu = cout.rdbuf(oss.rdbuf());
        Vector v(3);
        cout.rdbuf(cu);
        kiemTra(v[0] == 7 && v[1] == 8 && v[2] == 9, "Vector(3): doc 3 so nguyen tu cin");
        bool nem = false;
        try {
            int x = v[5];
            (void)x;
        } catch (out_of_range& e) {
            nem = true;
        }
        kiemTra(nem, "Vector: nem out_of_range khi chi so ngoai pham vi");
        Vector v2(v);
        kiemTra(v2[1] == 8, "Vector: copy constructor sao chep du lieu");
        v2[1] = 80;
        kiemTra(v[1] == 8, "Vector: gan tach bien khong alias v-object goc");
    }

    // ============ 3. Phong ban & chuc vu ============
    tieuDe("3. Phong ban & chuc vu");
    cungCapLenh("Phong IT\nPhan mem\n");
    chayVaBat(NghiepVu::themPhongBan);
    kiemTra(PhongBan::SoLuong() == 1 && PhongBan::LayTai(0).GetMaPhong() == "P01",
            "themPhongBan: sinh ma P01, khong nhap tay ma");
    kiemTra(PhongBan::LayTai(0).GetTenPhong() == "Phong IT", "themPhongBan: luu ten phong");
    cungCapLenh("Phong Ke Toan\nKe toan\n");
    chayVaBat(NghiepVu::themPhongBan);
    kiemTra(PhongBan::SoLuong() == 2 && PhongBan::LayTai(1).GetMaPhong() == "P02",
            "themPhongBan: ma thu hai P02 (khong trung ma)");
    cungCapLenh("Phong Nhan Su\nNhan su\n");
    chayVaBat(NghiepVu::themPhongBan);
    kiemTra(PhongBan::SoLuong() == 3 && PhongBan::LayTai(2).GetMaPhong() == "P03",
            "themPhongBan: ma thu ba P03");
    cungCapLenh("Nhan vien\n500000\nMo ta chuc vu\n");
    chayVaBat(NghiepVu::themChucVu);
    kiemTra(ChucVu::SoLuong() == 1 && ChucVu::LayTai(0).GetMaCV() == "CV01"
                && ChucVu::LayTai(0).GetPhuCapCV() == 500000,
            "themChucVu: sinh ma CV01 + phu cap 500000");

    // ============ 4. Can bo (chuc nang 1 & 10) ============
    tieuDe("4. Can bo: them nhieu & them mot");
    cungCapLenh("2\n" + CB1 + CB2);
    string kq = chayVaBat(NghiepVu::themNhieuCanBo);
    kiemTra(coChu(kq, "Da them 2 can bo!"), "themNhieuCanBo: bao cao da them 2 can bo");
    kiemTra(CanBo::SoLuong() == 2, "themNhieuCanBo: danh sach co 2 can bo");
    kiemTra(CanBo::LayTai(0).GetMaCB() == "CB001" && CanBo::LayTai(1).GetMaCB() == "CB002",
            "themNhieuCanBo: ma tu sinh CB001, CB002");
    cungCapLenh(CB3);
    chayVaBat(NghiepVu::themMotCanBo);
    cungCapLenh(CB4);
    chayVaBat(NghiepVu::themMotCanBo);
    kiemTra(CanBo::SoLuong() == 4 && CanBo::LayTai(3).GetMaCB() == "CB004",
            "themMotCanBo: ma tu sinh tiep tuc CB003, CB004");
    kiemTra(CanBo::LayTai(0).GetTrangThai() == "DangLamViec", "can bo moi mac dinh DangLamViec");
    kiemTra(CanBo::LayTai(0).TinhTuoi() == 36 && CanBo::LayTai(2).TinhNamLam() == 6,
            "TinhTuoi/TinhNamLam tinh tu ngay sinh va ngay vao lam");

    // ============ 5. Tim kiem & sap xep ============
    tieuDe("5. Tim kiem theo ten & sap xep theo ma");
    cungCapLenh("van\n");
    kq = chayVaBat(NghiepVu::timKiemCanBoTheoTen);
    kiemTra(coChu(kq, "Tim thay 2 can bo"), "timKiemCanBoTheoTen(\"van\") -> 2 ket qua (khong phan biet hoa/thuong)");
    cungCapLenh("zzz\n");
    kq = chayVaBat(NghiepVu::timKiemCanBoTheoTen);
    kiemTra(coChu(kq, "Khong tim thay can bo nao"), "timKiemCanBoTheoTen(\"zzz\") -> khong co ket qua");
    NghiepVu::sapXepTheoMa(true);
    kiemTra(CanBo::LayTai(0).GetMaCB() == "CB001" && CanBo::LayTai(3).GetMaCB() == "CB004",
            "sapXepTheoMa(tang) -> CB001 ... CB004");
    NghiepVu::sapXepTheoMa(false);
    kiemTra(CanBo::LayTai(0).GetMaCB() == "CB004" && CanBo::LayTai(3).GetMaCB() == "CB001",
            "sapXepTheoMa(giam) -> CB004 ... CB001");
    NghiepVu::sapXepTheoMa(true);
    kiemTra(CanBo::LayTai(0).GetMaCB() == "CB001", "sapXepTheoMa(tang) lai -> da khuong hoa danh sach");

    // ============ 6. Phan cong: FK + rang buoc C2 ============
    tieuDe("6. Phan cong: khoa ngoai & rang buoc C2");
    cungCapLenh("CB001\nP01\nCV01\n01-01-2023\n\nChinhThuc\n1\n");
    kq = chayVaBat(NghiepVu::themPhanCong);
    kiemTra(coChu(kq, "Da them phan cong PC001") && PhanCong::SoLuong() == 1,
            "themPhanCong: phong chinh P01 hieu luc, ma PC001");
    cungCapLenh("CB001\nP01\nCV01\n01-06-2023\n\nChinhThuc\n1\n");
    kq = chayVaBat(NghiepVu::themPhanCong);
    kiemTra(coChu(kq, "Vi pham C2") && PhanCong::SoLuong() == 1,
            "C2: chong 2 phong chinh cung thoi gian bi tu choi");
    cungCapLenh("CB001\nP02\nCV01\n01-06-2023\n\nKiemNhiem\n0\n");
    kq = chayVaBat(NghiepVu::themPhanCong);
    kiemTra(coChu(kq, "Da them phan cong PC002") && PhanCong::SoLuong() == 2,
            "C2: kiem nhiem chong phong chinh van duoc phep");
    cungCapLenh("CB001\nP99\nCV01\n01-01-2024\n\nChinhThuc\n0\n");
    kq = chayVaBat(NghiepVu::themPhanCong);
    kiemTra(coChu(kq, "Ma phong khong ton tai!") && PhanCong::SoLuong() == 2,
            "FK: ma phong P99 khong ton tai bi tu choi");
    cungCapLenh("CB999\nP01\nCV01\n01-01-2024\n\nChinhThuc\n0\n");
    kq = chayVaBat(NghiepVu::themPhanCong);
    kiemTra(coChu(kq, "Ma can bo khong ton tai!") && PhanCong::SoLuong() == 2,
            "FK: ma can bo CB999 khong ton tai bi tu choi");
    cungCapLenh("CB001\nP01\nCV99\n01-01-2024\n\nChinhThuc\n0\n");
    kq = chayVaBat(NghiepVu::themPhanCong);
    kiemTra(coChu(kq, "Ma chuc vu khong ton tai!") && PhanCong::SoLuong() == 2,
            "FK: ma chuc vu CV99 khong ton tai bi tu choi");

    // ============ 7. Luong: cong thuc & rang buoc C3 ============
    tieuDe("7. Luong: thuc linh & rang buoc C3");
    cungCapLenh("CB001\n3.0\n2.0\n1.0\n01-01-2018\n31-12-2019\nTang luong\n");
    kq = chayVaBat(NghiepVu::themLuong);
    kiemTra(coChu(kq, "Da them luong ML001") && Luong::SoLuong() == 1,
            "themLuong: ban luong ML001 het han");
    kiemTra(Luong::LayTai(0).tinhThucLinh() == 7450001.0,
            "tinhThucLinh = (3.0 + 2.0) * 1490000 + 1 = 7450001");
    kiemTra(!Luong::LayTai(0).HieuLuc(), "HieuLuc() = false khi co DenNgay");
    cungCapLenh("CB001\n3.5\n0\n0\n01-06-2019\n\nTang luong\n");
    kq = chayVaBat(NghiepVu::themLuong);
    kiemTra(coChu(kq, "Vi pham C3") && Luong::SoLuong() == 1,
            "C3: trung thoi gian voi ban luong cu bi tu choi");
    cungCapLenh("CB001\n3.5\n0\n0\n01-01-2020\n\nTang luong\n");
    kq = chayVaBat(NghiepVu::themLuong);
    kiemTra(coChu(kq, "Da them luong ML002") && Luong::SoLuong() == 2
                && Luong::LayTai(1).tinhThucLinh() == 5215000.0,
            "themLuong: ban hieu luc ML002, thuc linh 3.5 * 1490000 = 5215000");

    // ============ 8. Danh gia & khen thuong/ky luat ============
    tieuDe("8. Danh gia & khen thuong / ky luat");
    cungCapLenh("CB001\nGioi\nRat tot\n10-11-2025\n");
    kq = chayVaBat(NghiepVu::themDanhGia);
    kiemTra(coChu(kq, "Da them danh gia DG001") && DanhGia::SoLuong() == 1,
            "themDanhGia: DG001 cho CB001");
    cungCapLenh("CB001\nTrungBinh\nKha\n01-01-2026\n");
    chayVaBat(NghiepVu::themDanhGia);
    cungCapLenh("CB002\nGioi\nTot\n01-06-2026\n");
    chayVaBat(NghiepVu::themDanhGia);
    kq = chayVaBat(NghiepVu::lietKeCanBoGioi);
    kiemTra(demLan(kq, "Ma can bo: ") == 1 && coChu(kq, "Ma can bo: CB002"),
            "lietKeCanBoGioi: lay danh gia MOI NHAT -> chi CB002 (DG002 2026 thay the DG001 Gioi)");
    cungCapLenh("CB001\nKHEN_THUONG\nKhen thuong vi thanh tich\n2026\nLy do\n");
    kq = chayVaBat(NghiepVu::themThiDua);
    kiemTra(coChu(kq, "Da them su kien SK001") && ThiDua::SoLuong() == 1,
            "themThiDua: SK001 khen thuong cho CB001");

    // ============ 9. Tai khoan & dang nhap ============
    tieuDe("9. Tai khoan & dang nhap");
    cungCapLenh("nhanvien\n123\nUSER\nCB001\n");
    kq = chayVaBat(NghiepVu::themTaiKhoan);
    kiemTra(coChu(kq, "Da tao tai khoan nhanvien") && Account::SoLuong() == 3
                && Account::LayTai(2).getMaTaiKhoan() == "TK003"
                && Account::LayTai(2).getMaCanBo() == "CB001",
            "themTaiKhoan: TK003 lien ket CB001, vai tro USER");
    cungCapLenh("nhanvien\n123\nUSER\nCB001\n");
    kq = chayVaBat(NghiepVu::themTaiKhoan);
    kiemTra(coChu(kq, "Ten dang nhap da ton tai!") && Account::SoLuong() == 3,
            "themTaiKhoan: trung ten dang nhap bi tu choi");
    cungCapLenh("admin\nadmin\n");
    chayVaBat(goiDangNhap);
    kiemTra(okDangNhap && vaiTro == "ADMIN", "dangNhap admin/admin -> vai tro ADMIN");
    cungCapLenh("admin\nsai-mat-khau\n");
    chayVaBat(goiDangNhap);
    kiemTra(!okDangNhap, "dangNhap sai mat khau -> that bai");
    cungCapLenh("user\n");
    kq = chayVaBat(NghiepVu::khoaMoKhoaTaiKhoan);
    kiemTra(coChu(kq, "la: BiKhoa"), "khoaMoKhoaTaiKhoan: khoa tai khoan user");
    cungCapLenh("user\nuser\n");
    chayVaBat(goiDangNhap);
    kiemTra(!okDangNhap, "tai khoan bi khoa -> khong dang nhap duoc");
    cungCapLenh("user\n");
    kq = chayVaBat(NghiepVu::khoaMoKhoaTaiKhoan);
    kiemTra(coChu(kq, "la: HoatDong"), "khoaMoKhoaTaiKhoan: mo khoa tai khoan user");

    // ============ 10. Xoa mem & sua thong tin ============
    tieuDe("10. Xoa mem & sua thong tin can bo");
    cungCapLenh("CB004\n");
    kq = chayVaBat(NghiepVu::xoaCanBoTheoMa);
    kiemTra(coChu(kq, "Da xoa mem can bo CB004") && CanBo::SoLuong() == 4
                && CanBo::LayTai(3).GetTrangThai() == "NghiViec",
            "xoaCanBoTheoMa: xoa mem CB004, van con 4 ban ghi (giu lich su)");
    kq = chayVaBat(NghiepVu::demCanBoNu);
    kiemTra(coChu(kq, "So can bo nu: 2 / 4"),
            "xoa mem khong lam mat thong ke (van tinh ca 4 ban ghi)");
    cungCapLenh("CB002\nTran Thi B Cap Nhat\n05-05-1995\nNu\nDa Nang\nCong nghe thong tin\nThac si\n01-09-2022\n");
    kq = chayVaBat(NghiepVu::suaThongTinCanBo);
    kiemTra(coChu(kq, "Da cap nhat thong tin can bo CB002")
                && CanBo::LayTai(1).GetTen() == "Tran Thi B Cap Nhat"
                && CanBo::LayTai(1).GetMaCB() == "CB002",
            "suaThongTinCanBo: doi thong tin, giu nguyen ma");
    cungCapLenh("P01\n");
    kq = chayVaBat(NghiepVu::xoaPhongBanTheoMa);
    kiemTra(coChu(kq, "Khong xoa duoc - phong dang duoc phan cong!") && PhongBan::SoLuong() == 3,
            "FK: khong xoa duoc phong ban dang duoc phan cong");
    cungCapLenh("CV01\n");
    kq = chayVaBat(NghiepVu::xoaChucVuTheoMa);
    kiemTra(coChu(kq, "Khong xoa duoc - chuc vu dang duoc phan cong!") && ChucVu::SoLuong() == 1,
            "FK: khong xoa duoc chuc vu dang duoc phan cong");
    cungCapLenh("P03\n");
    kq = chayVaBat(NghiepVu::xoaPhongBanTheoMa);
    kiemTra(coChu(kq, "Da xoa phong ban P03") && PhongBan::SoLuong() == 2,
            "xoaPhongBanTheoMa: xoa duoc P03 (khong co phan cong nao)");

    // ============ 11. Thong ke & bao cao ============
    tieuDe("11. Thong ke & bao cao");
    kq = chayVaBat(NghiepVu::demCanBoNu);
    kiemTra(coChu(kq, "So can bo nu: 2 / 4"), "demCanBoNu -> 2 / 4");
    kq = chayVaBat(NghiepVu::lietKeCanBoCNTT);
    kiemTra(demLan(kq, "Ma can bo: ") == 2, "lietKeCanBoCNTT -> 2 can bo");
    kq = chayVaBat(NghiepVu::lietKeDenHanTangLuong);
    kiemTra(demLan(kq, "Ma can bo: ") == 4,
            "lietKeDenHanTangLuong -> 4/4 can bo (chu ky 3 nam, NAM_HIEN_TAI 2026)");
    kq = chayVaBat(NghiepVu::tongThuNhap);
    kiemTra(coChu(kq, "5215000 dong"),
            "tongThuNhap -> 5215000 (chi tinh ban luong hieu luc, ML001 da het han)");
    kq = chayVaBat(NghiepVu::thongKeBaoCao);
    kiemTra(coChu(kq, "So can bo nu:") && coChu(kq, "Tong thu nhap")
                && coChu(kq, "So can bo chuyen CNTT:") && coChu(kq, "So can bo xep loai Gioi:"),
            "thongKeBaoCao: in day du 4 chi so");
    kq = chayVaBat(NghiepVu::hienThiDanhSach);
    kiemTra(demLan(kq, "----- CAN_BO -----") == 4 && demLan(kq, "----- PHAN_CONG -----") == 2,
            "hienThiDanhSach: 4 can bo + 2 phan cong hieu luc");

    // ============ 12. Da hinh runtime qua ThucThe* ============
    tieuDe("12. Da hinh runtime qua con tro ThucThe*");
    {
        ThucThe* mau[8];
        int soBanGhi[8] = {
            CanBo::SoLuong(), PhongBan::SoLuong(), ChucVu::SoLuong(), PhanCong::SoLuong(),
            Luong::SoLuong(), DanhGia::SoLuong(), ThiDua::SoLuong(), Account::SoLuong()
        };
        string kyVong[8] = {
            "CAN_BO", "PHONG_BAN", "CHUC_VU", "PHAN_CONG",
            "LICH_SU_LUONG", "DANH_GIA", "KHEN_THUONG_KY_LUAT", "TAI_KHOAN"
        };
        mau[0] = soBanGhi[0] > 0 ? &CanBo::LayTai(0) : NULL;
        mau[1] = soBanGhi[1] > 0 ? &PhongBan::LayTai(0) : NULL;
        mau[2] = soBanGhi[2] > 0 ? &ChucVu::LayTai(0) : NULL;
        mau[3] = soBanGhi[3] > 0 ? &PhanCong::LayTai(0) : NULL;
        mau[4] = soBanGhi[4] > 0 ? &Luong::LayTai(0) : NULL;
        mau[5] = soBanGhi[5] > 0 ? &DanhGia::LayTai(0) : NULL;
        mau[6] = soBanGhi[6] > 0 ? &ThiDua::LayTai(0) : NULL;
        mau[7] = soBanGhi[7] > 0 ? &Account::LayTai(0) : NULL;

        bool du8 = true;
        for (int t = 0; t < 8; t++) if (mau[t] == NULL) du8 = false;
        kiemTra(du8, "tao duoc 8 con tro ThucThe* cho 8 loai ban ghi khac nhau");
        if (du8) {
            for (int t = 0; t < 8; t++) {
                kiemTra(mau[t]->loaiThucThe() == kyVong[t],
                        "ThucThe*->loaiThucHe() -> " + kyVong[t]);
            }
            for (int t = 0; t < 8; t++) {
                kq = chayXuat(mau[t]);
                kiemTra(coChu(kq, "----- " + kyVong[t] + " -----"),
                        "ThucThe*->xuat() goi override cua " + kyVong[t]);
            }
        }
        kq = chayVaBat(NghiepVu::xuatTatCaTheoMau);
        bool duDau8 = true;
        for (int t = 0; t < 8; t++) {
            if (demLan(kq, "----- " + kyVong[t] + " -----") != soBanGhi[t]) duDau8 = false;
        }
        kiemTra(duDau8, "xuatTatCaTheoMau: in day du 8 loai, so ban ghi dung voi tung bang");
        kiemTra(coChu(kq, "18 ban ghi"),
                "xuatTatCaTheoMau: tong 18 ban ghi (4 CB + 2 PB + 1 CV + 2 PC + 2 ML + 3 DG + 1 SK + 3 TK)");
    }

    // ============ 13. Luu tru & doc lai file ============
    tieuDe("13. Luu tru file & doc lai (round-trip)");
    kiemTra(demDong("data/canbo.txt") == 4, "data/canbo.txt co 4 dong");
    kiemTra(demDong("data/phancong.txt") == 2, "data/phancong.txt co 2 dong");
    kiemTra(demDong("data/luong.txt") == 2, "data/luong.txt co 2 dong");
    kiemTra(demDong("data/account.txt") == 3, "data/account.txt co 3 dong");
    kiemTra(demDong("data/phongban.txt") == 2, "data/phongban.txt co 2 dong (P03 da xoa)");

    CanBo::DocTatCa();
    PhongBan::DocTatCa();
    ChucVu::DocTatCa();
    PhanCong::DocTatCa();
    Luong::DocTatCa();
    DanhGia::DocTatCa();
    ThiDua::DocTatCa();
    Account::DocTatCa();
    kiemTra(CanBo::SoLuong() == 4 && CanBo::LayTai(0).GetTen() == "Nguyen Van A"
                && CanBo::LayTai(1).GetTen() == "Tran Thi B Cap Nhat"
                && CanBo::LayTai(3).GetTrangThai() == "NghiViec",
            "doc lai data/canbo.txt: dung so luong & noi dung (ke ca ban ghi da sua/xoa mem)");
    kiemTra(PhongBan::SoLuong() == 2 && PhongBan::LayTai(0).GetMaPhong() == "P01"
                && PhongBan::LayTai(1).GetMaPhong() == "P02",
            "doc lai data/phongban.txt: chi con P01, P02 (P03 da xoa)");
    kiemTra(PhanCong::SoLuong() == 2 && PhanCong::LayTai(0).getLoaiPhanCong() == "ChinhThuc"
                && PhanCong::LayTai(0).getLaPhongChinh(),
            "doc lai data/phancong.txt: PC001 phong chinh + PC002 kiem nhiem");
    kiemTra(Luong::SoLuong() == 2 && Luong::LayTai(0).tinhThucLinh() == 7450001.0
                && Luong::LayTai(1).HieuLuc(),
            "doc lai data/luong.txt: ML001 7450001 + ML002 hieu luc");
    kiemTra(DanhGia::SoLuong() == 3 && DanhGia::LayTai(0).GetXepLoai() == "Gioi"
                && DanhGia::LayTai(1).GetXepLoai() == "TrungBinh"
                && DanhGia::LayTai(2).GetXepLoai() == "Gioi",
            "doc lai data/danhgia.txt: DG001 Gioi + DG002 TrungBinh + DG003 Gioi");
    kiemTra(ThiDua::SoLuong() == 1 && ThiDua::LayTai(0).GetLoaiSK() == "KHEN_THUONG",
            "doc lai data/thidua.txt: SK001 khen thuong");
    kiemTra(Account::SoLuong() == 3 && Account::LayTai(2).getUsername() == "nhanvien"
                && Account::LayTai(2).getMaCanBo() == "CB001" && Account::LayTai(2).getTrangThai(),
            "doc lai data/account.txt: TK003 nhanvien, lien ket CB001, dang hoat dong");

    // ============ Tong ket ============
    cout << "\n============================================" << endl;
    cout << "  Tong so phep kiem tra: " << soKiem << endl;
    cout << "  So FAIL: " << soLoi << endl;
    if (soLoi == 0) cout << "  KET QUA: PASS TAT CA" << endl;
    else cout << "  KET QUA: CO FAIL" << endl;
    cout << "============================================" << endl;

    lamRongData();
    if (banLenh != NULL) {
        delete banLenh;
        banLenh = NULL;
    }
    return soLoi == 0 ? 0 : 1;
}
