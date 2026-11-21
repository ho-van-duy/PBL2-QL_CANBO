#ifndef CANBO_H
#define CANBO_H

#include "Nguoi.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int NAM_HIEN_TAI = 2026;

class CanBo : public Nguoi {
private:
    string maCB;
    string chuyenMon;
    string trinhDo;
    double heSoLuong;
    double phuCapTrachNhiem;
    double anTrua;
    int    namTangLuong;
    string xepLoaiLaoDong;

public:
    CanBo();
    CanBo(const string& ma, const string& ht, const string& gt, const string& qq,
          int ns, const string& cm, const string& td, double hsl, double pc,
          double at, int ntl, const string& xl);
    virtual ~CanBo();

    string getMaCB() const;
    string getChuyenMon() const;
    string getTrinhDo() const;
    double getHeSoLuong() const;
    double getPhuCapTrachNhiem() const;
    double getAnTrua() const;
    int    getNamTangLuong() const;
    string getXepLoaiLaoDong() const;

    void setMaCB(const string& ma);
    void setChuyenMon(const string& cm);
    void setTrinhDo(const string& td);
    void setHeSoLuong(double hsl);
    void setPhuCapTrachNhiem(double pc);
    void setAnTrua(double at);
    void setNamTangLuong(int ntl);
    void setXepLoaiLaoDong(const string& xl);

    virtual void   nhap(istream& in);
    virtual void   xuat(ostream& out) const;
    virtual double thucLinh() const;

    void nhapMa(istream& in);
    void nhapThongTinKhac(istream& in);

    string thanhChuoi() const;
    static bool docChuoi(const string& dong, CanBo& cb);
};

string catKhoang(const string& s);
string thuongHoa(const string& s);
string chuanHoaMaCB(const string& s);
string soThuc(double x);
string tienTrieu(double trieu);
int    doRong(const string& s);
void   inCot(ostream& out, const string& s, int rong);
void   inVienBang(ostream& out, const vector<int>& rong);
void   inDongBang(ostream& out, const vector<string>& cot, const vector<int>& rong);
void   inBang(ostream& out, const vector<string>& tieuDe, const vector<int>& rong,
              const vector<vector<string> >& dong);

#endif
