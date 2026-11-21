#ifndef QUANLYCANBO_H
#define QUANLYCANBO_H

#include "CanBo.h"
#include "DList.h"
#include <string>

using namespace std;

// Tra ve duong dan file du lieu phu hop voi thu muc hien tai (root hoac bin/)
string duongDanDuLieu();

class QuanLyCanBo {
private:
    DList<CanBo> ds;
    string       tenFile;

    bool tonTaiMa(const string& ma) const;
    void nhapMaKhongTrung(CanBo& cb);

public:
    QuanLyCanBo(const string& tenFile);
    ~QuanLyCanBo();

    bool docFile();
    bool ghiFile() const;

    void nhapDanhSach();
    void themCanBo();
    void xoaTheoMa();
    void hienThi() const;
    void lietKeNangLuong() const;
    void demCanBoNu() const;
    void tongThuNhap() const;
    void lietKeCNTT() const;
    void lietKeLoaiGioi() const;
    void sapXepTheoMa();

    int soLuongCanBo() const;
    vector<CanBo> layDanhSach() const;
    bool themCanBoGUI(const CanBo& cb);
    bool suaCanBoGUI(const string& maCu, const CanBo& cbMoi);
    bool xoaCanBoGUI(const string& ma);
};

#endif
