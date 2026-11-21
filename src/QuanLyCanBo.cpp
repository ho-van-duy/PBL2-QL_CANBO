#include "QuanLyCanBo.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

using namespace std;

string duongDanDuLieu() {
    const char* cacDuongDan[] = {
        "data/canbo.txt",
        "../data/canbo.txt",
        "canbo.txt"
    };
    for (const char* p : cacDuongDan) {
        ifstream fi(p);
        if (fi.good()) return p;
    }
    return "data/canbo.txt";
}

static bool trungMa(const CanBo& a, const CanBo& b) {
    return a.getMaCB() == b.getMaCB();
}

static bool maTangDan(const CanBo& a, const CanBo& b) {
    return a.getMaCB() < b.getMaCB();
}

static bool thucLinhGiamDan(const CanBo* a, const CanBo* b) {
    return a->thucLinh() > b->thucLinh();
}

static vector<int> rongBangChinh() {
    vector<int> r;
    r.push_back(7);  r.push_back(22); r.push_back(5);  r.push_back(6);
    r.push_back(14); r.push_back(22); r.push_back(10); r.push_back(6);
    r.push_back(6);  r.push_back(10); r.push_back(8);  r.push_back(13);
    r.push_back(13);
    return r;
}

static vector<int> rongBang5Cot() {
    vector<int> r;
    r.push_back(7); r.push_back(22); r.push_back(22);
    r.push_back(10); r.push_back(13);
    return r;
}

static vector<int> rongBangNangLuong() {
    vector<int> r;
    r.push_back(7); r.push_back(22); r.push_back(22);
    r.push_back(13); r.push_back(13);
    return r;
}

static vector<string> tieuDe5Cot(const string& cot3, const string& cot4) {
    vector<string> t;
    t.push_back("Ma");
    t.push_back("Ho ten");
    t.push_back(cot3);
    t.push_back(cot4);
    t.push_back("Thuc linh");
    return t;
}

static vector<string> dong5Cot(
    const CanBo& cb,
    const string& cot3,
    const string& cot4
) {
    vector<string> d;
    d.push_back(cb.getMaCB());
    d.push_back(cb.getHoTen());
    d.push_back(cot3);
    d.push_back(cot4);
    d.push_back(tienTrieu(cb.thucLinh()));
    return d;
}

QuanLyCanBo::QuanLyCanBo(const string& file) : tenFile(file) {}

QuanLyCanBo::~QuanLyCanBo() {}

int QuanLyCanBo::soLuongCanBo() const {
    return ds.size();
}

vector<CanBo> QuanLyCanBo::layDanhSach() const {
    vector<CanBo> ketQua;

    for (DNode<CanBo>* p = ds.getHead(); p; p = p->next) {
        ketQua.push_back(p->data);
    }

    return ketQua;
}

bool QuanLyCanBo::themCanBoGUI(const CanBo& cb) {
    string ma = chuanHoaMaCB(cb.getMaCB());

    if (ma.empty() || tonTaiMa(ma)) {
        return false;
    }

    CanBo banSao = cb;
    banSao.setMaCB(ma);

    ds.themCuoi(banSao);

    if (!ghiFile()) {
        ds.xoa(banSao, trungMa);
        return false;
    }

    return true;
}

bool QuanLyCanBo::suaCanBoGUI(const string& maCu, const CanBo& cbMoi) {
    string maChuanCu = chuanHoaMaCB(maCu);
    string maMoi = chuanHoaMaCB(cbMoi.getMaCB());

    if (maChuanCu.empty() || maMoi.empty()) {
        return false;
    }

    DNode<CanBo>* nutCanSua = nullptr;

    for (DNode<CanBo>* p = ds.getHead(); p; p = p->next) {
        if (p->data.getMaCB() == maChuanCu) {
            nutCanSua = p;
            break;
        }
    }

    if (nutCanSua == nullptr) {
        return false;
    }

    if (maMoi != maChuanCu && tonTaiMa(maMoi)) {
        return false;
    }

    CanBo banSaoCu = nutCanSua->data;
    CanBo banSaoMoi = cbMoi;
    banSaoMoi.setMaCB(maMoi);

    nutCanSua->data = banSaoMoi;

    if (!ghiFile()) {
        nutCanSua->data = banSaoCu;
        return false;
    }

    return true;
}

bool QuanLyCanBo::xoaCanBoGUI(const string& ma) {
    string maChuan = chuanHoaMaCB(ma);

    if (maChuan.empty()) {
        return false;
    }

    DNode<CanBo>* nutCanXoa = nullptr;

    for (DNode<CanBo>* p = ds.getHead(); p; p = p->next) {
        if (p->data.getMaCB() == maChuan) {
            nutCanXoa = p;
            break;
        }
    }

    if (nutCanXoa == nullptr) {
        return false;
    }

    CanBo banSaoCu = nutCanXoa->data;

    if (!ds.xoa(banSaoCu, trungMa)) {
        return false;
    }

    if (!ghiFile()) {
        ds.themCuoi(banSaoCu);
        return false;
    }

    return true;
}

bool QuanLyCanBo::tonTaiMa(const string& ma) const {
    for (DNode<CanBo>* p = ds.getHead(); p; p = p->next) {
        if (p->data.getMaCB() == ma) {
            return true;
        }
    }

    return false;
}

void QuanLyCanBo::nhapMaKhongTrung(CanBo& cb) {
    while (tonTaiMa(cb.getMaCB())) {
        cout << "Ma \"" << cb.getMaCB()
             << "\" da ton tai trong danh sach, hay nhap ma khac.\n";

        while (true) {
            cout << "  Ma can bo (CBxxx)               : ";

            string ma;
            if (!getline(cin, ma)) return;

            string chuan = chuanHoaMaCB(ma);

            if (!chuan.empty()) {
                cb.setMaCB(chuan);
                break;
            }

            cout << "  Ma can bo phai gom CB va 3 chu so "
                 << "(vi du CB001), hay nhap lai!\n";
        }
    }
}

bool QuanLyCanBo::docFile() {
    ifstream fi(tenFile.c_str());

    if (!fi) return false;

    string dong;

    while (getline(fi, dong)) {
        if (catKhoang(dong).empty()) continue;

        CanBo cb;

        if (!CanBo::docChuoi(dong, cb)) continue;
        if (tonTaiMa(cb.getMaCB())) continue;

        ds.themCuoi(cb);
    }

    fi.close();
    return true;
}

bool QuanLyCanBo::ghiFile() const {
    ofstream fo(tenFile.c_str());

    if (!fo) return false;

    for (DNode<CanBo>* p = ds.getHead(); p; p = p->next) {
        fo << p->data.thanhChuoi() << "\n";
    }

    fo.close();
    return true;
}

void QuanLyCanBo::nhapDanhSach() {
    int n = 0;

    while (true) {
        cout << "So can bo can nhap: ";

        if (cin >> n && n > 0) break;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (cin.eof()) return;

        cout << "So luong khong hop le, hay nhap lai!\n";
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 1; i <= n; i++) {
        cout << "\n--- Can bo thu " << i << " ---\n";

        CanBo cb;
        cb.nhapMa(cin);
        nhapMaKhongTrung(cb);
        cb.nhapThongTinKhac(cin);

        ds.themCuoi(cb);
    }

    ghiFile();
    cout << "Da them " << n << " can bo vao danh sach.\n";
}

void QuanLyCanBo::themCanBo() {
    cout << "\n--- Them mot can bo ---\n";

    CanBo cb;
    cb.nhapMa(cin);
    nhapMaKhongTrung(cb);
    cb.nhapThongTinKhac(cin);

    ds.themCuoi(cb);
    ghiFile();

    cout << "Da them can bo \"" << cb.getMaCB()
         << "\" vao danh sach.\n";
}

void QuanLyCanBo::xoaTheoMa() {
    if (ds.isEmpty()) {
        cout << "Danh sach dang trong, khong co gi de xoa!\n";
        return;
    }

    string ma;

    while (true) {
        cout << "Nhap ma can bo can xoa (CBxxx): ";

        string tmp;
        if (!getline(cin, tmp)) return;

        ma = chuanHoaMaCB(tmp);

        if (!ma.empty()) break;

        cout << "Ma can bo khong hop le "
             << "(phai gom CB va 3 chu so, vi du CB001)!\n";
    }

    CanBo khoaMa;
    khoaMa.setMaCB(ma);

    if (ds.xoa(khoaMa, trungMa)) {
        ghiFile();
        cout << "Da loai bo can bo co ma \"" << ma
             << "\" khoi danh sach.\n";
    } else {
        cout << "Khong tim thay can bo co ma \"" << ma << "\".\n";
    }
}

void QuanLyCanBo::hienThi() const {
    if (ds.isEmpty()) {
        cout << "Danh sach dang trong!\n";
        return;
    }

    cout << "\nDANH SACH CAN BO (" << ds.size() << " nguoi):\n";

    vector<int> rong = rongBangChinh();

    vector<string> tieuDe;
    tieuDe.push_back("Ma");
    tieuDe.push_back("Ho ten");
    tieuDe.push_back("GT");
    tieuDe.push_back("NS");
    tieuDe.push_back("Que quan");
    tieuDe.push_back("Chuyen mon");
    tieuDe.push_back("Trinh do");
    tieuDe.push_back("HSL");
    tieuDe.push_back("PC");
    tieuDe.push_back("An trua");
    tieuDe.push_back("Nam NL");
    tieuDe.push_back("Xep loai");
    tieuDe.push_back("Thuc linh");

    inVienBang(cout, rong);
    inDongBang(cout, tieuDe, rong);
    inVienBang(cout, rong);

    for (DNode<CanBo>* p = ds.getHead(); p; p = p->next) {
        const Nguoi& ng = p->data;
        ng.xuat(cout);
    }

    inVienBang(cout, rong);
}

void QuanLyCanBo::lietKeNangLuong() const {
    if (ds.isEmpty()) {
        cout << "Danh sach dang trong!\n";
        return;
    }

    cout << "\nCAN BO DEN THOI DIEM NANG LUONG (nam tang luong <= "
         << NAM_HIEN_TAI << "):\n";

    vector<int> rong = rongBangNangLuong();

    vector<string> tieuDe;
    tieuDe.push_back("Ma");
    tieuDe.push_back("Ho ten");
    tieuDe.push_back("Chuyen mon");
    tieuDe.push_back("Nam tang luong");
    tieuDe.push_back("Thuc linh");

    vector<vector<string> > dong;

    for (DNode<CanBo>* p = ds.getHead(); p; p = p->next) {
        if (p->data.getNamTangLuong() > NAM_HIEN_TAI) continue;

        vector<string> d;
        d.push_back(p->data.getMaCB());
        d.push_back(p->data.getHoTen());
        d.push_back(p->data.getChuyenMon());
        d.push_back(to_string(p->data.getNamTangLuong()));
        d.push_back(tienTrieu(p->data.thucLinh()));

        dong.push_back(d);
    }

    if (dong.empty()) {
        cout << "(Khong co can bo nao den thoi diem nang luong.)\n";
        return;
    }

    inBang(cout, tieuDe, rong, dong);
}

void QuanLyCanBo::demCanBoNu() const {
    if (ds.isEmpty()) {
        cout << "Danh sach dang trong!\n";
        return;
    }

    vector<vector<string> > dong;

    for (DNode<CanBo>* p = ds.getHead(); p; p = p->next) {
        if (thuongHoa(p->data.getGioiTinh()) != "nu") continue;

        dong.push_back(
            dong5Cot(
                p->data,
                p->data.getChuyenMon(),
                p->data.getTrinhDo()
            )
        );
    }

    cout << "So can bo nu trong co quan: " << dong.size() << "\n";

    if (dong.empty()) {
        cout << "(Khong co can bo nu nao.)\n";
        return;
    }

    cout << "\nDANH SACH CAN BO NU:\n";

    inBang(
        cout,
        tieuDe5Cot("Chuyen mon", "Trinh do"),
        rongBang5Cot(),
        dong
    );
}

void QuanLyCanBo::tongThuNhap() const {
    if (ds.isEmpty()) {
        cout << "Danh sach dang trong!\n";
        return;
    }

    double tong = 0;
    vector<const CanBo*> dsTam;

    for (DNode<CanBo>* p = ds.getHead(); p; p = p->next) {
        tong += p->data.thucLinh();
        dsTam.push_back(&p->data);
    }

    sort(dsTam.begin(), dsTam.end(), thucLinhGiamDan);

    cout << "Tong thu nhap cua " << ds.size()
         << " can bo: " << tienTrieu(tong) << " VND\n";

    cout << "\nDANH SACH CAN BO SAP XEP THEO THUC LINH GIAM DAN:\n";

    vector<vector<string> > dong;

    for (size_t i = 0; i < dsTam.size(); i++) {
        dong.push_back(
            dong5Cot(
                *dsTam[i],
                dsTam[i]->getChuyenMon(),
                dsTam[i]->getTrinhDo()
            )
        );
    }

    inBang(
        cout,
        tieuDe5Cot("Chuyen mon", "Trinh do"),
        rongBang5Cot(),
        dong
    );
}

void QuanLyCanBo::lietKeCNTT() const {
    if (ds.isEmpty()) {
        cout << "Danh sach dang trong!\n";
        return;
    }

    cout << "\nCAN BO CHUYEN MON CONG NGHE THONG TIN:\n";

    vector<vector<string> > dong;

    for (DNode<CanBo>* p = ds.getHead(); p; p = p->next) {
        if (thuongHoa(p->data.getChuyenMon()) != "cong nghe thong tin")
            continue;

        dong.push_back(
            dong5Cot(
                p->data,
                p->data.getChuyenMon(),
                p->data.getTrinhDo()
            )
        );
    }

    if (dong.empty()) {
        cout << "(Khong co can bo nao chuyen mon Cong nghe thong tin.)\n";
        return;
    }

    inBang(
        cout,
        tieuDe5Cot("Chuyen mon", "Trinh do"),
        rongBang5Cot(),
        dong
    );
}

void QuanLyCanBo::lietKeLoaiGioi() const {
    if (ds.isEmpty()) {
        cout << "Danh sach dang trong!\n";
        return;
    }

    cout << "\nCAN BO XEP LOAI LAO DONG GIOI:\n";

    vector<vector<string> > dong;

    for (DNode<CanBo>* p = ds.getHead(); p; p = p->next) {
        if (thuongHoa(p->data.getXepLoaiLaoDong()) != "gioi")
            continue;

        dong.push_back(
            dong5Cot(
                p->data,
                p->data.getChuyenMon(),
                p->data.getXepLoaiLaoDong()
            )
        );
    }

    if (dong.empty()) {
        cout << "(Khong co can bo nao xep loai Gioi.)\n";
        return;
    }

    inBang(
        cout,
        tieuDe5Cot("Chuyen mon", "Xep loai"),
        rongBang5Cot(),
        dong
    );
}

void QuanLyCanBo::sapXepTheoMa() {
    if (ds.size() < 2) {
        cout << "Danh sach trong hoac chua du 2 can bo, khong can sap xep!\n";
        return;
    }

    ds.sapXep(maTangDan);
    ghiFile();

    cout << "Da sap xep danh sach theo ma can bo tang dan.\n";
    hienThi();
}