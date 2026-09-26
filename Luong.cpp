#include "Luong.h"
#include "CanBo.h"

Luong* Luong::ds = nullptr;
int Luong::soLuong = 0;
int Luong::sucChua = 0;

Luong::Luong(const string& maLuong, const string& maCanBo, const double& heSoLuong,
             const double& phuCap, const double& anTrua, const string& tuNgay,
             const string& denNgay, const string& lyDoTangLuong)
    : maLuong(maLuong), maCanBo(maCanBo), heSoLuong(heSoLuong), phuCap(phuCap),
      anTrua(anTrua), tuNgay(tuNgay), denNgay(denNgay), lyDoTangLuong(lyDoTangLuong) { }

void Luong::nhap() {
    cout << "Nhap ma can bo: ";
    getline(cin, maCanBo);
    do {
        cout << "Nhap he so luong (> 0): ";
        if (!(cin >> heSoLuong)) {
            cin.clear();
            cin.ignore(1000, '\n');
            heSoLuong = 0;
            continue;
        }
        cin.ignore(1000, '\n');
    } while (heSoLuong <= 0);
    do {
        cout << "Nhap phu cap (>= 0): ";
        if (!(cin >> phuCap)) {
            cin.clear();
            cin.ignore(1000, '\n');
            phuCap = -1;
            continue;
        }
        cin.ignore(1000, '\n');
    } while (phuCap < 0);
    do {
        cout << "Nhap an trua (>= 0): ";
        if (!(cin >> anTrua)) {
            cin.clear();
            cin.ignore(1000, '\n');
            anTrua = -1;
            continue;
        }
        cin.ignore(1000, '\n');
    } while (anTrua < 0);
    do {
        cout << "Nhap tu ngay ap dung (dd-MM-yyyy): ";
        getline(cin, tuNgay);
    } while (!NgayHopLe(tuNgay));
    do {
        cout << "Nhap den ngay (dd-MM-yyyy, bo trong neu dang hieu luc): ";
        getline(cin, denNgay);
    } while (!denNgay.empty() && !NgayHopLe(denNgay));
    cout << "Nhap ly do tang luong: ";
    getline(cin, lyDoTangLuong);
}

void Luong::xuat() const {
    cout << "Ma luong: " << maLuong
         << " | Ma can bo: " << maCanBo
         << " | HSL: " << heSoLuong
         << " | Phu cap: " << phuCap
         << " | An trua: " << anTrua
         << " | Tu ngay: " << tuNgay
         << " | Den ngay: " << (denNgay.empty() ? "(hieu luc)" : denNgay)
         << " | Ly do: " << lyDoTangLuong
         << " | Thuc linh: " << tinhThucLinh() << endl;
}

void Luong::ghiDong(ofstream& out) const {
    out << maLuong << '|' << maCanBo << '|' << heSoLuong << '|' << phuCap << '|'
        << anTrua << '|' << tuNgay << '|' << denNgay << '|' << lyDoTangLuong << endl;
}

void Luong::docDong(ifstream& in) {
    getline(in, maLuong, '|');
    getline(in, maCanBo, '|');
    string heSoStr, phuCapStr, anTruaStr;
    getline(in, heSoStr, '|');
    getline(in, phuCapStr, '|');
    getline(in, anTruaStr, '|');
    if (!heSoStr.empty()) heSoLuong = stod(heSoStr);
    if (!phuCapStr.empty()) phuCap = stod(phuCapStr);
    if (!anTruaStr.empty()) anTrua = stod(anTruaStr);
    getline(in, tuNgay, '|');
    getline(in, denNgay, '|');
    getline(in, lyDoTangLuong);
}

string Luong::getMaLuong() const { return maLuong; }
string Luong::getMaCanBo() const { return maCanBo; }
double Luong::getHeSoLuong() const { return heSoLuong; }
double Luong::getPhuCap() const { return phuCap; }
double Luong::getAnTrua() const { return anTrua; }
string Luong::getTuNgay() const { return tuNgay; }
string Luong::getDenNgay() const { return denNgay; }
string Luong::getLyDoTangLuong() const { return lyDoTangLuong; }

void Luong::setMaLuong(const string& maLuong) { this->maLuong = maLuong; }
void Luong::setMaCanBo(const string& maCanBo) { this->maCanBo = maCanBo; }
void Luong::setHeSoLuong(const double& heSoLuong) { this->heSoLuong = heSoLuong; }
void Luong::setPhuCap(const double& phuCap) { this->phuCap = phuCap; }
void Luong::setAnTrua(const double& anTrua) { this->anTrua = anTrua; }
void Luong::setTuNgay(const string& tuNgay) { this->tuNgay = tuNgay; }
void Luong::setDenNgay(const string& denNgay) { this->denNgay = denNgay; }
void Luong::setLyDoTangLuong(const string& lyDoTangLuong) { this->lyDoTangLuong = lyDoTangLuong; }

bool Luong::HieuLuc() const { return denNgay.empty(); }

double Luong::tinhThucLinh() const {
    return (heSoLuong + phuCap) * 1490000.0 + anTrua;
}

void Luong::Them(const Luong& a) {
    if (soLuong == sucChua) {
        sucChua = (sucChua == 0) ? 2 : sucChua * 2;
        Luong* moi = new Luong[sucChua];
        for (int i = 0; i < soLuong; i++) moi[i] = ds[i];
        delete[] ds;
        ds = moi;
    }
    ds[soLuong++] = a;
}

bool Luong::XoaMot(int idx) {
    if (idx < 0 || idx >= soLuong) return false;
    for (int i = idx; i < soLuong - 1; i++) ds[i] = ds[i + 1];
    soLuong--;
    return true;
}

Luong& Luong::LayTai(int idx) { return ds[idx]; }

void Luong::DocTatCa() {
    ifstream in("data/luong.txt");
    if (!in) return;
    soLuong = 0;
    while (true) {
        Luong a;
        a.docDong(in);
        if (!in) break;
        Them(a);
    }
    in.close();
}

void Luong::GhiTatCa() {
    ofstream out("data/luong.txt");
    if (!out) return;
    for (int i = 0; i < soLuong; i++) ds[i].ghiDong(out);
    out.close();
}