#include "Account.h"

using namespace std;

Account* Account::ds = nullptr;
int Account::soLuong = 0;
int Account::sucChua = 0;

Account::Account(const string& maTaiKhoan, const string& username, const string& password,
                 const string& role, const bool& trangThai, const string& maCanBo)
    : maTaiKhoan(maTaiKhoan), username(username), password(password),
      role(role), trangThai(trangThai), maCanBo(maCanBo) { }

string Account::getMaTaiKhoan() const { return maTaiKhoan; }
string Account::getUsername() const { return username; }
string Account::getPassword() const { return password; }
string Account::getRole() const { return role; }
bool Account::getTrangThai() const { return trangThai; }
string Account::getMaCanBo() const { return maCanBo; }

void Account::setMaTaiKhoan(const string& maTaiKhoan) { this->maTaiKhoan = maTaiKhoan; }
void Account::setUsername(const string& username) { this->username = username; }
void Account::setPassword(const string& password) { this->password = password; }
void Account::setRole(const string& role) { this->role = role; }
void Account::setTrangThai(const bool& trangThai) { this->trangThai = trangThai; }
void Account::setMaCanBo(const string& maCanBo) { this->maCanBo = maCanBo; }

void Account::ghiDong(ofstream& out) const {
    out << maTaiKhoan << '|' << username << '|' << password << '|'
        << role << '|' << (trangThai ? 1 : 0) << '|' << maCanBo << endl;
}

void Account::docDong(ifstream& in) {
    getline(in, maTaiKhoan, '|');
    getline(in, username, '|');
    getline(in, password, '|');
    getline(in, role, '|');
    string trangThaiStr;
    getline(in, trangThaiStr, '|');
    trangThai = (trangThaiStr == "1");
    getline(in, maCanBo);
}

void Account::input() {
    cout << "Nhap username: ";
    cin >> username;
    cin.ignore();

    cout << "Nhap password: ";
    cin >> password;
    cin.ignore();
}

void Account::display() {
    cout << "Ma tai khoan: " << maTaiKhoan
        << " | Username: " << username
        << " | Password: " << password
        << " | Role: " << role
        << " | Trang thai: " << (trangThai ? "HoatDong" : "BiKhoa")
        << " | Ma can bo: " << maCanBo << endl;
}

void Account::Them(const Account& a) {
    if (soLuong == sucChua) {
        sucChua = (sucChua == 0) ? 2 : sucChua * 2;
        Account* moi = new Account[sucChua];
        for (int i = 0; i < soLuong; i++) moi[i] = ds[i];
        delete[] ds;
        ds = moi;
    }
    ds[soLuong++] = a;
}

bool Account::XoaMot(int idx) {
    if (idx < 0 || idx >= soLuong) return false;
    for (int i = idx; i < soLuong - 1; i++) ds[i] = ds[i + 1];
    soLuong--;
    return true;
}

Account& Account::LayTai(int idx) { return ds[idx]; }

void Account::DocTatCa() {
    ifstream in("data/account.txt");
    if (!in) return;
    soLuong = 0;
    while (true) {
        Account a;
        a.docDong(in);
        if (!in) break;
        Them(a);
    }
    in.close();
}

void Account::GhiTatCa() {
    ofstream out("data/account.txt");
    if (!out) return;
    for (int i = 0; i < soLuong; i++) ds[i].ghiDong(out);
    out.close();
}