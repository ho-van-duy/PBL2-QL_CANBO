#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "QuanLyCanBo.h"
 
#include <GLFW/glfw3.h>
#include <algorithm>
#include <cctype>
#include <cfloat>
#include <cstdio>
#include <string>
#include <vector>
 
using namespace std;
 
static const float CO_CHU = 18.0f;
 
// ==================== FONT + GIAO DIEN ====================
 
static bool napFont(ImGuiIO& io) {
    const char* duongDan[] = {
        "font.ttf",
        "C:/Windows/Fonts/segoeui.ttf",
        "C:/Windows/Fonts/tahoma.ttf",
        "C:/Windows/Fonts/arial.ttf"
    };
    for (const char* p : duongDan) {
        FILE* f = fopen(p, "rb");
        if (!f) continue;
        fclose(f);
#if IMGUI_VERSION_NUM >= 19200
        ImFont* font = io.Fonts->AddFontFromFileTTF(p, CO_CHU);
#else
        ImFontConfig cfg;
        cfg.OversampleH = 2;
        cfg.OversampleV = 1;
        ImFont* font = io.Fonts->AddFontFromFileTTF(
            p, CO_CHU, &cfg, io.Fonts->GetGlyphRangesVietnamese());
#endif
        if (font) return true;
    }
    io.Fonts->AddFontDefault();
    return false;
}
 
static void caiGiaoDien() {
    ImGui::StyleColorsLight();
    ImGuiStyle& s = ImGui::GetStyle();
 
    s.WindowRounding    = 0.0f;
    s.ChildRounding     = 10.0f;
    s.FrameRounding     = 6.0f;
    s.PopupRounding     = 8.0f;
    s.GrabRounding      = 6.0f;
    s.ScrollbarRounding = 8.0f;
    s.WindowPadding     = ImVec2(16, 14);
    s.FramePadding      = ImVec2(10, 6);
    s.ItemSpacing       = ImVec2(10, 10);
    s.CellPadding       = ImVec2(8, 6);
    s.FrameBorderSize   = 0.0f;
 
    ImVec4* c = s.Colors;
    c[ImGuiCol_Text]              = ImVec4(0.10f, 0.12f, 0.16f, 1.0f);
    c[ImGuiCol_TextDisabled]      = ImVec4(0.45f, 0.50f, 0.58f, 1.0f);
    c[ImGuiCol_WindowBg]          = ImVec4(0.94f, 0.95f, 0.97f, 1.0f);
    c[ImGuiCol_ChildBg]           = ImVec4(1.00f, 1.00f, 1.00f, 1.0f);
    c[ImGuiCol_PopupBg]           = ImVec4(1.00f, 1.00f, 1.00f, 1.0f);
    c[ImGuiCol_Border]            = ImVec4(0.84f, 0.87f, 0.91f, 1.0f);
    c[ImGuiCol_FrameBg]           = ImVec4(0.95f, 0.96f, 0.98f, 1.0f);
    c[ImGuiCol_FrameBgHovered]    = ImVec4(0.90f, 0.93f, 0.97f, 1.0f);
    c[ImGuiCol_FrameBgActive]     = ImVec4(0.86f, 0.90f, 0.96f, 1.0f);
    c[ImGuiCol_Button]            = ImVec4(0.88f, 0.91f, 0.96f, 1.0f);
    c[ImGuiCol_ButtonHovered]     = ImVec4(0.80f, 0.86f, 0.95f, 1.0f);
    c[ImGuiCol_ButtonActive]      = ImVec4(0.72f, 0.80f, 0.92f, 1.0f);
    c[ImGuiCol_Header]            = ImVec4(0.10f, 0.45f, 0.95f, 0.18f);
    c[ImGuiCol_HeaderHovered]     = ImVec4(0.10f, 0.45f, 0.95f, 0.10f);
    c[ImGuiCol_HeaderActive]      = ImVec4(0.10f, 0.45f, 0.95f, 0.28f);
    c[ImGuiCol_TableHeaderBg]     = ImVec4(0.91f, 0.94f, 0.98f, 1.0f);
    c[ImGuiCol_TableBorderStrong] = ImVec4(0.80f, 0.84f, 0.90f, 1.0f);
    c[ImGuiCol_TableBorderLight]  = ImVec4(0.90f, 0.92f, 0.95f, 1.0f);
    c[ImGuiCol_TableRowBg]        = ImVec4(0, 0, 0, 0);
    c[ImGuiCol_TableRowBgAlt]     = ImVec4(0, 0, 0, 0.025f);
    c[ImGuiCol_ModalWindowDimBg]  = ImVec4(0, 0, 0, 0.35f);
}
 
static void chuToBatDau(float co) {
#if IMGUI_VERSION_NUM >= 19200
    ImGui::PushFont(nullptr, co);
#else
    ImGui::SetWindowFontScale(co / CO_CHU);
#endif
}
 
static void chuToKetThuc() {
#if IMGUI_VERSION_NUM >= 19200
    ImGui::PopFont();
#else
    ImGui::SetWindowFontScale(1.0f);
#endif
}
 
static void doiToanManHinh(GLFWwindow* w) {
    static int x = 100, y = 100, rong = 1280, cao = 780;
    if (glfwGetWindowMonitor(w)) {
        glfwSetWindowMonitor(w, nullptr, x, y, rong, cao, 0);
    } else {
        glfwGetWindowPos(w, &x, &y);
        glfwGetWindowSize(w, &rong, &cao);
        GLFWmonitor* mon = glfwGetPrimaryMonitor();
        const GLFWvidmode* vm = glfwGetVideoMode(mon);
        glfwSetWindowMonitor(w, mon, 0, 0, vm->width, vm->height, vm->refreshRate);
    }
}
 
// ==================== HAM HO TRO ====================
 
static void copyToBuffer(char* dst, size_t size, const string& src) {
    if (size > 0) snprintf(dst, size, "%s", src.c_str());
}
 
static string lowerText(string s) {
    for (char& c : s) c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    return s;
}
 
static string tienCoDau(double trieu) {
    string s = tienTrieu(trieu);
    string kq;
    int dem = 0;
    for (int i = static_cast<int>(s.size()) - 1; i >= 0; --i) {
        kq += s[i];
        if (++dem % 3 == 0 && i > 0 && s[i - 1] != '-') kq += '.';
    }
    reverse(kq.begin(), kq.end());
    return kq;
}
 
static string hienGioiTinh(const string& s) { return thuongHoa(s) == "nu" ? "Nữ" : "Nam"; }
 
static string hienTrinhDo(const string& s) {
    string k = thuongHoa(s);
    if (k == "trung cap") return "Trung cấp";
    if (k == "cao dang")  return "Cao đẳng";
    if (k == "dai hoc")   return "Đại học";
    if (k == "cao hoc")   return "Cao học";
    if (k == "tien si")   return "Tiến sĩ";
    return s;
}
 
static string hienXepLoai(const string& s) {
    string k = thuongHoa(s);
    if (k == "gioi")       return "Giỏi";
    if (k == "kha")        return "Khá";
    if (k == "trung binh") return "Trung bình";
    if (k == "yeu")        return "Yếu";
    return s;
}
 
 
template <typename T>
static int soSanh3(const T& a, const T& b) { return a < b ? -1 : (b < a ? 1 : 0); }
 
// ==================== MAN HINH / BO LOC ====================
 
enum ManHinh {
    MH_TRANGCHU = 0, MH_QUANLY, MH_NANGLUONG, MH_NU,
    MH_THUNHAP, MH_CNTT, MH_GIOI, MH_SAPXEP
};
 
static const char* TEN_MH[] = {
    "Trang chủ", "Quản lý cán bộ", "Nâng lương", "Cán bộ nữ",
    "Tổng thu nhập", "Cán bộ CNTT", "Xếp loại giỏi", "Sắp xếp theo mã"
};
 
static bool locTheoManHinh(const CanBo& cb, int mh) {
    switch (mh) {
        case MH_NANGLUONG: return cb.getNamTangLuong() <= NAM_HIEN_TAI;
        case MH_NU:        return thuongHoa(cb.getGioiTinh()) == "nu";
        case MH_CNTT:      return thuongHoa(cb.getChuyenMon()) == "cong nghe thong tin";
        case MH_GIOI:      return thuongHoa(cb.getXepLoaiLaoDong()) == "gioi";
        default:           return true;
    }
}
 
enum CotId {
    COT_STT = 0, COT_MA, COT_TEN, COT_GT, COT_QQ, COT_NS, COT_CM, COT_TD,
    COT_HSL, COT_PC, COT_AT, COT_NTL, COT_XL, COT_TL
};
 
static int soSanhCot(const CanBo& x, const CanBo& y, int cot) {
    switch (cot) {
        case COT_MA:  return soSanh3(x.getMaCB(), y.getMaCB());
        case COT_TEN: return soSanh3(x.getHoTen(), y.getHoTen());
        case COT_GT:  return soSanh3(x.getGioiTinh(), y.getGioiTinh());
        case COT_QQ:  return soSanh3(x.getQueQuan(), y.getQueQuan());
        case COT_NS:  return soSanh3(x.getNamSinh(), y.getNamSinh());
        case COT_CM:  return soSanh3(x.getChuyenMon(), y.getChuyenMon());
        case COT_TD:  return soSanh3(x.getTrinhDo(), y.getTrinhDo());
        case COT_HSL: return soSanh3(x.getHeSoLuong(), y.getHeSoLuong());
        case COT_PC:  return soSanh3(x.getPhuCapTrachNhiem(), y.getPhuCapTrachNhiem());
        case COT_AT:  return soSanh3(x.getAnTrua(), y.getAnTrua());
        case COT_NTL: return soSanh3(x.getNamTangLuong(), y.getNamTangLuong());
        case COT_XL:  return soSanh3(x.getXepLoaiLaoDong(), y.getXepLoaiLaoDong());
        case COT_TL:  return soSanh3(x.thucLinh(), y.thucLinh());
        default:      return 0;
    }
}
 
// ==================== FORM THONG TIN CAN BO ====================
 
struct FormCanBo {
    char ma[32] = "";
    char hoTen[128] = "";
    char gioiTinh[16] = "Nam";
    char queQuan[128] = "";
    int namSinh = 1995;
    char chuyenMon[128] = "";
    char trinhDo[32] = "Dai hoc";
    double heSoLuong = 2.34;
    double phuCap = 0.0;
    double anTrua = 0.0;
    int namTangLuong = 2026;
    char xepLoai[32] = "Kha";
};
 
enum CheDo { CD_XEM = 0, CD_THEM, CD_SUA };
 
static void napForm(FormCanBo& f, const CanBo& cb) {
    copyToBuffer(f.ma, sizeof(f.ma), cb.getMaCB());
    copyToBuffer(f.hoTen, sizeof(f.hoTen), cb.getHoTen());
    copyToBuffer(f.gioiTinh, sizeof(f.gioiTinh), cb.getGioiTinh());
    copyToBuffer(f.queQuan, sizeof(f.queQuan), cb.getQueQuan());
    f.namSinh = cb.getNamSinh();
    copyToBuffer(f.chuyenMon, sizeof(f.chuyenMon), cb.getChuyenMon());
    copyToBuffer(f.trinhDo, sizeof(f.trinhDo), cb.getTrinhDo());
    f.heSoLuong = cb.getHeSoLuong();
    f.phuCap = cb.getPhuCapTrachNhiem();
    f.anTrua = cb.getAnTrua();
    f.namTangLuong = cb.getNamTangLuong();
    copyToBuffer(f.xepLoai, sizeof(f.xepLoai), cb.getXepLoaiLaoDong());
}
 
static CanBo makeCanBo(const FormCanBo& f) {
    return CanBo(chuanHoaMaCB(f.ma), catKhoang(f.hoTen), f.gioiTinh,
                 catKhoang(f.queQuan), f.namSinh, catKhoang(f.chuyenMon),
                 f.trinhDo, f.heSoLuong, f.phuCap, f.anTrua,
                 f.namTangLuong, f.xepLoai);
}
 
static bool maDaTonTai(const vector<CanBo>& ds, const string& ma) {
    for (const CanBo& cb : ds)
        if (cb.getMaCB() == ma) return true;
    return false;
}
 
static bool formHopLe(const FormCanBo& f, string& loi) {
    if (chuanHoaMaCB(f.ma).empty())            loi = "Mã cán bộ không hợp lệ. Ví dụ: CB001.";
    else if (catKhoang(f.hoTen).empty())       loi = "Vui lòng nhập họ tên.";
    else if (catKhoang(f.queQuan).empty())     loi = "Vui lòng nhập quê quán.";
    else if (f.namSinh < 1900 || f.namSinh > NAM_HIEN_TAI - 18)
        loi = "Năm sinh phải từ 1900 đến " + to_string(NAM_HIEN_TAI - 18) + ".";
    else if (catKhoang(f.chuyenMon).empty())   loi = "Vui lòng nhập chuyên môn.";
    else if (f.heSoLuong < 1.0 || f.heSoLuong > 8.0) loi = "Hệ số lương phải từ 1 đến 8.";
    else if (f.phuCap < 0.0 || f.phuCap > 5.0)       loi = "Phụ cấp trách nhiệm phải từ 0 đến 5.";
    else if (f.anTrua < 0.0 || f.anTrua > 1.0)       loi = "Phụ cấp ăn trưa phải từ 0 đến 1 triệu.";
    else if (f.namTangLuong < 2000 || f.namTangLuong > 2100)
        loi = "Năm tăng lương phải từ 2000 đến 2100.";
    else { loi.clear(); return true; }
    return false;
}
 
struct LuaChon { const char* giaTri; const char* hienThi; };
 
static const LuaChon DS_GIOI_TINH[] = { {"Nam", "Nam"}, {"Nu", "Nữ"} };
static const LuaChon DS_TRINH_DO[] = {
    {"Trung cap", "Trung cấp"}, {"Cao dang", "Cao đẳng"},
    {"Dai hoc", "Đại học"}, {"Cao hoc", "Cao học"}, {"Tien si", "Tiến sĩ"}
};
static const LuaChon DS_XEP_LOAI[] = {
    {"Gioi", "Giỏi"}, {"Kha", "Khá"}, {"Trung binh", "Trung bình"}, {"Yeu", "Yếu"}
};
 
template <size_t N>
static void comboLua(const char* id, char* buf, size_t size, const LuaChon (&ds)[N]) {
    int cur = 0;
    for (size_t i = 0; i < N; ++i)
        if (string(buf) == ds[i].giaTri) cur = static_cast<int>(i);
 
    ImGui::SetNextItemWidth(-FLT_MIN);
    if (ImGui::BeginCombo(id, ds[cur].hienThi)) {
        for (size_t i = 0; i < N; ++i) {
            bool chon = (static_cast<int>(i) == cur);
            if (ImGui::Selectable(ds[i].hienThi, chon))
                copyToBuffer(buf, size, ds[i].giaTri);
            if (chon) ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }
}
 
static void nhanForm(const char* text) {
    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    ImGui::TextUnformatted(text);
    ImGui::TableSetColumnIndex(1);
}
 
// Ve form; cheDo quyet dinh co cho sua hay khong
static void veForm(FormCanBo& f, int cheDo) {
    if (!ImGui::BeginTable("formCanBo", 2)) return;
 
    ImGui::TableSetupColumn("nhan", ImGuiTableColumnFlags_WidthFixed, 140);
    ImGui::TableSetupColumn("giatri", ImGuiTableColumnFlags_WidthStretch);
 
    ImGui::BeginDisabled(cheDo == CD_XEM);
 
    nhanForm("Mã cán bộ:");
    ImGui::BeginDisabled(cheDo == CD_SUA);  // khong cho doi ma khi sua
    ImGui::SetNextItemWidth(-FLT_MIN);
    ImGui::InputText("##ma", f.ma, sizeof(f.ma));
    ImGui::EndDisabled();
 
    nhanForm("Họ tên:");
    ImGui::SetNextItemWidth(-FLT_MIN);
    ImGui::InputText("##hoten", f.hoTen, sizeof(f.hoTen));
 
    nhanForm("Giới tính:");
    comboLua("##gt", f.gioiTinh, sizeof(f.gioiTinh), DS_GIOI_TINH);
 
    nhanForm("Quê quán:");
    ImGui::SetNextItemWidth(-FLT_MIN);
    ImGui::InputText("##quequan", f.queQuan, sizeof(f.queQuan));
 
    nhanForm("Năm sinh:");
    ImGui::SetNextItemWidth(-FLT_MIN);
    ImGui::InputInt("##namsinh", &f.namSinh);
 
    nhanForm("Chuyên môn:");
    ImGui::SetNextItemWidth(-FLT_MIN);
    ImGui::InputText("##chuyenmon", f.chuyenMon, sizeof(f.chuyenMon));
 
    nhanForm("Trình độ:");
    comboLua("##td", f.trinhDo, sizeof(f.trinhDo), DS_TRINH_DO);
 
    nhanForm("Hệ số lương:");
    ImGui::SetNextItemWidth(-FLT_MIN);
    ImGui::InputDouble("##hsl", &f.heSoLuong, 0.1, 0.5, "%.2f");
 
    nhanForm("Phụ cấp TN:");
    ImGui::SetNextItemWidth(-FLT_MIN);
    ImGui::InputDouble("##pc", &f.phuCap, 0.1, 0.5, "%.2f");
 
    nhanForm("Phụ cấp ăn trưa:");
    ImGui::SetNextItemWidth(-FLT_MIN);
    ImGui::InputDouble("##antrua", &f.anTrua, 0.05, 0.1, "%.2f");
 
    nhanForm("Năm tăng lương:");
    ImGui::SetNextItemWidth(-FLT_MIN);
    ImGui::InputInt("##ntl", &f.namTangLuong);
 
    nhanForm("Xếp loại:");
    comboLua("##xl", f.xepLoai, sizeof(f.xepLoai), DS_XEP_LOAI);
 
    ImGui::EndDisabled();
 
    // Thuc linh tinh truc tiep theo cong thuc (HSL + PC) * 1.49 + an trua
    nhanForm("Thực lĩnh:");
    string tl = tienCoDau((f.heSoLuong + f.phuCap) * 1.49 + f.anTrua);
    char bufTL[64];
    snprintf(bufTL, sizeof(bufTL), "%s", tl.c_str());
    ImGui::SetNextItemWidth(-FLT_MIN);
    ImGui::InputText("##thuclinh", bufTL, sizeof(bufTL), ImGuiInputTextFlags_ReadOnly);
 
    ImGui::EndTable();
}
 
// ==================== THANH PHAN GIAO DIEN ====================
 
static bool nutMau(const char* nhan, ImVec4 mau, ImVec2 kichThuoc = ImVec2(0, 0)) {
    ImGui::PushStyleColor(ImGuiCol_Button, mau);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered,
        ImVec4(min(mau.x + 0.08f, 1.f), min(mau.y + 0.08f, 1.f), min(mau.z + 0.08f, 1.f), 1));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive,
        ImVec4(mau.x * 0.8f, mau.y * 0.8f, mau.z * 0.8f, 1));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 1, 1, 1));
    bool r = ImGui::Button(nhan, kichThuoc);
    ImGui::PopStyleColor(4);
    return r;
}
 
// Muc menu ben trai: chu can trai, muc dang chon to mau xanh
static bool mucMenu(const char* nhan, bool dangChon) {
    ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.0f, 0.5f));
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(16, 10));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 8.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(10, 4));
 
    ImGui::PushStyleColor(ImGuiCol_Button,
        dangChon ? ImVec4(0.12f, 0.45f, 0.95f, 1) : ImVec4(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered,
        dangChon ? ImVec4(0.18f, 0.52f, 1.00f, 1) : ImVec4(0, 0, 0, 0.06f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0, 0, 0.12f));
    ImGui::PushStyleColor(ImGuiCol_Text, dangChon ? ImVec4(1, 1, 1, 1) : ImVec4(0.10f, 0.12f, 0.16f, 1));
 
    bool r = ImGui::Button(nhan, ImVec2(-FLT_MIN, 0));
 
    ImGui::PopStyleColor(4);
    ImGui::PopStyleVar(4);
    return r;
}
 
static void theThongKe(const char* id, const char* nhan, const string& giaTri,
                       ImVec4 mau, float rong) {
    ImGui::BeginChild(id, ImVec2(rong, 90), true, ImGuiWindowFlags_NoScrollbar);
    ImGui::TextDisabled("%s", nhan);
    chuToBatDau(26.0f);
    ImGui::TextUnformatted(giaTri.c_str());
    chuToKetThuc();
    ImGui::EndChild();
}
 
static string csv(const string& s) {
    string kq = "\"";
    for (char c : s) { if (c == '"') kq += '"'; kq += c; }
    return kq + "\"";
}
 
// Xuat danh sach dang hien thi ra file CSV (mo duoc bang Excel)
static bool xuatCSV(const char* ten, const vector<CanBo>& ds, const vector<int>& chiSo) {
    FILE* f = fopen(ten, "wb");
    if (!f) return false;
 
    fputs("\xEF\xBB\xBF", f);  // BOM UTF-8 de Excel hieu tieng Viet
    fputs("STT,Mã CB,Họ tên,Giới tính,Quê quán,Năm sinh,Chuyên môn,Trình độ,"
          "Hệ số lương,Phụ cấp TN,Ăn trưa (triệu),Năm tăng lương,Xếp loại,Thực lĩnh (VND)\n", f);
 
    int stt = 1;
    for (int i : chiSo) {
        const CanBo& cb = ds[i];
        string dong = to_string(stt++) + "," + csv(cb.getMaCB()) + "," + csv(cb.getHoTen()) + ","
            + csv(hienGioiTinh(cb.getGioiTinh())) + "," + csv(cb.getQueQuan()) + ","
            + to_string(cb.getNamSinh()) + "," + csv(cb.getChuyenMon()) + ","
            + csv(hienTrinhDo(cb.getTrinhDo())) + "," + soThuc(cb.getHeSoLuong()) + ","
            + soThuc(cb.getPhuCapTrachNhiem()) + "," + soThuc(cb.getAnTrua()) + ","
            + to_string(cb.getNamTangLuong()) + "," + csv(hienXepLoai(cb.getXepLoaiLaoDong())) + ","
            + tienTrieu(cb.thucLinh()) + "\n";
        fputs(dong.c_str(), f);
    }
    fclose(f);
    return true;
}
 
static const char* TEN_POPUP_XOA = "Xác nhận xóa";
 
// ==================== CHUONG TRINH CHINH ====================
 
int main() {
    if (!glfwInit()) return 1;
 
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
 
    GLFWwindow* window = glfwCreateWindow(1366, 800, "Quản lý cán bộ", nullptr, nullptr);
    if (!window) { glfwTerminate(); return 1; }
 
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
 
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr;
 
    bool coFontVN = napFont(io);
    caiGiaoDien();
 
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
 
    QuanLyCanBo quanLy(duongDanDuLieu());
    bool docDuocFile = quanLy.docFile();
 
    int    manHinh = MH_QUANLY;
    int    cheDo = CD_XEM;
    int    dongChon = -1;
    char   oTimKiem[100] = "";
    string tuKhoa;              // tu khoa da ap dung (bam "Tim kiem" hoac Enter)
    FormCanBo form;
    string maDangSua, maCanChon, loi, thongBao;
    bool   thongBaoLoi = false;
    double thoiDiemThongBao = 0.0;
    bool   yeuCauMoXoa = false;
 
    auto baoThongBao = [&](const string& nd, bool la_loi) {
        thongBao = nd; thongBaoLoi = la_loi; thoiDiemThongBao = ImGui::GetTime();
    };
 
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
 
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
 
        if (ImGui::IsKeyPressed(ImGuiKey_F11, false)) doiToanManHinh(window);
 
        const float W = io.DisplaySize.x, H = io.DisplaySize.y;
        const float rongMenu = 230.0f, rongPhai = 360.0f, khoang = 14.0f, caoHeader = 76.0f;
 
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(io.DisplaySize);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::Begin("QuanLyCanBo", nullptr,
            ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar |
            ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBringToFrontOnFocus);
        ImGui::PopStyleVar();
 
        vector<CanBo> danhSach = quanLy.layDanhSach();
        int tongSo = static_cast<int>(danhSach.size());
 
        // Chon lai can bo vua them/sua xong (theo ma)
        if (!maCanChon.empty()) {
            dongChon = -1;
            for (int i = 0; i < tongSo; ++i)
                if (danhSach[i].getMaCB() == maCanChon) { dongChon = i; break; }
            if (dongChon >= 0) napForm(form, danhSach[dongChon]);
            cheDo = CD_XEM;
            maCanChon.clear();
        }
        if (dongChon >= tongSo) { dongChon = -1; form = FormCanBo{}; cheDo = CD_XEM; }
 
        // ================= KHUNG 1: MENU TRAI =================
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(14, 14));
        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(1, 1, 1, 1));
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 0));
        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 0.0f);
        ImGui::BeginChild("menu", ImVec2(rongMenu, H), true, ImGuiWindowFlags_NoScrollbar);
        ImGui::PopStyleVar(2);
        ImGui::PopStyleColor(2);
 
        chuToBatDau(22.0f);
        ImGui::TextUnformatted("Quản lý cán bộ");
        chuToKetThuc();
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
 
        for (int i = 0; i < 8; ++i) {
            if (mucMenu(TEN_MH[i], manHinh == i)) {
                if (manHinh != i) { cheDo = CD_XEM; loi.clear(); }
                manHinh = i;
            }
        }
 
 
        ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 62);
        ImGui::TextDisabled("Đoàn kết – Kỷ cương");
        ImGui::TextDisabled("Phát triển");
 
        ImGui::EndChild();
 
        // ================= HEADER =================
        {
            ImDrawList* dl = ImGui::GetWindowDrawList();
            ImU32 c1 = ImGui::GetColorU32(ImVec4(1, 1, 1, 1));
            ImU32 c2 = ImGui::GetColorU32(ImVec4(0.90f, 0.94f, 1.00f, 1));
            dl->AddRectFilledMultiColor(ImVec2(rongMenu, 0), ImVec2(W, caoHeader), c1, c2, c2, c1);
 
            ImGui::SetCursorPos(ImVec2(rongMenu + 24, 10));
            chuToBatDau(24.0f);
            ImGui::TextUnformatted("PHẦN MỀM QUẢN LÝ CÁN BỘ");
            chuToKetThuc();
            ImGui::SetCursorPosX(rongMenu + 24);
            ImGui::SetCursorPosY(42);
            ImGui::Text("Năm hiện tại: %d", NAM_HIEN_TAI);
 
            const char* chao = "Xin chào, Admin";
            ImGui::SetCursorPos(ImVec2(W - ImGui::CalcTextSize(chao).x - 28, 28));
            ImGui::TextUnformatted(chao);
        }
 
        // ================= KHUNG 2: DANH SACH (GIUA) =================
        const float xGiua = rongMenu + khoang;
        const float yPanel = caoHeader + khoang;
        const float caoPanel = H - yPanel - khoang;
        float rongGiua = W - xGiua - khoang - rongPhai - khoang;
        if (rongGiua < 420) rongGiua = 420;
 
        ImGui::SetCursorPos(ImVec2(xGiua, yPanel));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(18, 14));
        ImGui::BeginChild("giua", ImVec2(rongGiua, caoPanel), true, ImGuiWindowFlags_NoScrollbar);
        ImGui::PopStyleVar();
 
        chuToBatDau(22.0f);
        ImGui::TextUnformatted(TEN_MH[manHinh]);
        chuToKetThuc();
 
        if (!coFontVN)
            ImGui::TextColored(ImVec4(0.80f, 0.45f, 0.00f, 1),
                "Không tìm thấy font tiếng Việt. Hãy đặt file font.ttf cạnh chương trình.");
        if (!docDuocFile)
            ImGui::TextColored(ImVec4(0.82f, 0.15f, 0.15f, 1), "Cảnh báo: không đọc được canbo.txt");
 
        // ---- Thong ke ----
        int soNu = 0, soDenHan = 0;
        double tongThuNhap = 0;
        for (const CanBo& cb : danhSach) {
            if (thuongHoa(cb.getGioiTinh()) == "nu") soNu++;
            if (cb.getNamTangLuong() <= NAM_HIEN_TAI) soDenHan++;
            tongThuNhap += cb.thucLinh();
        }
 
        if (manHinh == MH_TRANGCHU) {
            float sp = ImGui::GetStyle().ItemSpacing.x;
            float rong = (ImGui::GetContentRegionAvail().x - sp) / 2.0f;
            theThongKe("c1", "TỔNG SỐ CÁN BỘ", to_string(tongSo), ImVec4(0.45f, 0.72f, 1, 1), rong);
            ImGui::SameLine();
            theThongKe("c2", "CÁN BỘ NỮ", to_string(soNu), ImVec4(1, 0.60f, 0.80f, 1), rong);
            theThongKe("c3", "ĐẾN HẠN NÂNG LƯƠNG", to_string(soDenHan), ImVec4(1, 0.80f, 0.35f, 1), rong);
            ImGui::SameLine();
            theThongKe("c4", "TỔNG THU NHẬP (VND)", tienCoDau(tongThuNhap), ImVec4(0.40f, 0.90f, 0.55f, 1), rong);
            ImGui::Spacing();
            ImGui::TextDisabled("Chọn mục ở menu bên trái để xem danh sách, lọc hoặc sắp xếp cán bộ.");
        }
        else {
            // ---- Tim kiem ----
            float sp = ImGui::GetStyle().ItemSpacing.x;
            float rongO = ImGui::GetContentRegionAvail().x - 2 * sp - 130 - 110;
            ImGui::SetNextItemWidth(max(rongO, 120.0f));
            bool enter = ImGui::InputTextWithHint("##tim", "Nhập mã cán bộ hoặc họ tên...",
                oTimKiem, sizeof(oTimKiem), ImGuiInputTextFlags_EnterReturnsTrue);
            ImGui::SameLine();
            if (nutMau("Tìm kiếm", ImVec4(0.10f, 0.42f, 0.90f, 1), ImVec2(130, 0)) || enter)
                tuKhoa = oTimKiem;
            ImGui::SameLine();
            if (nutMau("Làm mới", ImVec4(0.35f, 0.38f, 0.48f, 1), ImVec2(110, 0))) {
                oTimKiem[0] = '\0';
                tuKhoa.clear();
            }
 
            // ---- Cac nut thao tac ----
            bool coChon = dongChon >= 0;
 
            if (nutMau("+  Thêm", ImVec4(0.18f, 0.62f, 0.35f, 1), ImVec2(110, 0))) {
                form = FormCanBo{};
                dongChon = -1;
                cheDo = CD_THEM;
                loi.clear();
            }
            ImGui::SameLine();
 
            ImGui::BeginDisabled(!coChon);
            if (nutMau("Sửa", ImVec4(0.20f, 0.42f, 0.80f, 1), ImVec2(100, 0))) {
                maDangSua = danhSach[dongChon].getMaCB();
                cheDo = CD_SUA;
                loi.clear();
            }
            ImGui::SameLine();
            if (nutMau("Xóa", ImVec4(0.78f, 0.25f, 0.25f, 1), ImVec2(100, 0)))
                yeuCauMoXoa = true;
            ImGui::EndDisabled();
 
            ImGui::SameLine();
            bool xuat = nutMau("Xuất danh sách", ImVec4(0.35f, 0.38f, 0.48f, 1));
 
            if (!thongBao.empty()) {
                if (ImGui::GetTime() - thoiDiemThongBao > 4.0) thongBao.clear();
                else {
                    ImGui::SameLine();
                    ImGui::AlignTextToFramePadding();
                    ImGui::TextColored(thongBaoLoi ? ImVec4(0.82f, 0.15f, 0.15f, 1) : ImVec4(0.10f, 0.55f, 0.25f, 1),
                                       " %s", thongBao.c_str());
                }
            }
 
            // ---- Loc + tim ----
            vector<int> chiSo;
            string key = lowerText(tuKhoa);
            double tongHienThi = 0;
            for (int i = 0; i < tongSo; ++i) {
                const CanBo& cb = danhSach[i];
                if (!locTheoManHinh(cb, manHinh)) continue;
                if (!key.empty()
                    && lowerText(cb.getMaCB()).find(key) == string::npos
                    && lowerText(cb.getHoTen()).find(key) == string::npos)
                    continue;
                chiSo.push_back(i);
                tongHienThi += cb.thucLinh();
            }
 
            // Thu tu mac dinh theo man hinh (khi nguoi dung chua bam tieu de cot)
            if (manHinh == MH_THUNHAP)
                stable_sort(chiSo.begin(), chiSo.end(), [&](int a, int b) {
                    return danhSach[a].thucLinh() > danhSach[b].thucLinh(); });
            else if (manHinh == MH_SAPXEP)
                stable_sort(chiSo.begin(), chiSo.end(), [&](int a, int b) {
                    return danhSach[a].getMaCB() < danhSach[b].getMaCB(); });
 
            // ---- Bang ----
            float caoChan = ImGui::GetTextLineHeightWithSpacing() + 4;
            string idBang = "BangCanBo" + to_string(manHinh);  // moi man hinh 1 bang rieng
 
            if (ImGui::BeginTable(idBang.c_str(), 14,
                ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_BordersOuter |
                ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable |
                ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY |
                ImGuiTableFlags_Sortable | ImGuiTableFlags_SizingStretchProp,
                ImVec2(0, -caoChan)))
            {
                ImGui::TableSetupScrollFreeze(0, 1);
                ImGui::TableSetupColumn("STT", ImGuiTableColumnFlags_NoSort, 0.45f, COT_STT);
                ImGui::TableSetupColumn("Mã CB", 0, 0.7f, COT_MA);
                ImGui::TableSetupColumn("Họ tên", 0, 1.7f, COT_TEN);
                ImGui::TableSetupColumn("Giới tính", 0, 0.7f, COT_GT);
                ImGui::TableSetupColumn("Quê quán", 0, 1.1f, COT_QQ);
                ImGui::TableSetupColumn("Năm sinh", 0, 0.7f, COT_NS);
                ImGui::TableSetupColumn("Chuyên môn", 0, 1.7f, COT_CM);
                ImGui::TableSetupColumn("Trình độ", 0, 0.9f, COT_TD);
                ImGui::TableSetupColumn("HSL", 0, 0.5f, COT_HSL);
                ImGui::TableSetupColumn("PC", 0, 0.5f, COT_PC);
                ImGui::TableSetupColumn("Ăn trưa", 0, 0.9f, COT_AT);
                ImGui::TableSetupColumn("Năm NL", 0, 0.65f, COT_NTL);
                ImGui::TableSetupColumn("Xếp loại", 0, 0.85f, COT_XL);
                ImGui::TableSetupColumn("Thực lĩnh", 0, 1.1f, COT_TL);
                ImGui::TableHeadersRow();
 
                if (ImGuiTableSortSpecs* sp2 = ImGui::TableGetSortSpecs()) {
                    if (sp2->SpecsCount > 0) {
                        int cot = static_cast<int>(sp2->Specs[0].ColumnUserID);
                        bool tang = sp2->Specs[0].SortDirection == ImGuiSortDirection_Ascending;
                        stable_sort(chiSo.begin(), chiSo.end(), [&](int a, int b) {
                            int c = soSanhCot(danhSach[a], danhSach[b], cot);
                            return tang ? c < 0 : c > 0;
                        });
                    }
                }
 
                int stt = 0;
                for (int idx : chiSo) {
                    const CanBo& cb = danhSach[idx];
                    ++stt;
                    ImGui::TableNextRow();
 
                    ImGui::TableSetColumnIndex(0);
                    char label[32];
                    snprintf(label, sizeof(label), "%d##row%d", stt, idx);
                    if (ImGui::Selectable(label, dongChon == idx,
                            ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowOverlap)) {
                        dongChon = idx;
                        napForm(form, cb);
                        cheDo = CD_XEM;
                        loi.clear();
                    }
                    if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)) {
                        dongChon = idx;
                        napForm(form, cb);
                        maDangSua = cb.getMaCB();
                        cheDo = CD_SUA;
                        loi.clear();
                    }
 
                    ImGui::TableSetColumnIndex(1);  ImGui::TextUnformatted(cb.getMaCB().c_str());
                    ImGui::TableSetColumnIndex(2);  ImGui::TextUnformatted(cb.getHoTen().c_str());
                    ImGui::TableSetColumnIndex(3);  ImGui::TextUnformatted(hienGioiTinh(cb.getGioiTinh()).c_str());
                    ImGui::TableSetColumnIndex(4);  ImGui::TextUnformatted(cb.getQueQuan().c_str());
                    ImGui::TableSetColumnIndex(5);  ImGui::Text("%d", cb.getNamSinh());
                    ImGui::TableSetColumnIndex(6);  ImGui::TextUnformatted(cb.getChuyenMon().c_str());
                    ImGui::TableSetColumnIndex(7);  ImGui::TextUnformatted(hienTrinhDo(cb.getTrinhDo()).c_str());
                    ImGui::TableSetColumnIndex(8);  ImGui::TextUnformatted(soThuc(cb.getHeSoLuong()).c_str());
                    ImGui::TableSetColumnIndex(9);  ImGui::TextUnformatted(soThuc(cb.getPhuCapTrachNhiem()).c_str());
                    ImGui::TableSetColumnIndex(10); ImGui::TextUnformatted(soThuc(cb.getAnTrua()).c_str());
                    ImGui::TableSetColumnIndex(11);
                    ImGui::Text("%d", cb.getNamTangLuong());
                    ImGui::TableSetColumnIndex(12);
                    ImGui::TextUnformatted(hienXepLoai(cb.getXepLoaiLaoDong()).c_str());
                    ImGui::TableSetColumnIndex(13); ImGui::TextUnformatted(tienCoDau(cb.thucLinh()).c_str());
                }
                ImGui::EndTable();
            }
 
            if (xuat) {
                if (xuatCSV("danhsach_canbo.csv", danhSach, chiSo))
                    baoThongBao("Đã xuất ra danhsach_canbo.csv", false);
                else
                    baoThongBao("Không ghi được file xuất.", true);
            }
 
            if (manHinh == MH_THUNHAP)
                ImGui::Text("Tổng số: %d cán bộ   |   Tổng thu nhập: %s VND",
                            static_cast<int>(chiSo.size()), tienCoDau(tongHienThi).c_str());
            else
                ImGui::Text("Tổng số: %d cán bộ", static_cast<int>(chiSo.size()));
        }
 
        ImGui::EndChild();
 
        // ================= KHUNG 3: THONG TIN CAN BO (PHAI) =================
        ImGui::SameLine(0, khoang);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(18, 14));
        ImGui::BeginChild("phai", ImVec2(rongPhai, caoPanel), true);
        ImGui::PopStyleVar();
 
        chuToBatDau(22.0f);
        ImGui::TextUnformatted("Thông tin cán bộ");
        chuToKetThuc();
 
        const char* nhanCheDo = cheDo == CD_THEM ? "Đang thêm cán bộ mới"
                              : cheDo == CD_SUA  ? "Đang chỉnh sửa"
                              : (dongChon >= 0 ? "Đang xem – bấm Sửa để chỉnh" : "Chọn một cán bộ trong danh sách");
        ImGui::TextDisabled("%s", nhanCheDo);
        ImGui::Spacing();
 
        veForm(form, cheDo);
 
        if (!loi.empty())
            ImGui::TextColored(ImVec4(0.82f, 0.15f, 0.15f, 1), "%s", loi.c_str());
 
        ImGui::Spacing();
 
        float rongNut = (ImGui::GetContentRegionAvail().x - ImGui::GetStyle().ItemSpacing.x) / 2.0f;
 
        ImGui::BeginDisabled(cheDo == CD_XEM);
        if (nutMau("Lưu", ImVec4(0.10f, 0.42f, 0.90f, 1), ImVec2(rongNut, 38))) {
            loi.clear();
            if (formHopLe(form, loi)) {
                CanBo cb = makeCanBo(form);
                string maMoi = cb.getMaCB();
                bool them = (cheDo == CD_THEM);
 
                if (them && maDaTonTai(danhSach, maMoi)) {
                    loi = "Mã " + maMoi + " đã tồn tại, hãy chọn mã khác.";
                } else {
                    bool ok = them ? quanLy.themCanBoGUI(cb)
                                   : quanLy.suaCanBoGUI(maDangSua, cb);
                    if (ok) {
                        baoThongBao(them ? "Thêm cán bộ thành công." : "Cập nhật cán bộ thành công.", false);
                        maCanChon = maMoi;
                    } else {
                        loi = "Thao tác thất bại (lỗi ghi file hoặc dữ liệu không hợp lệ).";
                    }
                }
            }
        }
        ImGui::SameLine();
        if (nutMau("Hủy", ImVec4(0.35f, 0.38f, 0.48f, 1), ImVec2(rongNut, 38))) {
            loi.clear();
            if (dongChon >= 0) napForm(form, danhSach[dongChon]);
            else form = FormCanBo{};
            cheDo = CD_XEM;
        }
        ImGui::EndDisabled();
 
        ImGui::EndChild();
 
        // ================= POPUP XOA =================
        if (yeuCauMoXoa) {
            ImGui::OpenPopup(TEN_POPUP_XOA);
            yeuCauMoXoa = false;
        }
 
        ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
        if (ImGui::BeginPopupModal(TEN_POPUP_XOA, nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
            string maXoa, tenXoa;
            if (dongChon >= 0 && dongChon < tongSo) {
                maXoa = danhSach[dongChon].getMaCB();
                tenXoa = danhSach[dongChon].getHoTen();
            }
 
            ImGui::Text("Bạn có chắc muốn xóa cán bộ %s (%s)?", maXoa.c_str(), tenXoa.c_str());
            ImGui::TextDisabled("Dữ liệu sau khi xóa sẽ được cập nhật vào file.");
            ImGui::Spacing();
 
            if (nutMau("Xác nhận xóa", ImVec4(0.78f, 0.25f, 0.25f, 1), ImVec2(160, 0))) {
                if (!maXoa.empty() && quanLy.xoaCanBoGUI(maXoa)) {
                    baoThongBao("Xóa cán bộ thành công.", false);
                    dongChon = -1;
                    form = FormCanBo{};
                    cheDo = CD_XEM;
                } else {
                    baoThongBao("Xóa thất bại.", true);
                }
                ImGui::CloseCurrentPopup();
            }
            ImGui::SameLine();
            if (ImGui::Button("Hủy##xoa", ImVec2(110, 0)))
                ImGui::CloseCurrentPopup();
 
            ImGui::EndPopup();
        }
 
        ImGui::End();
 
        ImGui::Render();
        int dw, dh;
        glfwGetFramebufferSize(window, &dw, &dh);
        glViewport(0, 0, dw, dh);
        glClearColor(0.94f, 0.95f, 0.97f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }
 
    quanLy.ghiFile();
 
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
 