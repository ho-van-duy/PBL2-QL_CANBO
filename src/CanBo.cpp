#include "CanBo.h"
#include <cctype>
#include <iomanip>
#include <limits>
#include <sstream>

using namespace std;

string catKhoang(const string& s) {
    string kq;
    bool khoangTrang = true;
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == ' ' || s[i] == '\t') {
            if (!khoangTrang) { kq += ' '; khoangTrang = true; }
        } else {
            kq += s[i];
            khoangTrang = false;
        }
    }
    if (!kq.empty() && kq.back() == ' ') kq.pop_back();
    return kq;
}

string thuongHoa(const string& s) {
    string kq;
    bool khoangTrang = true;
    for (size_t i = 0; i < s.size(); i++) {
        unsigned char c = (unsigned char)s[i];
        if (c == ' ' || c == '\t') {
            if (!khoangTrang) { kq += ' '; khoangTrang = true; }
        } else if (isalnum(c)) {
            kq += (char)tolower(c);
            khoangTrang = false;
        }
    }
    if (!kq.empty() && kq.back() == ' ') kq.pop_back();
    return kq;
}

string chuanHoaMaCB(const string& s) {
    string k;
    for (size_t i = 0; i < s.size(); i++) {
        unsigned char c = (unsigned char)s[i];
        if (c == ' ' || c == '\t') continue;
        k += (char)toupper(c);
    }
    if (k.size() < 3 || k.size() > 5) return "";
    if (k[0] != 'C' || k[1] != 'B') return "";
    for (size_t i = 2; i < k.size(); i++)
        if (!isdigit((unsigned char)k[i])) return "";
    int so = 0;
    for (size_t i = 2; i < k.size(); i++) so = so * 10 + (k[i] - '0');
    if (so > 999) return "";
    ostringstream out;
    out << "CB" << setw(3) << setfill('0') << so;
    return out.str();
}

string soThuc(double x) {
    ostringstream out;
    out << fixed << setprecision(2) << x;
    string s = out.str();
    while (!s.empty() && s[s.size() - 1] == '0') s.erase(s.size() - 1);
    if (!s.empty() && s[s.size() - 1] == '.') s.erase(s.size() - 1);
    return s;
}

string tienTrieu(double trieu) {
    ostringstream out;
    out << fixed << setprecision(0) << trieu * 1000000.0;
    return out.str();
}

static string chuanHoaGioiTinh(const string& s) {
    string k = thuongHoa(s);
    if (k == "nam" || k == "m") return "Nam";
    if (k == "nu"  || k == "f") return "Nu";
    return "";
}

static string chuanHoaTrinhDo(const string& s) {
    string k = thuongHoa(s);
    if (k == "trung cap") return "Trung cap";
    if (k == "cao dang")  return "Cao dang";
    if (k == "dai hoc")   return "Dai hoc";
    if (k == "cao hoc")   return "Cao hoc";
    if (k == "tien si")   return "Tien si";
    return "";
}

static string chuanHoaXepLoai(const string& s) {
    string k = thuongHoa(s);
    if (k == "gioi")       return "Gioi";
    if (k == "kha")        return "Kha";
    if (k == "trung binh") return "Trung binh";
    if (k == "yeu")        return "Yeu";
    return "";
}

static void nhapChuoiBatBuoc(istream& in, const string& thongBao, string& kq) {
    while (true) {
        cout << thongBao;
        if (!getline(in, kq)) { kq = ""; return; }
        kq = catKhoang(kq);
        if (!kq.empty()) return;
        cout << "  Xin nhap lai, khong duoc de trong!\n";
    }
}

template <typename So>
static void nhapSo(istream& in, const string& thongBao, So& x, So minN, So maxN) {
    while (true) {
        cout << thongBao;
        if (in >> x) {
            in.ignore(numeric_limits<streamsize>::max(), '\n');
            if (x >= minN && x <= maxN) return;
            ostringstream gioiHan;
            gioiHan << fixed << setprecision(0) << minN << " den " << maxN;
            cout << "  Gia tri phai tu " << gioiHan.str() << ", hay nhap lai!\n";
            continue;
        }
        in.clear();
        in.ignore(numeric_limits<streamsize>::max(), '\n');
        if (in.eof()) { x = minN; return; }
        cout << "  Du lieu sai dinh dang so, hay nhap lai!\n";
    }
}

int doRong(const string& s) {
    int r = 0;
    for (size_t i = 0; i < s.size(); i++)
        if (((unsigned char)s[i] & 0xC0) != 0x80) r++;
    return r;
}

void inCot(ostream& out, const string& s, int rong) {
    out << s;
    for (int i = doRong(s); i < rong; i++) out << ' ';
}

void inVienBang(ostream& out, const vector<int>& rong) {
    out << "+";
    for (size_t i = 0; i < rong.size(); i++)
        out << string(rong[i] + 2, '-') << "+";
    out << "\n";
}

void inDongBang(ostream& out, const vector<string>& cot, const vector<int>& rong) {
    out << "|";
    for (size_t i = 0; i < rong.size(); i++) {
        out << " ";
        inCot(out, i < cot.size() ? cot[i] : string(""), rong[i]);
        out << " |";
    }
    out << "\n";
}

void inBang(ostream& out, const vector<string>& tieuDe, const vector<int>& rong,
            const vector<vector<string> >& dong) {
    inVienBang(out, rong);
    inDongBang(out, tieuDe, rong);
    inVienBang(out, rong);
    for (size_t i = 0; i < dong.size(); i++)
        inDongBang(out, dong[i], rong);
    inVienBang(out, rong);
}

CanBo::CanBo() : heSoLuong(0), phuCapTrachNhiem(0), anTrua(0), namTangLuong(0) {}

CanBo::CanBo(const string& ma, const string& ht, const string& gt, const string& qq,
             int ns, const string& cm, const string& td, double hsl, double pc,
             double at, int ntl, const string& xl)
    : Nguoi(ht, gt, qq, ns), maCB(ma), chuyenMon(cm), trinhDo(td),
      heSoLuong(hsl), phuCapTrachNhiem(pc), anTrua(at), namTangLuong(ntl),
      xepLoaiLaoDong(xl) {}

CanBo::~CanBo() {}

string CanBo::getMaCB() const { return maCB; }
string CanBo::getChuyenMon() const { return chuyenMon; }
string CanBo::getTrinhDo() const { return trinhDo; }
double CanBo::getHeSoLuong() const { return heSoLuong; }
double CanBo::getPhuCapTrachNhiem() const { return phuCapTrachNhiem; }
double CanBo::getAnTrua() const { return anTrua; }
int    CanBo::getNamTangLuong() const { return namTangLuong; }
string CanBo::getXepLoaiLaoDong() const { return xepLoaiLaoDong; }

void CanBo::setMaCB(const string& ma) { maCB = ma; }
void CanBo::setChuyenMon(const string& cm) { chuyenMon = cm; }
void CanBo::setTrinhDo(const string& td) { trinhDo = td; }
void CanBo::setHeSoLuong(double hsl) { heSoLuong = hsl; }
void CanBo::setPhuCapTrachNhiem(double pc) { phuCapTrachNhiem = pc; }
void CanBo::setAnTrua(double at) { anTrua = at; }
void CanBo::setNamTangLuong(int ntl) { namTangLuong = ntl; }
void CanBo::setXepLoaiLaoDong(const string& xl) { xepLoaiLaoDong = xl; }

void CanBo::nhapMa(istream& in) {
    while (true) {
        cout << "  Ma can bo (CBxxx)               : ";
        string tmp;
        if (!getline(in, tmp)) { maCB = "CB000"; return; }
        string ma = chuanHoaMaCB(tmp);
        if (!ma.empty()) { maCB = ma; return; }
        cout << "  Ma can bo phai gom CB va 3 chu so (vi du CB001), hay nhap lai!\n";
    }
}

void CanBo::nhapThongTinKhac(istream& in) {
    string tmp;
    int    ns;
    double d;

    nhapChuoiBatBuoc(in, "  Ho ten                          : ", tmp);
    hoTen = tmp;

    while (true) {
        cout << "  Gioi tinh (Nam/Nu)              : ";
        if (!getline(in, tmp)) { gioiTinh = "Nam"; break; }
        string g = chuanHoaGioiTinh(tmp);
        if (!g.empty()) { gioiTinh = g; break; }
        cout << "  Gioi tinh khong hop le, chi nhan Nam hoac Nu!\n";
    }

    nhapChuoiBatBuoc(in, "  Que quan                        : ", tmp);
    queQuan = tmp;

    string gioiHan = "1900-" + to_string(NAM_HIEN_TAI - 18) + ")";
    nhapSo<int>(in, "  Nam sinh (" + gioiHan + "        : ", ns, 1900, NAM_HIEN_TAI - 18);
    namSinh = ns;

    nhapChuoiBatBuoc(in, "  Chuyen mon                      : ", tmp);
    chuyenMon = tmp;

    while (true) {
        cout << "  Trinh do (Trung cap/Cao dang/Dai hoc/Cao hoc/Tien si): ";
        if (!getline(in, tmp)) { trinhDo = "Trung cap"; break; }
        string td = chuanHoaTrinhDo(tmp);
        if (!td.empty()) { trinhDo = td; break; }
        cout << "  Trinh do khong co trong danh muc, hay nhap lai!\n";
    }

    nhapSo<double>(in, "  He so luong (1.0-8.0)           : ", d, 1.0, 8.0);
    heSoLuong = d;

    nhapSo<double>(in, "  Phu cap trach nhiem (0.0-5.0)   : ", d, 0.0, 5.0);
    phuCapTrachNhiem = d;

    nhapSo<double>(in, "  Tro cap an trua (0.0-1.0 trieu) : ", d, 0.0, 1.0);
    anTrua = d;

    nhapSo<int>(in, "  Nam tang luong (2000-2100)      : ", ns, 2000, 2100);
    namTangLuong = ns;

    while (true) {
        cout << "  Xep loai lao dong (Gioi/Kha/Trung binh/Yeu): ";
        if (!getline(in, tmp)) { xepLoaiLaoDong = "Trung binh"; break; }
        string xl = chuanHoaXepLoai(tmp);
        if (!xl.empty()) { xepLoaiLaoDong = xl; break; }
        cout << "  Xep loai khong hop le, hay nhap lai!\n";
    }
}

void CanBo::nhap(istream& in) {
    nhapMa(in);
    nhapThongTinKhac(in);
}

void CanBo::xuat(ostream& out) const {
    vector<int> rong;
    rong.push_back(7);  rong.push_back(22); rong.push_back(5);  rong.push_back(6);
    rong.push_back(14); rong.push_back(22); rong.push_back(10); rong.push_back(6);
    rong.push_back(6);  rong.push_back(10); rong.push_back(8);  rong.push_back(13);
    rong.push_back(13);

    vector<string> cot;
    cot.push_back(maCB);
    cot.push_back(hoTen);
    cot.push_back(gioiTinh);
    cot.push_back(to_string(namSinh));
    cot.push_back(queQuan);
    cot.push_back(chuyenMon);
    cot.push_back(trinhDo);
    cot.push_back(soThuc(heSoLuong));
    cot.push_back(soThuc(phuCapTrachNhiem));
    cot.push_back(tienTrieu(anTrua));
    cot.push_back(to_string(namTangLuong));
    cot.push_back(xepLoaiLaoDong);
    cot.push_back(tienTrieu(thucLinh()));

    inDongBang(out, cot, rong);
}

double CanBo::thucLinh() const {
    return (heSoLuong + phuCapTrachNhiem) * 1.49 + anTrua;
}

string CanBo::thanhChuoi() const {
    ostringstream out;
    out << maCB << ';'
        << hoTen << ';'
        << gioiTinh << ';'
        << queQuan << ';'
        << namSinh << ';'
        << chuyenMon << ';'
        << trinhDo << ';'
        << soThuc(heSoLuong) << ';'
        << soThuc(phuCapTrachNhiem) << ';'
        << soThuc(anTrua) << ';'
        << namTangLuong << ';'
        << xepLoaiLaoDong;
    return out.str();
}

bool CanBo::docChuoi(const string& dong, CanBo& cb) {
    stringstream ss(dong);
    string truong[12];
    for (int i = 0; i < 12; i++) {
        if (!getline(ss, truong[i], ';')) return false;
    }

    string ma = chuanHoaMaCB(truong[0]);
    string g  = chuanHoaGioiTinh(truong[2]);
    string td = chuanHoaTrinhDo(truong[6]);
    string xl = chuanHoaXepLoai(truong[11]);
    if (ma.empty() || g.empty() || td.empty() || xl.empty()) return false;

    try {
        int    ns  = stoi(truong[4]);
        int    ntl = stoi(truong[10]);
        double hsl = stod(truong[7]);
        double pc  = stod(truong[8]);
        double at  = stod(truong[9]);
        if (ns  < 1900 || ns  > NAM_HIEN_TAI - 18) return false;
        if (ntl < 2000 || ntl > 2100)              return false;
        if (hsl < 1.0  || hsl > 8.0)               return false;
        if (pc  < 0.0  || pc  > 5.0)               return false;
        if (at  < 0.0  || at  > 1.0)               return false;

        string ht = catKhoang(truong[1]);
        string qq = catKhoang(truong[3]);
        string cm = catKhoang(truong[5]);
        if (ht.empty() || qq.empty() || cm.empty()) return false;

        cb.maCB          = ma;
        cb.hoTen         = ht;
        cb.gioiTinh      = g;
        cb.queQuan       = qq;
        cb.namSinh       = ns;
        cb.chuyenMon     = cm;
        cb.trinhDo       = td;
        cb.heSoLuong     = hsl;
        cb.phuCapTrachNhiem = pc;
        cb.anTrua        = at;
        cb.namTangLuong  = ntl;
        cb.xepLoaiLaoDong = xl;
    } catch (...) {
        return false;
    }
    return true;
}
