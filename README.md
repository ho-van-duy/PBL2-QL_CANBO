# PBL2 — CHƯƠNG TRÌNH QUẢN LÝ CÁN BỘ

> **Đề tài 21**: "Viết chương trình quản lý cán bộ theo hướng đối tượng."
> **Môn học**: PBL2 (Project-Based Learning 2) · **Ngành**: CNTT
> **Kiến trúc chính thức**: **8 bảng** (10 nghiệp vụ + `TAI_KHOAN` đăng nhập)

---

## MỤC LỤC

1. [Giới thiệu đề tài](#1-giới-thiệu-đề-tài)
2. [Yêu cầu đề tài — 10 chức năng](#2-yêu-cầu-đề-tài--10-chức-năng)
3. [Phân tích nghiệp vụ & Edge cases](#3-phân-tích-nghiệp-vụ--edge-cases)
4. [ERD — Sơ đồ 8 bảng](#4-erd--sơ-đồ-8-bảng)
5. [Thiết kế chi tiết từng bảng](#5-thiết-kế-chi-tiết-từng-bảng)
6. [Công thức & Ánh xạ thuộc tính đề bài](#6-công-thức--ánh-xạ-thuộc-tính-đề-bài)
7. [SQL Schema](#7-sql-schema)
8. [Kiến trúc OOP & Cấu trúc thư mục](#8-kiến-trúc-oop--cấu-trúc-thư-mục)
9. [Cấu trúc dữ liệu & Thuật toán (Big-O)](#9-cấu-trúc-dữ-liệu--thuật-toán-big-o)
10. [Lưu trữ dữ liệu (File Text)](#10-lưu-trữ-dữ-liệu-file-text)
11. [Kế hoạch triển khai](#11-kế-hoạch-triển-khai)

---

## 1. GIỚI THIỆU ĐỀ TÀI

Chương trình quản lý cán bộ theo hướng đối tượng (OOP) nhằm quản lý thông tin nhân sự của một cơ quan quy mô khoảng 1.000 cán bộ và sinh viên, bao gồm:

- Hồ sơ hành chính (mã, họ tên, giới tính, quê quán, năm sinh).
- Chuyên môn, trình độ.
- Phân công phòng ban, đảm nhiệm chức vụ (kèm lịch sử phân công).
- Lịch sử lương, phụ cấp.
- Đánh giá, xếp loại lao động.
- Khen thưởng / Kỷ luật.
- Đăng nhập phân quyền **ADMIN / USER**.

Hệ thống được xây dựng bằng ngôn ngữ **C++**, lưu trữ in-memory bằng **`Vector` mảng động tự viết** và ghi/đọc file text. Toàn bộ thiết kế (ERD, Class Diagram, code) dựa trên **mô hình 8 bảng thống nhất**.

---

## 2. YÊU CẦU ĐỀ TÀI — 10 CHỨC NĂNG

| # | Chức năng | Mô tả |
|---|-----------|-------|
| 1 | Tạo và nhập danh sách cán bộ | Nhập từ bàn phím nhiều cán bộ |
| 2 | Hiển thị danh sách cán bộ | In toàn bộ cán bộ cùng thông tin liên quan |
| 3 | Liệt kê cán bộ đến thời điểm nâng lương | Dựa trên lịch sử lương và chu kỳ nâng lương |
| 4 | Đếm số cán bộ nữ | Thống kê theo giới tính |
| 5 | Tính tổng thu nhập toàn bộ cán bộ | Tổng `Thực lĩnh` của danh sách |
| 6 | Liệt kê cán bộ chuyên môn "Công nghệ thông tin" | Lọc theo `ChuyenMon` |
| 7 | Hiển thị cán bộ xếp loại lao động "Giỏi" | Lọc theo bản đánh giá mới nhất (theo `NgayDanhGia`) |
| 8 | Sắp xếp danh sách theo mã cán bộ | Tăng/giảm dần |
| 9 | Xóa cán bộ theo mã | Xóa mềm (giữ lịch sử) |
| 10 | Thêm cán bộ vào danh sách | Thêm 1 cán bộ mới |

> Ngoài 10 chức năng bắt buộc của đề bài, hệ thống bổ sung module **đăng nhập & phân quyền ADMIN/USER** (mở rộng, không thuộc yêu cầu gốc).

---

## 3. PHÂN TÍCH NGHIỆP VỤ & EDGE CASES

### 3.1 Insight thiết kế
Không chỉ lưu **trạng thái hiện tại** mà còn lưu **lịch sử quá trình công tác**:

- Phòng ban / chức vụ: một cán bộ có thể chuyển phòng, kiêm nhiệm, thay đổi chức vụ qua các năm → dùng bảng `PHAN_CONG`.
- Lương: không chỉ lưu lương hiện tại mà lưu toàn bộ biến động theo `LICH_SU_LUONG`.
- Đánh giá: nhiều kỳ đánh giá trong `DANH_GIA`.

### 3.2 Edge cases được xử lý

| # | Tình huống | Cách xử lý |
|---|------------|------------|
| 1 | Một cán bộ thuộc nhiều phòng ban | `PHAN_CONG` nhiều dòng |
| 2 | Một cán bộ kiêm nhiệm | `LoaiPhanCong = KiemNhiem` |
| 3 | Chuyển phòng nhiều lần | Nhiều `PHAN_CONG` theo thời gian |
| 4 | Một cán bộ giữ nhiều chức vụ | `MaChucVu` khác nhau trong `PHAN_CONG` |
| 5 | Thay đổi chức vụ theo thời gian | `TuNgay/DenNgay` trong `PHAN_CONG` |
| 6 | Nhiều lần tăng lương | Nhiều bản `LICH_SU_LUONG` |
| 7 | Nhiều lần đánh giá | Nhiều bản `DANH_GIA` |
| 8 | Nhiều lần khen thưởng/kỷ luật | Nhiều bản `KHEN_THUONG_KY_LUAT` |
| 9 | Cán bộ nghỉ việc nhưng giữ lịch sử | Xóa mềm: `TrangThai = NghiViec` |
| 10 | Bản ghi đang hiệu lực | `DenNgay = NULL` |
| 11 | Trùng phòng/chức vụ chính hiệu lực | Ràng buộc không-chồng-thời-gian |
| 12 | Cán bộ chưa có tài khoản | `CAN_BO 1 : 0..1 TAI_KHOAN` (`MaCanBo` để NULL) |
| 13 | Tài khoản bị khóa | `TrangThai = false` → không đăng nhập được |

### 3.3 Ràng buộc nghiệp vụ (Constraint)

- **C1** `DenNgay = NULL` ⇔ bản ghi **đang hiệu lực** (không có ngày kết thúc).
- **C2** Một cán bộ có nhiều nhất **1 phòng chính hiệu lực** tại một thời điểm → kiểm tra overlap khi thêm `PHAN_CONG` (`LaPhongChinh = 1`).
- **C3** Các bảng có `TuNgay/DenNgay` phải **không chồng thời gian** với bản ghi cùng loại của cùng cán bộ.
- **C4** `UNIQUE(MaCanBo, NgayDanhGia)` — một cán bộ chỉ có 1 bản đánh giá trong một ngày.
- **C5** `HeSoLuong > 0`, `PhuCap >= 0`, `AnTrua >= 0`.
- **C6** Giá trị liệt kê: `GioiTinh` ∈ {Nam, Nu}; `TrangThai` ∈ {DangLamViec, NghiViec}; `LoaiPhanCong` ∈ {ChinhThuc, KiemNhiem, DieuChuyen, BoNhiem, MienNhiem}; `XepLoai` ∈ {Gioi, Kha, TrungBinh, Yeu}; `LoaiSuKien` ∈ {KHEN_THUONG, KY_LUAT}; `VaiTro` ∈ {ADMIN, USER}.
- **C7** Cán bộ **đến hạn nâng lương**: chênh lệch từ lần tăng lương gần nhất (hoặc ngày vào làm nếu chưa tăng) **≥ chu kỳ cố định 3 năm** (`CHU_KY_NANG_LUONG = 3`).
- **C8** `TenDangNhap` **UNIQUE**; `CAN_BO 1 : 0..1 TAI_KHOAN` — một cán bộ nhiều nhất 1 tài khoản.

---

## 4. ERD — SƠ ĐỒ 8 BẢNG

### 4.1 Mô tả quan hệ (Cardinality)

```
                        ┌──────────────┐
     ┌──────────────────│  CAN_BO      │──────────────────────┐
     │                  └──────┬───────┘                      │
     │         (trung tâm)    1                1              1
     │                     ┌───┴───┐          │               │
     │             ┌───────┤1      │1         │               │
     │             │       N        N         │               │
     │             │   ┌───┴──┐ ┌───┴──┐      │               │
     │             │   │PHAN  │ │PHAN  │      │               │
     │             │   │CONG  │ │CONG  │      │               │
     │             │   └──┬───┘ └──┬───┘      │               │
     │             │    N          N          │               │
   PHONG_BAN      │    │          ┌─┴─┐       1               1
     1 ───────────┘    └─┐         │CHUC│       N              N
                    ┌────┴────┐    │VU  │   ┌───┴────┐    ┌────┴─────────┐
                    │ 1:N     │    └────┘   │LICH_SU │    │DANH_GIA      │
                    └─────────┘             │LUONG   │    └──────────────┘
                                                                1
                              KHEN_THUONG_KY_LUAT ──────────────┘ N

                              0..1
          TAI_KHOAN ───────────────── CAN_BO (ngoài các quan hệ trên)
```

**Tóm tắt quan hệ (rút gọn):**

| Bảng | Quan hệ |
|---|---|
| `CAN_BO` 1 : N `PHAN_CONG` | 1 cán bộ → nhiều bản phân công |
| `PHONG_BAN` 1 : N `PHAN_CONG` | 1 phòng → nhiều phân công |
| `CHUC_VU` 1 : N `PHAN_CONG` | 1 chức vụ → nhiều phân công |
| `CAN_BO` 1 : N `LICH_SU_LUONG` | 1 cán bộ → nhiều bản lương |
| `CAN_BO` 1 : N `DANH_GIA` | 1 cán bộ → nhiều bản đánh giá |
| `CAN_BO` 1 : N `KHEN_THUONG_KY_LUAT` | 1 cán bộ → nhiều sự kiện khen/kỷ luật |
| `CAN_BO` 1 : 0..1 `TAI_KHOAN` | 1 cán bộ → tối đa 1 tài khoản |

> **Lưu ý thiết kế**: KHÔNG có quan hệ trực tiếp `CAN_BO → PHONG_BAN` hoặc `CAN_BO → CHUC_VU`. Mối liên kết này được quản lý hoàn toàn qua bảng trung gian `PHAN_CONG`.

### 4.2 Sơ đồ ERD dạng văn bản

```
┌──────────────┐         ┌──────────────────┐         ┌──────────────┐
│  CAN_BO      │  1    N │    PHAN_CONG     │ N    1  │  PHONG_BAN   │
│──────────────│─────────│──────────────────│─────────│──────────────│
│ MaCanBo  PK │         │ MaPhanCong   PK  │         │ MaPhong   PK │
│ HoTen        │         │ MaCanBo      FK  │         │ TenPhong     │
│ NgaySinh     │         │ MaPhong      FK  │         │ MoTa         │
│ GioiTinh     │         │ MaChucVu     FK  │         └──────────────┘
│ QueQuan      │         │ TuNgay           │
│ ChuyenMon    │         │ DenNgay (NULL)   │         ┌──────────────┐
│ TrinhDo      │         │ LoaiPhanCong     │   N  1  │  CHUC_VU     │
│ NgayVaoLam   │         │ LaPhongChinh     │─────────│──────────────│
│ TrangThai    │         └──────────────────┘         │ MaChucVu PK  │
└──────┬───────┘                                      │ TenChucVu    │
       │ 1                                            │ PhuCapChucVu │
  ┌────┴────────┐  N                                  │ MoTa         │
  │  LICH_SU_   │────────────────────                 └──────────────┘
  │  LUONG      │────────────────────
  │─────────────│  N
  │ MaLuong PK  │────────────────────
  │ MaCanBo FK  │     1
  │ HeSoLuong   │
  │ PhuCap      │      N
  │ AnTrua      │
  │ TuNgay      │                 ┌──────────────────┐
  │ DenNgay     │            N    │  DANH_GIA        │
  │ LyDoTangLuong│────────────────│──────────────────│
└─────────────┘  1 → N          │ MaDanhGia    PK  │
                                   │ MaCanBo      FK  │
        ┌──────────────────────────┤ XepLoai         │
        │                          │ NhanXet         │
        │   ┌───────────────────── │ NgayDanhGia     │
        │   ▼                       └──────────────────┘
        │   ┌──────────────────────────────────────┐
        └───│  KHEN_THUONG_KY_LUAT                 │
            │──────────────────────────────────────│
            │ MaSuKien  PK                         │
            │ MaCanBo   FK                         │
            │ LoaiSuKien (KHEN_THUONG | KY_LUAT)   │
            │ NoiDung                              │
            │ Nam                                  │
            │ LyDo                                 │
            └──────────────────────────────────────┘

┌───────────────────────────────────────────────────────────────┐
│  TAI_KHOAN  ·  CAN_BO 1 : 0..1 TAI_KHOAN                      │
│───────────────────────────────────────────────────────────────│
│ MaTaiKhoan  PK   TenDangNhap  UNIQUE   MatKhau   VaiTro       │
│ TrangThai   bool   MaCanBo  FK (NULL = cán bộ chưa có tài khoản)│
└───────────────────────────────────────────────────────────────┘
```

---

## 5. THIẾT KẾ CHI TIẾT TỪNG BẢNG

**Ánh xạ Bảng ERD → Class C++ → File dữ liệu** (mục này mô tả ở tầng CSDL; tên class code như mục 8):

| Bảng ERD (mục 4/5) | Class C++ (mục 8) | File dữ liệu (mục 10) |
|---|---|---|
| `CAN_BO` | `CanBo` | `data/canbo.txt` |
| `PHONG_BAN` | `PhongBan` | `data/phongban.txt` |
| `CHUC_VU` | `ChucVu` | `data/chucvu.txt` |
| `PHAN_CONG` | `PhanCong` | `data/phancong.txt` |
| `LICH_SU_LUONG` | `Luong` | `data/luong.txt` |
| `DANH_GIA` | `DanhGia` | `data/danhgia.txt` |
| `KHEN_THUONG_KY_LUAT` | `ThiDua` | `data/thidua.txt` |
| `TAI_KHOAN` | `Account` | `data/account.txt` |

### 5.1 CAN_BO — Thực thể trung tâm

| Cột | Kiểu | Ràng buộc | Mô tả |
|---|---|---|---|
| `MaCanBo` | VARCHAR | **PK** | Mã cán bộ, ví dụ "CB001" |
| `HoTen` | VARCHAR | NOT NULL | Họ và tên |
| `NgaySinh` | DATE | NOT NULL | Ngày sinh (đề gốc: "Năm sinh") |
| `GioiTinh` | VARCHAR | C6 | "Nam", "Nu" |
| `QueQuan` | VARCHAR | — | Quê quán |
| `ChuyenMon` | VARCHAR | — | Chuyên môn (vd: "Công nghệ thông tin") |
| `TrinhDo` | VARCHAR | — | Trình độ (vd: Đại học, Thạc sĩ, Tiến sĩ) |
| `NgayVaoLam` | DATE | — | Ngày vào làm |
| `TrangThai` | VARCHAR | C6 | "DangLamViec", "NghiViec" |

> **Lưu ý**: `TrinhDo` là thuộc tính của `CAN_BO` (không tách bảng). Thông tin đào tạo ở phạm vi PBL2 được đại diện tối thiểu bởi cột `TrinhDo` (trình độ đạt được sau đào tạo).

### 5.2 PHONG_BAN — Phòng ban/đơn vị

| Cột | Kiểu | Ràng buộc | Mô tả |
|---|---|---|---|
| `MaPhong` | VARCHAR | **PK** | Mã phòng, ví dụ "P01" |
| `TenPhong` | VARCHAR | NOT NULL | Tên phòng |
| `MoTa` | VARCHAR | — | Mô tả |

> Số lượng nhân viên của phòng **không lưu cứng** — tính động từ `PHAN_CONG` (tránh redundancy).

### 5.3 CHUC_VU — Chức vụ

| Cột | Kiểu | Ràng buộc | Mô tả |
|---|---|---|---|
| `MaChucVu` | VARCHAR | **PK** | Mã chức vụ, ví dụ "CV01" |
| `TenChucVu` | VARCHAR | NOT NULL | Tên chức vụ |
| `PhuCapChucVu` | DOUBLE | ≥ 0 (C5) | **Phụ cấp trách nhiệm (PC)** |
| `MoTa` | VARCHAR | — | Mô tả |

### 5.4 PHAN_CONG — Phân công phòng ban & chức vụ (bảng trung gian)

| Cột | Kiểu | Ràng buộc | Mô tả |
|---|---|---|---|
| `MaPhanCong` | VARCHAR | **PK** | Mã phân công |
| `MaCanBo` | VARCHAR | **FK → CAN_BO** | Cán bộ |
| `MaPhong` | VARCHAR | **FK → PHONG_BAN** | Phòng ban |
| `MaChucVu` | VARCHAR | **FK → CHUC_VU** | Chức vụ |
| `TuNgay` | DATE | NOT NULL | Từ ngày |
| `DenNgay` | DATE | NULL = hiệu lực (C1) | Đến ngày |
| `LoaiPhanCong` | VARCHAR | C6, C3 | ChinhThuc, KiemNhiem, DieuChuyen, BoNhiem, MienNhiem |
| `LaPhongChinh` | BOOLEAN | C2 | 1 = phòng chính |

> **Vai trò**: thay thế `BO_NHIEM` của kiến trúc cũ — đảm nhận cả phân công phòng, đảm nhiệm chức vụ, kiêm nhiệm, điều chuyển và bổ nhiệm/miễn nhiệm, đồng thời giữ lịch sử.

### 5.5 LICH_SU_LUONG — Lịch sử lương (class `Luong`)

| Cột | Kiểu | Ràng buộc | Mô tả |
|---|---|---|---|
| `MaLuong` | VARCHAR | **PK** | Mã bản ghi lương |
| `MaCanBo` | VARCHAR | **FK → CAN_BO** | Cán bộ |
| `HeSoLuong` | DOUBLE | > 0 (C5) | Hệ số lương (HSL) |
| `PhuCap` | DOUBLE | ≥ 0 (C5) | Phụ cấp trách nhiệm (snapshot từ `CHUC_VU.PhuCapChucVu`) |
| `AnTrua` | DOUBLE | ≥ 0 (C5) | Phụ cấp ăn trưa |
| `TuNgay` | DATE | NOT NULL | Thời điểm áp dụng |
| `DenNgay` | DATE | NULL = hiệu lực (C1) | Kết thúc áp dụng |
| `LyDoTangLuong` | VARCHAR | — | Lý do tăng lương |

> **`ThucLinh` KHÔNG lưu cứng** — là giá trị tính toán (xem mục 6).

### 5.6 DANH_GIA — Đánh giá / xếp loại

| Cột | Kiểu | Ràng buộc | Mô tả |
|---|---|---|---|
| `MaDanhGia` | VARCHAR | **PK** | Mã bản đánh giá |
| `MaCanBo` | VARCHAR | **FK → CAN_BO** | Cán bộ |
| `XepLoai` | VARCHAR | C6 | "Gioi", "Kha", "TrungBinh", "Yeu" |
| `NhanXet` | VARCHAR | — | Nhận xét |
| `NgayDanhGia` | DATE | C4 | Ngày đánh giá |

### 5.7 KHEN_THUONG_KY_LUAT — Khen thưởng & Kỷ luật (gộp) (class `ThiDua`)

| Cột | Kiểu | Ràng buộc | Mô tả |
|---|---|---|---|
| `MaSuKien` | VARCHAR | **PK** | Mã sự kiện |
| `MaCanBo` | VARCHAR | **FK → CAN_BO** | Cán bộ |
| `LoaiSuKien` | VARCHAR | C6 | "KHEN_THUONG" hoặc "KY_LUAT" |
| `NoiDung` | VARCHAR | — | Nội dung / hình thức |
| `Nam` | INT | — | Năm sự kiện |
| `LyDo` | VARCHAR | — | Lý do |

> `KHEN_THUONG_KY_LUAT` KHÔNG phải thuộc tính string đơn giản của `CAN_BO` — quan hệ `CAN_BO 1:N KHEN_THUONG_KY_LUAT` cho phép nhiều bản ghi/cán bộ.

### 5.8 TAI_KHOAN — Tài khoản đăng nhập (ADMIN + USER gộp chung) (class `Account`)

| Cột | Kiểu | Ràng buộc | Mô tả |
|---|---|---|---|
| `MaTaiKhoan` | VARCHAR | **PK** | Mã tài khoản, ví dụ "TK001" |
| `TenDangNhap` | VARCHAR | **UNIQUE** (C8) | Tên đăng nhập |
| `MatKhau` | VARCHAR | NOT NULL | Mật khẩu (demo lưu rõ ràng) |
| `VaiTro` | VARCHAR | C6 | "ADMIN" hoặc "USER" |
| `TrangThai` | BOOLEAN | — | `true` = hoạt động; `false` = bị khóa |
| `MaCanBo` | VARCHAR | **FK → CAN_BO**, NULL | Cán bộ tương ứng (USER); ADMIN để trống |

> **Cách tiếp cận**: MỘT class `Account` có cột `VaiTro` phân biệt Admin/User (KHÔNG dùng inheritance như một số bản tham khảo). Admin/User khác nhau chủ yếu ở **quyền**, nên `VaiTro` là đủ cho PBL2.

---

## 6. CÔNG THỨC & ÁNH XẠ THUỘC TÍNH ĐỀ BÀI

### 6.1 Công thức tính Thực lĩnh

```
ThucLinh = (HeSoLuong + PhuCap) * 1.490.000 + AnTrua
```

- **HeSoLuong** (HSL): lấy từ bản `LICH_SU_LUONG` đang hiệu lực.
- **PhuCap** (PC): snapshot được chụp từ `CHUC_VU.PhuCapChucVu` (qua `PHAN_CONG` hiệu lực) khi lập bản lương.
- **AnTrua**: lưu trong `LICH_SU_LUONG`.
- `ThucLinh` là **hàm tính toán** (`tinhThucLinh()`), không phải cột lưu trữ — đảm bảo luôn nhất quán với đúng 3 thành phần trên.

### 6.2 Ánh xạ thuộc tính đề bài → Bảng

| Thuộc tính đề bài | Bảng lưu trữ |
|---|---|
| Mã cán bộ | `CAN_BO.MaCanBo` |
| Họ tên | `CAN_BO.HoTen` |
| Giới tính | `CAN_BO.GioiTinh` |
| Quê quán | `CAN_BO.QueQuan` |
| Năm sinh | `CAN_BO.NgaySinh` (lấy năm) |
| Chuyên môn | `CAN_BO.ChuyenMon` |
| Trình độ | `CAN_BO.TrinhDo` |
| Chức vụ | `PHAN_CONG.MaChucVu` → `CHUC_VU` (bản hiệu lực) |
| Hệ số lương | `LICH_SU_LUONG.HeSoLuong` (bản hiệu lực) |
| Phụ cấp trách nhiệm | `CHUC_VU.PhuCapChucVu` → snapshot `LICH_SU_LUONG.PhuCap` |
| Ăn trưa | `LUONG.AnTrua` |
| **Thực lĩnh** | **Tính toán** `= (HSL + PC) * 1.490.000 + AnTrua` |
| Năm tăng lương | `LUONG.TuNgay` (lần tăng gần nhất) |
| Xếp loại lao động | `DANH_GIA.XepLoai` (bản mới nhất theo `NgayDanhGia`) |

---

## 7. SQL SCHEMA

```sql
CREATE TABLE CAN_BO (
    MaCanBo      VARCHAR(10) PRIMARY KEY,
    HoTen        VARCHAR(100) NOT NULL,
    NgaySinh     DATE NOT NULL,
    GioiTinh     VARCHAR(10) CHECK (GioiTinh IN ('Nam','Nu')),
    QueQuan      VARCHAR(100),
    ChuyenMon    VARCHAR(100),
    TrinhDo      VARCHAR(50),
    NgayVaoLam   DATE,
    TrangThai    VARCHAR(20) DEFAULT 'DangLamViec'
                 CHECK (TrangThai IN ('DangLamViec','NghiViec'))
);

CREATE TABLE PHONG_BAN (
    MaPhong   VARCHAR(10) PRIMARY KEY,
    TenPhong  VARCHAR(100) NOT NULL,
    MoTa      VARCHAR(200)
);

CREATE TABLE CHUC_VU (
    MaChucVu      VARCHAR(10) PRIMARY KEY,
    TenChucVu     VARCHAR(100) NOT NULL,
    PhuCapChucVu  DOUBLE CHECK (PhuCapChucVu >= 0),
    MoTa           VARCHAR(200)
);

CREATE TABLE PHAN_CONG (
    MaPhanCong    VARCHAR(10) PRIMARY KEY,
    MaCanBo       VARCHAR(10) NOT NULL REFERENCES CAN_BO(MaCanBo),
    MaPhong       VARCHAR(10) NOT NULL REFERENCES PHONG_BAN(MaPhong),
    MaChucVu      VARCHAR(10) NOT NULL REFERENCES CHUC_VU(MaChucVu),
    TuNgay        DATE NOT NULL,
    DenNgay       DATE,                 -- NULL = dang hieu luc
    LoaiPhanCong  VARCHAR(20) CHECK (LoaiPhanCong IN
                  ('ChinhThuc','KiemNhiem','DieuChuyen','BoNhiem','MienNhiem')),
    LaPhongChinh  BOOLEAN DEFAULT 0
);

CREATE TABLE LICH_SU_LUONG (
    MaLuong        VARCHAR(10) PRIMARY KEY,
    MaCanBo        VARCHAR(10) NOT NULL REFERENCES CAN_BO(MaCanBo),
    HeSoLuong      DOUBLE CHECK (HeSoLuong > 0),
    PhuCap         DOUBLE CHECK (PhuCap >= 0),
    AnTrua         DOUBLE CHECK (AnTrua >= 0),
    TuNgay         DATE NOT NULL,
    DenNgay        DATE,                 -- NULL = dang hieu luc
    LyDoTangLuong  VARCHAR(200)
);

CREATE TABLE DANH_GIA (
    MaDanhGia    VARCHAR(10) PRIMARY KEY,
    MaCanBo      VARCHAR(10) NOT NULL REFERENCES CAN_BO(MaCanBo),
    XepLoai      VARCHAR(20) CHECK (XepLoai IN ('Gioi','Kha','TrungBinh','Yeu')),
    NhanXet      VARCHAR(200),
    NgayDanhGia  DATE,
    UNIQUE (MaCanBo, NgayDanhGia)
);

CREATE TABLE KHEN_THUONG_KY_LUAT (
    MaSuKien    VARCHAR(10) PRIMARY KEY,
    MaCanBo     VARCHAR(10) NOT NULL REFERENCES CAN_BO(MaCanBo),
    LoaiSuKien  VARCHAR(20) CHECK (LoaiSuKien IN ('KHEN_THUONG','KY_LUAT')),
    NoiDung     VARCHAR(200),
    Nam         INT,
    LyDo        VARCHAR(200)
);

CREATE TABLE TAI_KHOAN (
    MaTaiKhoan   VARCHAR(10) PRIMARY KEY,
    TenDangNhap  VARCHAR(50) NOT NULL UNIQUE,
    MatKhau      VARCHAR(50) NOT NULL,
    VaiTro       VARCHAR(10) CHECK (VaiTro IN ('ADMIN','USER')),
    TrangThai    BOOLEAN DEFAULT TRUE,
    MaCanBo      VARCHAR(10) REFERENCES CAN_BO(MaCanBo)   -- NULL = chua co tai khoan
);
```

---

## 8. KIẾN TRÚC OOP & CẤU TRÚC THƯ MỤC

### 8.1 Nguyên tắc OOP — 4 tính chất hiện rõ trong code

Chương trình thể hiện đầy đủ **4 tính chất cơ bản của lập trình hướng đối tượng**:

| Tính chất | Cách thể hiện trong đồ án |
|---|---|
| **Encapsulation** (đóng gói) | Mọi thuộc tính của mỗi thực thể là `private`, truy cập duy nhất qua getter/setter. Tầng nghiệp vụ `NghiepVu` chỉ gọi qua interface (`GetMaCB()`, `HieuLuc()`, `Them()`, `LayTai()`...), không bao giờ đụng trực tiếp field. Trạng thái "đang hiệu lực" được giấu sau `HieuLuc()` |
| **Abstraction** (trừu tượng) | Lớp nền `ThucThe` định nghĩa **bộ hành vi chung**: 3 pure virtual buộc con hiện thực (`nhap`, `ghiDong`, `docDong`) + `xuat()` **có thân mặc định** gọi `loaiThucThe()` (nạp nhãn loại); tầng nghiệp vụ `NghiepVu` phơi ra API nghiệp vụ (`tongThuNhap()`, `demCanBoNu()`, `dangNhap()`...) — người gọi (main) không cần biết chi tiết lưu trữ |
| **Inheritance** (kế thừa) | 8 model kế thừa `: public ThucThe` và `override` các hành vi. Đặc biệt mỗi `xuat()` của lớp con **gọi lại `ThucThe::xuat()`** ở đầu thân hàm → tái sử dụng mã của cha (dòng nhãn `----- CAN_BO -----`) rồi in thêm phần riêng. `Account` ánh xạ `nhap()/xuat()` sang `input()/display()` riêng của nó |
| **Polymorphism** (đa hình) | Gọi `xuat()` qua con trỏ `ThucThe*` sẽ dispatch đúng bản của từng loại thực thể (xem §8.6); **đa hình xảy ra ngay trong thân `ThucThe::xuat()`**: nó gọi `loaiThucThe()` (pure virtual) → compiler gọi đúng bản `CAN_BO`, `PHONG_BAN`, … Ngoài ra có **nạp chồng toán tử** (`PhanCong::operator==`, `Vector::operator[]`) |

- **Association**: các class liên kết qua khóa (mã ID) — `CanBo` ↔ `PhanCong`, `PhanCong` ↔ `PhongBan`, `PhanCong` ↔ `ChucVu` (KHÔNG nhúng giá trị đối tượng).
- **Aggregation**: `PhongBan` chứa nhiều `CanBo` thông qua `PhanCong`; mỗi class entity **tự quản danh sách tĩnh mảng động** của chính nó (`static T* ds; static int soLuong; static int sucChua;` + `Them/XoaMot/LayTai/SoLuong/DocTatCa/GhiTatCa`) bằng `new[]/delete[]` + **nhân đôi khi đầy** → thể hiện rõ encapsulation + phân tích độ phức tạp. Mô-đun `Vector` (mảng `int` động, rule of three) giữ nguyên làm ví dụ minh họa.
- **VaiTro thay cho kế thừa hành vi**: `Account` dùng cột `VaiTro` để phân quyền (Admin/User khác nhau chủ yếu ở quyền) — KHÔNG tạo 2 class kế thừa; kế thừa trong đồ án nằm ở chỗ 8 model dùng chung `ThucThe`.

> **Phân biệt**:
> - **DATABASE ENTITY** = 8 bảng ở trên.
> - **C++ CLASS** = 8 class model (kế thừa `ThucThe`) + `Vector` (cấu trúc dữ liệu tự viết) + tầng nghiệp vụ `NghiepVu` (phục vụ triển khai).
> - Thuộc tính (`TrinhDo`...) ≠ bảng ≠ data structure (`Vector`).

### 8.2 Quy tắc triển khai đã chốt

- **Mã khóa tự sinh** (hàm `NghiepVu::sinhMaTuDong(loai)`: quét hậu tố lớn nhất của danh sách tương ứng rồi + 1, đệm `0` cho đủ độ dài) — người dùng không nhập mã → đảm bảo PK unique: `CB001…`, `P01…`, `CV01…`, `PC001…`, `ML001…`, `DG001…`, `SK001…`, `TK001…`. Kèm các hàm tiện ích **private `timXTheoMa(...)`** (8 bảng) tìm chỉ số bản ghi theo mã (linear search, xem §9.1), dùng nội bộ cho xóa theo mã + kiểm tra khóa ngoại.
- **Tìm kiếm cán bộ theo TÊN**: `NghiepVu::timKiemCanBoTheoTen()` — không phân biệt hoa/thường, khớp chuỗi con, in ra **nhiều** kết quả.
- **`PHAN_CONG` nhập tay đầy đủ**: người dùng chọn `MaCanBo`, `MaPhong`, `MaChucVu` từ danh sách hiện có và nhập `TuNgay`, `DenNgay` (để trống = hiệu lực), `LoaiPhanCong`, `LaPhongChinh` (0/1). `NghiepVu` vẫn kiểm tra ràng buộc C2/C3.
- **Giới tính**: chỉ nhận `Nam` hoặc `Nu` (`CanBo::nhap()` validate, nhập khác → hỏi lại).
- **Chu kỳ nâng lương cố định `CHU_KY_NANG_LUONG = 3`** (năm) — áp dụng trong `NghiepVu::lietKeDenHanTangLuong()`.
- **Đăng nhập**: 1 class `Account` (`VaiTro = ADMIN/USER`), mật khẩu lưu rõ ràng (demo), đăng nhập qua `NghiepVu::dangNhap()`. **Tài khoản mặc định demo**: `admin / admin` (ADMIN) và `user / user` (USER).
- **Gộp nghiệp vụ 1 module `NghiepVu`**: toàn bộ 10 chức năng + đăng nhập + `sinhMaTuDong`/`timXTheoMa`/`timKiemCanBoTheoTen`/`dateThanhSo`/`giaoNhau` là **hàm tĩnh** của 1 class `NghiepVu` (không cần tách 5 service vì mọi danh sách đã là `static` trong từng model).

### 8.3 Cấu trúc thư mục (1 mô-đun = 1 cặp `.h` + `.cpp`, phẳng tại thư mục gốc)

```
QL_CANBO/
├── README.md                            ← báo cáo + ERD (file này)
│
│   ── 8 MÔ-ĐUN MODEL (.h + .cpp) ── mỗi class tự quản danh sách tĩnh mảng động
├── ThucThe.h                         ← lớp nền trừu tượng (4 hành vi chung) — 8 model kế thừa
├── CanBo.h           / CanBo.cpp     ← CAN_BO
├── PhongBan.h        / PhongBan.cpp  ← PHONG_BAN
├── ChucVu.h          / ChucVu.cpp    ← CHUC_VU
├── PhanCong.h        / PhanCong.cpp  ← PHAN_CONG
├── Luong.h           / Luong.cpp     ← LICH_SU_LUONG
├── DanhGia.h         / DanhGia.cpp   ← DANH_GIA
├── ThiDua.h          / ThiDua.cpp    ← KHEN_THUONG_KY_LUAT
├── Account.h         / Account.cpp   ← TAI_KHOAN (ADMIN + USER gộp, VaiTro)
│
│   ── 1 MÔ-ĐUN CẤU TRÚC DỮ LIỆU (.h + .cpp) ──
├── Vector.h          / Vector.cpp        ← mảng int động tự viết (minh họa new[]/delete[])
│
│   ── 1 MÔ-ĐUN NGHIỆP VỤ (.h + .cpp) ── toàn bộ 10 chức năng + đăng nhập
├── NghiepVu.h          / NghiepVu.cpp      ← hồ sơ/phòng/chức vụ/phân công/lương/đánh giá/khen thưởng + báo cáo + tài khoản
│
├── data/                                 ← 8 file dữ liệu .txt (mục 10)
└── main.cpp                              ← đăng nhập → menu ADMIN / USER
```

### 8.4 Menu dự kiến

```
============================================
      HỆ THỐNG QUẢN LÝ CÁN BỘ
============================================
Đăng nhập bằng tài khoản (qua NghiepVu)
   -> ADMIN: toàn quyền / USER: xem thông tin
============================================

------------ MENU ADMIN ------------
1. Quản lý cán bộ (thêm, xem, xóa, sửa)
2. Quản lý phòng ban
3. Quản lý chức vụ
4. Phân công phòng ban & chức vụ
5. Quản lý lương (lịch sử lương)
6. Đánh giá cán bộ
7. Khen thưởng / Kỷ luật
8. Tìm kiếm
9. Sắp xếp
10. Thống kê / Báo cáo
11. Quản lý tài khoản
0. Đăng xuất / Thoát

------------ MENU USER -------------
1. Xem thông tin cá nhân
2. Xem lương của bản thân
3. Xem đánh giá của bản thân
4. Xem phân công / phòng ban của bản thân
5. Tìm kiếm cán bộ
6. Xem danh sách phòng ban
0. Đăng xuất
```

### 8.5 Cách biên dịch

```bash
g++ *.cpp -o QLCB.exe
```

### 8.6 Liên kết giữa các thực thể & phép join runtime
Quan hệ giữa các thực thể (ERD, mục 4) được thể hiện trong code bằng **khóa (mã ID)**: bảng con giữ cột FK, và **`NghiepVu` thực hiện phép "join" bằng cách quét danh sách, so khóa (FK == PK) khi chạy** — không nhúng con trỏ/reference giữa các model.

| Quan hệ (ERD mục 4) | Khóa liên kết | Nơi thực hiện join |
|---|---|---|
| `CAN_BO` 1 : N `PHAN_CONG` | `PHAN_CONG.MaCanBo` == `CAN_BO.MaCanBo` | `NghiepVu` — quản lý hồ sơ/phân công |
| `PHONG_BAN` 1 : N `PHAN_CONG` | `PHAN_CONG.MaPhong` == `PHONG_BAN.MaPhong` | `NghiepVu` — quản lý hồ sơ/phân công |
| `CHUC_VU` 1 : N `PHAN_CONG` | `PHAN_CONG.MaChucVu` == `CHUC_VU.MaChucVu` | `NghiepVu` — quản lý hồ sơ/phân công |
| `CAN_BO` 1 : N `LICH_SU_LUONG` | `LICH_SU_LUONG.MaCanBo` == `CAN_BO.MaCanBo` | `NghiepVu` — quản lý lương |
| `CAN_BO` 1 : N `DANH_GIA` | `DANH_GIA.MaCanBo` == `CAN_BO.MaCanBo` | `NghiepVu` — quản lý đánh giá |
| `CAN_BO` 1 : N `KHEN_THUONG_KY_LUAT` | `KHEN_THUONG_KY_LUAT.MaCanBo` == `CAN_BO.MaCanBo` | `NghiepVu` — quản lý đánh giá |
| `CAN_BO` 1 : 0..1 `TAI_KHOAN` | `TAI_KHOAN.MaCanBo` == `CAN_BO.MaCanBo` (NULL) | `NghiepVu` — đăng nhập |

Ví dụ join 2 bảng (chức năng 5 — tổng thu nhập): duyệt `CAN_BO`, với mỗi mã CB quét `LICH_SU_LUONG`, chọn bản `HieuLuc()`, lấy `tinhThucLinh()` và cộng dồn — chi tiết ở §9.2.

**Đa hình khi hiển thị** — vì 8 model kế thừa `ThucThe`, một hàm duy nhất in được mọi loại thực thể:

```cpp
void xuatTatCa(ThucThe* ds[], int n) {
    for (int i = 0; i < n; i++) ds[i]->xuat(); // dispatch đúng xuat() của từng loại;
                                               // mỗi xuat() con gọi ThucThe::xuat() → in nhãn loại
}
```

> Liên kết dữ liệu là **logic so khóa lúc chạy** (không phải con trỏ nhúng) — phản ánh đúng quan hệ ERD 1:N ở mục 4 và tránh phụ thuộc vòng giữa các model.

---

## 9. CẤU TRÚC DỮ LIỆU & THUẬT TOÁN (BIG-O)

### 9.1 Cấu trúc dữ liệu
- Mỗi class entity **tự quản danh sách tĩnh mảng động** của chính nó (`static T* ds; static int soLuong; static int sucChua;`), viết tay bằng `new[]/delete[]` — **không dùng `std::vector`**.
- API của mỗi danh sách: `Them` (= push_back), `XoaMot(idx)` (= erase), `LayTai(idx)` (= operator[]), `SoLuong()` (= size), `DocTatCa()/GhiTatCa()` (load/save file).
- Cấp phát **nhân đôi** khi đầy → `Them` **O(1) amortized**; `XoaMot` **O(n)** do phải dịch chuyển các phần tử phía sau.
- Mô-đun `Vector` (mảng `int` động, rule of three, `operator[]` ném `out_of_range`) giữ nguyên như ví dụ minh họa cơ chế mảng động; danh sách thực tế do từng class quản lý.
- `DocTatCa()` reset danh sách trước khi load → gọi nhiều lần không nhân đôi dữ liệu.
- Tìm kiếm mặc định: **Linear Search** (O(n)). (Tùy chọn nâng cao) `std::unordered_map<string, size_t>` index theo mã → tìm trung bình **O(1)**, trade-off: tốn bộ nhớ, phải đồng bộ khi thêm/xóa.

### 9.2 Ánh xạ 10 chức năng đề bài → Thuật toán

| Đề bài | Cấu trúc / Thuật toán | Độ phức tạp |
|---|---|---|
| 1 & 10. Nhập / Thêm cán bộ | mảng động tự viết: `Them()` (nhân đôi khi đầy) | **O(1)** (amortized) |
| 2. Hiển thị danh sách | duyệt bằng `LayTai(idx)` | **O(n)** |
| 3. Liệt kê đến hạn nâng lương | duyệt `Luong` bản hiệu lực + so chu kỳ 3 năm | **O(n)** |
| 4. Đếm cán bộ nữ | vòng lặp so `GioiTinh == "Nu"` | **O(n)** |
| 5. Tổng thu nhập | vòng lặp cộng dồn + `tinhThucLinh()` | **O(n)** |
| 6. Lọc chuyên môn CNTT | duyệt + so `ChuyenMon` | **O(n)** |
| 7. Cán bộ xếp loại "Giỏi" | duyệt `DANH_GIA` lấy bản mới nhất + lọc | **O(n)** |
| 8. Sắp xếp theo mã cán bộ | thuật toán sắp xếp tự viết trên mảng (QuickSort/MergeSort) | **O(n log n)** |
| 9. Xóa theo mã cán bộ | Linear search + `XoaMot(idx)` / xóa mềm | **O(n)** |

> **Đăng nhập**: tìm `Account` theo `TenDangNhap` bằng Linear Search → **O(n)**.

### 9.3 Giải thích ngắn
- **O(1)** thêm cuối: `Vector` cấp phát thêm bộ nhớ theo cấp số nhân → phí amortized là hằng số.
- **O(n)** duyệt/thống kê/lọc: phải xét từng phần tử một lần.
- **O(n log n)** sắp xếp: `std::sort` chia để trị, tốt nhất cho dữ liệu ngẫu nhiên; trade-off với phương án thủ công (Bubble Sort O(n²) — KHÔNG dùng, chỉ nêu để so sánh).

---

## 10. LƯU TRỮ DỮ LIỆU (FILE TEXT)

- Mỗi entity một file, mỗi dòng = 1 bản ghi, các cột ngăn bởi **`|`**:

| File | Nội dung |
|---|---|
| `data/canbo.txt` | CAN_BO (class `CanBo`) |
| `data/phongban.txt` | PHONG_BAN (class `PhongBan`) |
| `data/chucvu.txt` | CHUC_VU (class `ChucVu`) |
| `data/phancong.txt` | PHAN_CONG (class `PhanCong`) |
| `data/luong.txt` | LICH_SU_LUONG (class `Luong`) |
| `data/danhgia.txt` | DANH_GIA (class `DanhGia`) |
| `data/thidua.txt` | KHEN_THUONG_KY_LUAT (class `ThiDua`) |
| `data/account.txt` | TAI_KHOAN (class `Account`) |

- Mỗi class gọi `DocTatCa()` khi khởi động và `GhiTatCa()` sau mỗi thao tác ghi (qua `NghiepVu`).
- Giá trị `DenNgay` rỗng (không có) được hiểu là **đang hiệu lực**.
- Việc ghi/đọc lặp từng phần tử của danh sách tĩnh (`GhiTatCa`/`DocTatCa`).

---

## 11. KẾ HOẠCH TRIỂN KHAI

| Bước | Công việc | Trạng thái |
|---|---|---|
| 1 | Chốt phạm vi nghiệp vụ | ✅ Đã chốt (8 bảng) |
| 2 | Chốt ERD | ✅ Bảng này |
| 3 | PK/FK/Cardinality/Constraint | ✅ Bảng này |
| 4 | ERD → Class Diagram | ✅ Mục 8 |
| 5 | Xác định attribute + method | ✅ Đã chốt (8 model + `Vector`) |
| 6 | Xác định cấu trúc dữ liệu | ✅ `Vector` tự viết |
| 7 | Xác định thuật toán + Big-O | ✅ Mục 9 |
| 8 | Thiết kế lưu trữ file | ✅ Mục 10 |
| 9 | Code model/class | ✅ 8 model xong (mỗi class tự quản danh sách + file I/O) |
| 10 | Code `Vector` mảng động | ✅ `Vector` int-array (guard + ném `out_of_range`) |
| 11 | Code lớp nền `ThucThe` + hàm tiện ích (sinh mã, tìm kiếm) | ✅ `ThucThe` xong (8 model kế thừa + override); hàm sinh mã/tìm kiếm nằm trong `NghiepVu` (B12, §8.2) |
| 12 | Code nghiệp vụ (`NghiepVu` — gộp 1 module) | ✅ Xong: `khoiTao` + `dangNhap` + `sinhMaTuDong` + 10 chức năng + tìm kiếm theo tên + quản lý 7 nhóm tài nguyên + `thongKeBaoCao` |
| 13 | Code search/sort/statistics | ⏳ |
| 14 | UI/menu + đăng nhập | ⏳ |
| 15 | Kiểm thử (bao gồm đa hình qua `ThucThe*`) & báo cáo | ⏳ |

---

*Tài liệu này là nguồn tri thức chính thức của dự án. Mọi thiết kế (ERD, Class Diagram, code, báo cáo) phải nhất quán với mô hình 8 bảng được mô tả ở trên.*
