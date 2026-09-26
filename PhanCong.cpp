#include "PhanCong.h"
#include "CanBo.h"

PhanCong* PhanCong::ds = nullptr;
int PhanCong::soLuong = 0;
int PhanCong::sucChua = 0;

PhanCong::PhanCong(const string& maPhanCong, const string& maCanBo, const string& maPhong,
                   const string& maChucVu, const string& tuNgay, const string& denNgay,
                   const string& loaiPhanCong, const bool& laPhongChinh)
    : maPhanCong(maPhanCong), maCanBo(maCanBo), maPhong(maPhong), maChucVu(maChucVu),
      tuNgay(tuNgay), denNgay(denNgay), loaiPhanCong(loaiPhanCong), laPhongChinh(laPhongChinh) { }

void PhanCong::nhap() {
    cout << "Nhap ma can bo: ";
    getline(cin, maCanBo);
    cout << "Nhap ma phong: ";
    getline(cin, maPhong);
    cout << "Nhap ma chuc vu: ";
    getline(cin, maChucVu);
    do {
        cout << "Nhap tu ngay (dd-MM-yyyy): ";
        getline(cin, tuNgay);
    } while (!NgayHopLe(tuNgay));
    do {
        cout << "Nhap den ngay (dd-MM-yyyy, bo trong neu dang hieu luc): ";
        getline(cin, denNgay);
    } while (!denNgay.empty() && !NgayHopLe(denNgay));
    do {
        cout << "Nhap loai phan cong (ChinhThuc/KiemNhiem/DieuChuyen/BoNhiem/MienNhiem): ";
        getline(cin, loaiPhanCong);
    } while (loaiPhanCong != "ChinhThuc" && loaiPhanCong != "KiemNhiem" &&
             loaiPhanCong != "DieuChuyen" && loaiPhanCong != "BoNhiem" &&
             loaiPhanCong != "MienNhiem");
    int chon;
    do {
        cout << "La phong chinh? (1: co / 0: khong): ";
        if (!(cin >> chon)) {
            cin.clear();
            cin.ignore(1000, '\n');
            chon = -1;
            continue;
        }
        cin.ignore(1000, '\n');
    } while (chon != 0 && chon != 1);
    laPhongChinh = (chon == 1);
}

void PhanCong::xuat() const {
    cout << "Ma phan cong: " << maPhanCong
         << " | Ma can bo: " << maCanBo
         << " | Ma phong: " << maPhong
         << " | Ma chuc vu: " << maChucVu
         << " | Tu ngay: " << tuNgay
         << " | Den ngay: " << (denNgay.empty() ? "(hieu luc)" : denNgay)
         << " | Loai: " << loaiPhanCong
         << " | Phong chinh: " << (laPhongChinh ? "co" : "khong") << endl;
}

void PhanCong::ghiDong(ofstream& out) const {
    out << maPhanCong << '|' << maCanBo << '|' << maPhong << '|' << maChucVu << '|'
        << tuNgay << '|' << denNgay << '|' << loaiPhanCong << '|'
        << (laPhongChinh ? 1 : 0) << endl;
}

void PhanCong::docDong(ifstream& in) {
    getline(in, maPhanCong, '|');
    getline(in, maCanBo, '|');
    getline(in, maPhong, '|');
    getline(in, maChucVu, '|');
    getline(in, tuNgay, '|');
    getline(in, denNgay, '|');
    getline(in, loaiPhanCong, '|');
    string phongChinhStr;
    getline(in, phongChinhStr);
    laPhongChinh = (phongChinhStr == "1");
}

string PhanCong::getMaPhanCong() const { return maPhanCong; }
string PhanCong::getMaCanBo() const { return maCanBo; }
string PhanCong::getMaPhong() const { return maPhong; }
string PhanCong::getMaChucVu() const { return maChucVu; }
string PhanCong::getTuNgay() const { return tuNgay; }
string PhanCong::getDenNgay() const { return denNgay; }
string PhanCong::getLoaiPhanCong() const { return loaiPhanCong; }
bool PhanCong::getLaPhongChinh() const { return laPhongChinh; }

void PhanCong::setMaPhanCong(const string& maPhanCong) { this->maPhanCong = maPhanCong; }
void PhanCong::setMaCanBo(const string& maCanBo) { this->maCanBo = maCanBo; }
void PhanCong::setMaPhong(const string& maPhong) { this->maPhong = maPhong; }
void PhanCong::setMaChucVu(const string& maChucVu) { this->maChucVu = maChucVu; }
void PhanCong::setTuNgay(const string& tuNgay) { this->tuNgay = tuNgay; }
void PhanCong::setDenNgay(const string& denNgay) { this->denNgay = denNgay; }
void PhanCong::setLoaiPhanCong(const string& loaiPhanCong) { this->loaiPhanCong = loaiPhanCong; }
void PhanCong::setLaPhongChinh(const bool& laPhongChinh) { this->laPhongChinh = laPhongChinh; }

bool PhanCong::HieuLuc() const { return denNgay.empty(); }

bool PhanCong::operator==(const PhanCong& other) const {
    return maPhanCong == other.maPhanCong;
}

void PhanCong::Them(const PhanCong& a) {
    if (soLuong == sucChua) {
        sucChua = (sucChua == 0) ? 2 : sucChua * 2;
        PhanCong* moi = new PhanCong[sucChua];
        for (int i = 0; i < soLuong; i++) moi[i] = ds[i];
        delete[] ds;
        ds = moi;
    }
    ds[soLuong++] = a;
}

bool PhanCong::XoaMot(int idx) {
    if (idx < 0 || idx >= soLuong) return false;
    for (int i = idx; i < soLuong - 1; i++) ds[i] = ds[i + 1];
    soLuong--;
    return true;
}

PhanCong& PhanCong::LayTai(int idx) { return ds[idx]; }

void PhanCong::DocTatCa() {
    ifstream in("data/phancong.txt");
    if (!in) return;
    soLuong = 0;
    while (true) {
        PhanCong a;
        a.docDong(in);
        if (!in) break;
        Them(a);
    }
    in.close();
}

void PhanCong::GhiTatCa() {
    ofstream out("data/phancong.txt");
    if (!out) return;
    for (int i = 0; i < soLuong; i++) ds[i].ghiDong(out);
    out.close();
}