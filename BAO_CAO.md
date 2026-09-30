# BÁO CÁO TỔNG HỢP — HỆ THỐNG QUẢN LÝ CÁN BỘ (PBL2)

| | |
|---|---|
| **Đồ án** | Lập trình hướng đối tượng (PBL2) — Quản lý cán bộ |
| **Ngôn ngữ** | C++11 (`g++ -std=c++11 -Wall -Wextra`, build sạch 0 cảnh báo) |
| **Kiểm thử** | `kiemthu/KiemThu.cpp` — **94/94 PASS**, exit code 0 |
| **Tài liệu chi tiết** | `README.md` (ERD, class diagram, quy tắc nghiệp vụ, Big-O, đối chiếu đề bài) |

---

## 1. Phạm vi đã hoàn thành

| Mục | Nội dung |
|---|---|
| B11 | Lớp nền `ThucThe` + 8 model kế thừa |
| B12 | Module nghiệp vụ `NghiepVu` (gộp 1 module): `khoiTao`, `dangNhap`, `sinhMaTuDong`, 10 chức năng, tìm kiếm, quản lý 7 nhóm tài nguyên, `thongKeBaoCao` |
| B13 | Search / sort / statistics (QuickSort, tìm kiếm theo tên, 6 hàm thống kê) — gộp trong `NghiepVu` |
| B14 | `main.cpp`: đăng nhập + menu ADMIN/USER + 7 submenu nhóm, `chonMenu()` an toàn EOF |
| B15 | **Bộ kiểm thử tự động 94 phép kiểm tra** + **`NghiepVu::xuatTatCaTheoMau()`** (đa hình `ThucThe*`) nối vào mục 12 menu ADMIN + báo cáo này |

Toàn bộ 15 mục roadmap trong `README.md` đã đánh dấu ✅.

---

## 2. Kiến trúc OOP

### 2.1 Lớp nền `ThucThe` — điểm nhấn đa hình

```cpp
class ThucThe {
public:
    virtual void nhap() = 0;                      // thuần ảo
    virtual void xuat() const {                   // CÓ THÂN MẶC ĐỊNH
        cout << "----- " << loaiThucThe() << " -----" << endl;
    }
    virtual void ghiDong(ofstream& out) const = 0; // thuần ảo
    virtual void docDong(ifstream& in) = 0;        // thuần ảo
    virtual string loaiThucThe() const = 0;        // thuần ảo
    virtual ~ThucThe() {}
};
```

Đây là kỹ thuật **Template Method** ở dạng tối giản: `ThucThe` định nghĩa *khuôn mẫu* in nhãn loại, lớp con chỉ phải hiện thực `loaiThucThe()`. Nhờ vậy 8 lớp con không phải lặp lại dòng `----- CAN_BO -----`.

### 2.2 Bốn tính chất OOP

| Tính chất | Thể hiện |
|---|---|
| **Encapsulation** | Thuộc tính `private`, truy cập qua getter/setter. `NghiepVu` không đụng field, chỉ gọi `GetMaCB()`, `HieuLuc()`, `Them()`, `LayTai()`… Trạng thái "đang hiệu lực" được giấu sau `HieuLuc()` |
| **Abstraction** | `ThucThe` định nghĩa bộ hành vi chung (3 hàm thuần ảo + `xuat()` có thân mặc định); `NghiepVu` phơi ra API nghiệp vụ để `main.cpp` không biết chi tiết lưu trữ |
| **Inheritance** | 8 model `: public ThucThe` và `override` hành vi; mỗi `xuat()` của lớp con **gọi lại `ThucThe::xuat()`** ở đầu thân hàm để tái sử dụng mã của cha |
| **Polymorphism** | Gọi `xuat()` qua `ThucThe*` định tuyến đúng bản của từng loại lúc **chạy** (§4). Đa hình còn xảy ra *bên trong* `ThucThe::xuat()` khi gọi `loaiThucThe()` ảo |

Ngoài ra còn có **nạp chồng toán tử** (`PhanCong::operator==`, `Vector::operator[]`).

### 2.3 Phân biệt với ERD

- **DATABASE ENTITY** (mục 4 đề bài) = 8 bảng: `CAN_BO`, `PHONG_BAN`, `CHUC_VU`, `PHAN_CONG`, `LICH_SU_LUONG`, `DANH_GIA`, `KHEN_THUONG_KY_LUAT`, `TAI_KHOAN`.
- **C++ CLASS** = 8 model (kế thừa `ThucThe`) + `Vector` (cấu trúc dữ liệu tự viết) + tầng nghiệp vụ `NghiepVu`.
- Quan hệ 1–N **không nhúng con trỏ** giữa các model, mà dùng **khóa (mã ID)**; `NghiepVu` thực hiện phép "join" lúc chạy bằng cách quét danh sách và so khóa (FK == PK). Chi tiết từ quan hệ nào nằm ở đâu xem `README.md` §8.6.

---

## 3. Quy tắc nghiệp vụ đã chốt

| Mã | Quy tắc |
|---|---|
| C1 | `NGAYVAOLAM` ≤ `NGAYSINH` → từ chối khi thêm cán bộ |
| C2 | Một cán bộ **không được phục vụ 2 phòng chính cùng lúc**; phòng kiêm nhiệm không bị chặn |
| C3 | Trùng `ThoiGian` giữa các bản ghi `LICH_SU_LUONG` của cùng một cán bộ → từ chối |
| C4 | Xóa cán bộ = **xóa mềm** (`TrangThai = "NghiViec"`), giữ nguyên mã để không phá khoá ngoại/tham chiếu lịch sử |
| C5 | Xóa `PHONG_BAN`/`CHUC_VU` đang được phân công → từ chối; xóa mềm chỉ áp dụng cho cán bộ |
| C6 | Thêm tài khoản: tên đăng nhập phải duy nhất, mật khẩu ≥ 4 ký tự; tài khoản bị khoá không đăng nhập được |

Các quy tắc khác: mã khóa **tự sinh** (`sinhMaTuDong`) người dùng không nhập tay; chu kỳ tăng lương **3 năm**; `tongThuNhap()` chỉ cộng các bản ghi lương **đang hiệu lực**.

---

## 4. Đa hình runtime qua `ThucThe*`

### 4.1 Hàm dùng thật trong chương trình

`NghiepVu::xuatTatCaTheoMau()` (mục 12 của menu ADMIN):

```cpp
int dem[8] = { CanBo::SoLuong(), PhongBan::SoLuong(), ChucVu::SoLuong(), PhanCong::SoLuong(),
               Luong::SoLuong(), DanhGia::SoLuong(), ThiDua::SoLuong(), Account::SoLuong() };
int tong = /* tổng dem */;
ThucThe** ds = new ThucThe*[tong];          // mảng phẳng, cấp phát đúng số bản ghi thật
// … điền ds bằng &CanBo::LayTai(i), &PhongBan::LayTai(i), …
for (int i = 0; i < tong; i++) ds[i]->xuat(); // cùng kiểu con trỏ, 8 bản khác nhau
delete[] ds;
```

Một vòng `for` duy nhất gọi `xuat()` trên **cùng một kiểu con trỏ `ThucThe*`**, nhưng mỗi bản ghi in ra nhãn khác nhau — đó là bằng chứng đa hình lúc chạy. Bên trong mỗi `xuat()` của lớp con, lời gọi `ThucThe::xuat()` lại định tuyến `loaiThucThe()` ảo về đúng bản của lớp con.

Mảng được cấp phát động bằng `new[]` **theo đúng số bản ghi** thay vì một mảng cố định, nên không có giới hạn cắt dữ liệu và không tốn 128 KB stack.

### 4.2 Kết quả kiểm chứng

Nhóm 12 của bộ kiểm thử xác nhận:

- tạo được **8 con trỏ `ThucThe*`** trỏ tới 8 loại bản ghi khác nhau;
- `ds[i]->loaiThucThe()` trả về đúng 8 nhãn: `CAN_BO`, `PHONG_BAN`, `CHUC_VU`, `PHAN_CONG`, `LICH_SU_LUONG`, `DANH_GIA`, `KHEN_THUONG_KY_LUAT`, `TAI_KHOAN`;
- `ds[i]->xuat()` gọi đúng bản `override` của từng loại (kiểm tra dòng nhãn `----- <LOAI> -----`);
- `xuatTatCaTheoMau()` in đủ 8 loại với số bản ghi khớp từng bảng (18 bản ghi trong kịch bản kiểm thử).

Đã kiểm tra thủ công qua menu 12 của chương trình thật: in ra `----- CAN_BO -----`, `----- TAI_KHOAN -----`, … đúng như mong đợi.

---

## 5. Kết quả kiểm thử tự động

```
============================================
   KIEM THU TU DONG - HE THONG QUAN LY CAN BO
============================================

  Tong so phep kiem tra: 94
  So FAIL: 0
  KET QUA: PASS TAT CA
============================================
```

| # | Nhóm kiểm tra | Phép | Nội dung chính |
|---|---|---|---|
| 1 | Khởi tạo & sinh mã | 9 | 2 tài khoản demo; `sinhMaTuDong` cho 8 loại → `CB001`, `P01`, `CV01`, `PC001`, `ML001`, `DG001`, `SK001`, `TK003`; loại lạ → chuỗi rỗng |
| 2 | `Vector` | 6 | Nhập từ `cin`, `out_of_range`, copy constructor, gán tách biến |
| 3 | Phòng ban & chức vụ | 6 | Sinh mã `P01`→`P03`, `CV01`; lưu tên/phụ cấp |
| 4 | Cán bộ | 10 | Thêm nhiều/thêm một, mã `CB001`→`CB004`, mặc định `DangLamViec`, `TinhTuoi()`/`TinhNamLam()` |
| 5 | Tìm kiếm & sắp xếp | 6 | Tìm theo tên không phân biệt hoa/thường (2 kết quả), "không tìm thấy", QuickSort tăng/giản/khương hóa |
| 6 | Phân công — FK + C2 | 10 | Phòng chính; **C2** chặn 2 phòng chính, cho phép kiêm nhiệm; FK sai `MaCanBo`/`MaPhong`/`MaChucVu` đều bị từ chối |
| 7 | Lương — công thức + C3 | 6 | `tinhThucLinh()` = `(3.0+2.0)*1490000 + 1 = 7450001`; `HieuLuc()` theo `DenNgay`; **C3** chặn trùng thời gian |
| 8 | Đánh giá & khen thưởng | 4 | Lấy đánh giá **mới nhất** (DG002 2026 thay DG001 "Giỏi"); thêm sự kiện `SK001` |
| 9 | Tài khoản & đăng nhập | 9 | Tạo `TK003` liên kết `CB001`; trùng tên đăng nhập bị từ chối; đúng/sai mật khẩu; khoá → không đăng nhập được; mở khoá lại |
| 10 | Xóa mềm & sửa | 10 | Xóa mềm `CB004` (còn 4 bản ghi, `NghiViec`); thống kê vẫn tính cả bản ghi đã xóa mềm; sửa thông tin giữ nguyên mã; FK chặn xóa phòng/chức vụ đang dùng |
| 11 | Thống kê & báo cáo | 9 | `demCanBoNu` 2/4; `lietKeCanBoCNTT` 2; `lietKeDenHanTangLuong` 4/4; `tongThuNhap` = 5215000 (chỉ bản lương hiệu lực); `thongKeBaoCao` đủ 4 chỉ số |
| 12 | **Đa hình `ThucThe*`** | 20 | 8 con trỏ; 8 nhãn `loaiThucThe()`; 8 bản `xuat()`; `xuatTatCaTheoMau` đủ 8 loại & đúng số bản ghi |
| 13 | Lưu trữ & round-trip | 12 | Đếm dòng 5 file; `DocTatCa()` đọc lại đúng số lượng/nội dung/sau khi sửa & xóa mềm |

### 5.1 Cách chạy lại

```bash
g++ -std=c++11 -Wall -Wextra CanBo.cpp PhongBan.cpp ChucVu.cpp PhanCong.cpp Luong.cpp DanhGia.cpp ThiDua.cpp Account.cpp Vector.cpp NghiepVu.cpp kiemthu\KiemThu.cpp -o KT.exe
KT.exe
```

Harness có `main()` riêng nên **không** dùng `*.cpp` (sẽ trùng `main()` với `main.cpp` của chương trình chính).

Bộ kiểm thử **ghi đè** 8 file trong `data/` rồi đưa chúng về trạng thái "7 file rỗng + `account.txt` chứa đúng 2 tài khoản demo" khi kết thúc, nên chạy `QLCB.exe` ngay sau đó vẫn đăng nhập được. Điều kiện được phép chạy:

- 7 file `data/*.txt` (trừ `account.txt`) phải **rỗng**;
- `data/account.txt` được phép **rỗng hoặc chỉ chứa đúng 2 tài khoản demo** `TK001|admin|admin|ADMIN|1|` và `TK002|user|user|USER|1|` — đây chính là trạng thái sinh ra sau khi chạy chương trình chính một lần, nên việc chạy `KT.exe` ngay sau `QLCB.exe` vẫn được.

Nếu `data/` có dữ liệu thật (cán bộ, phân công, …): chương trình **dừng ngay, không ghi đè**, in ra file cần xử lý, exit code **2**. Chạy hợp lệ: **94/94 PASS** với exit code **0** (tất cả PASS) hoặc **1** (có FAIL).

---

## 6. Thuật toán & độ phức tạp

| Thuật toán | Nơi dùng | Big-O |
|---|---|---|
| Tìm kiếm tuyến tính theo mã | `NghiepVu::timXTheoMa()` (8 bảng), kiểm tra khóa ngoại | O(n) |
| Tìm theo tên (khớp chuỗi con) | `timKiemCanBoTheoTen()` | O(n · L) |
| QuickSort tăng/giảm | `sapXepTheoMa()` | O(n log n) trung bình |
| Quét danh sách khi join runtime | `HieuLuc()`, `demCanBoNu()`, `tongThuNhap()`, `hienThiDanhSach()` | O(n · k) |
| `sinhMaTuDong()` | quét hậu tố lớn nhất rồi +1 | O(n · L) |
| Tìm đánh giá mới nhất | `lietKeCanBoGioi()` | O(n · m) |

Chi tiết đầy đủ (kèm giải thích vì sao chọn QuickSort, đánh đổi bộ nhớ đệm) xem `README.md` §9.

---

## 7. Cấu trúc lưu trữ

- Mỗi model tự quản danh sách tĩnh động: `static T* ds; static int soLuong; static int sucChua;` cùng bộ `Them` / `XoaMot` / `LayTai` / `SoLuong` / `DocTatCa` / `GhiTatCa`, dùng `new[]/delete[]` và **nhân đôi khi đầy** → thể hiện rõ encapsulation + phân tích độ phức tạp.
- Lưu trữ file: mỗi bảng 1 file `.txt` trong `data/`, phân tách trường bằng dấu `|` (xem `README.md` §10).
- `NghiepVu::khoiTao()` nạp 8 file lúc khởi động và tạo 2 tài khoản demo (`admin`/`admin`, `user`/`user`) nếu chưa có.

---

## 8. Kiểm tra thủ công trên chương trình thật

Ngoài bộ kiểm thử tự động, `QLCB.exe` đã được chạy với kịch bản nhập từ bàn phím để xác nhận:

- đăng nhập `admin`/`admin` → vào đúng MENU ADMIN; sai mật khẩu → báo lỗi, tối đa 3 lần thử;
- thêm cán bộ qua menu 1 → sinh mã `CB001` và báo "Da them can bo CB001!";
- chọn **mục 12** → in `=== XUAT TAT CA DUOC QUA CON TRO ThucThe* (5 ban ghi) ===` kèm nhãn `----- CAN_BO -----`, `----- TAI_KHOAN -----`, …;
- các submenu nhóm quay lại đúng, chọn `0` ở menu chính → thoát êm; hết EOF → thoát gọn, không quay vô hạn;
- sau mỗi lần chạy, 7 file `data/*.txt` rỗng và `account.txt` chứa đúng 2 tài khoản demo, nên lần chạy kế tiếp vẫn đăng nhập được.

---

## 9. Đối chiếu với đề bài

| Yêu cầu đề bài | Mức độ đáp ứng |
|---|---|
| Xây dựng CSDL gồm 8 bảng với PK/FK | ✅ Theo đúng ERD mục 4 (`README.md`) |
| 4 tính chất OOP | ✅ §2.2 |
| Tìm kiếm | ✅ theo tên (khớp chuỗi con, không phân biệt hoa/thường) |
| Sắp xếp | ✅ QuickSort tăng/giảm theo mã |
| Thống kê / báo cáo | ✅ 6 hàm thống kê + `thongKeBaoCao` in 4 chỉ số tổng hợp |
| Xử lý file | ✅ đọc/ghi 8 file `.txt`, tự nạp lúc khởi động |
| Phân quyền Admin / User | ✅ `TAI_KHOAN.VaiTro`, 12 mục ADMIN / 6 mục USER |
| **Mở rộng ngoài đề bài** | • Mục 12 menu: xuất tất cả bản ghi qua đa hình `ThucThe*`<br>• Bộ kiểm thử tự động 94 phép kiểm tra<br>• Ràng buộc nghiệp vụ C1–C6 được kiểm tra tự động |

---

## 10. Hạn chế & hướng phát triển

**Hạn chế đã biết:**

1. Tìm kiếm/sắp xếp/thống kê đều quét mảng tuyến tính → O(n); quy mô dữ liệu rất lớn sẽ chậm. Có thể nâng lên cây nhị phân tìm kiếm / `std::map` cho khóa chính.
2. Dữ liệu lưu ở dạng text, chưa có chỉ mục; `DocTatCa()` phải đọc toàn bộ file mỗi lần khởi động.
3. `NghiepVu` là mô-đun nghiệp vụ tập trung khá lớn — có thể tách thành nhiều service nếu mở rộng thêm nghiệp vụ.
4. Xóa cán bộ là xóa mềm nên danh sách vẫn giữ bản ghi `NghiViec`; thống kê hiện **cố ý** tính cả bản ghi này (đã có phép kiểm tra riêng khẳng định hành vi này).
5. Xác thực tài khoản dùng so khớp chuỗi thuần, chưa mã hóa mật khẩu — chỉ phù hợp bài tập, không dùng cho sản phẩm thật.

**Hướng phát triển:**

- Thêm `std::map<string, ...>` để tra cứu khóa chính O(log n).
- Bổ sung `TAI_KHOAN.MaCanBo` một–một hai chiều chặt hơn, và chức năng đổi mật khẩu.
- Tách `Vector` thành module generic dùng template để tái sử dụng cho cả 8 model.
- Xuất báo cáo ra file CSV để in ấn.
