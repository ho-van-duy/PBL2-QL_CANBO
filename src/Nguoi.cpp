#include "Nguoi.h"

Nguoi::Nguoi() : namSinh(0) {}

Nguoi::Nguoi(const string& ht, const string& gt, const string& qq, int ns)
    : hoTen(ht), gioiTinh(gt), queQuan(qq), namSinh(ns) {}

Nguoi::~Nguoi() {}

string Nguoi::getHoTen() const    { return hoTen; }
string Nguoi::getGioiTinh() const { return gioiTinh; }
string Nguoi::getQueQuan() const  { return queQuan; }
int    Nguoi::getNamSinh() const  { return namSinh; }
