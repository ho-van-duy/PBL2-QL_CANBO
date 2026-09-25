# PBL2 — CHƯƠNG TRÌNH QUẢN LÝ CÁN BỘ

> **Đề tài 21**: "Viết chương trình quản lý cán bộ theo hướng đối tượng."
> **Môn học**: PBL2 (Project-Based Learning 2) · **Ngành**: CNTT
> **Kiến trúc chính thức**: **8 bảng** (7 nghiệp vụ + `TAI_KHOAN` đăng nhập)

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
| 7 | Hiển thị cán bộ xếp loại lao động "Giỏi" | Lọc theo bản đánh giá mới nhất |
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
- **C4** `UNIQUE(MaCanBo, NamDanhGia)` — một cán bộ chỉ có 1 bản đánh giá trong một năm.
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
                       1 → N       │ NamDanhGia       │
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

### 5.5 LICH_SU_LUONG — Lịch sử lương

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
| `NamDanhGia` | INT | C4 | Năm đánh giá |
| `XepLoai` | VARCHAR | C6 | "Gioi", "Kha", "TrungBinh", "Yeu" |
| `NhanXet` | VARCHAR | — | Nhận xét |
| `NgayDanhGia` | DATE | — | Ngày đánh giá |

### 5.7 KHEN_THUONG_KY_LUAT — Khen thưởng & Kỷ luật (gộp)

| Cột | Kiểu | Ràng buộc | Mô tả |
|---|---|---|---|
| `MaSuKien` | VARCHAR | **PK** | Mã sự kiện |
| `MaCanBo` | VARCHAR | **FK → CAN_BO** | Cán bộ |
| `LoaiSuKien` | VARCHAR | C6 | "KHEN_THUONG" hoặc "KY_LUAT" |
| `NoiDung` | VARCHAR | — | Nội dung / hình thức |
| `Nam` | INT | — | Năm sự kiện |
| `LyDo` | VARCHAR | — | Lý do |

> `KHEN_THUONG_KY_LUAT` KHÔNG phải thuộc tính string đơn giản của `CAN_BO` — quan hệ `CAN_BO 1:N KHEN_THUONG_KY_LUAT` cho phép nhiều bản ghi/cán bộ.

### 5.8 TAI_KHOAN — Tài khoản đăng nhập (ADMIN + USER gộp chung)

| Cột | Kiểu | Ràng buộc | Mô tả |
|---|---|---|---|
| `MaTaiKhoan` | VARCHAR | **PK** | Mã tài khoản, ví dụ "TK001" |
| `TenDangNhap` | VARCHAR | **UNIQUE** (C8) | Tên đăng nhập |
| `MatKhau` | VARCHAR | NOT NULL | Mật khẩu (demo lưu rõ ràng) |
| `VaiTro` | VARCHAR | C6 | "ADMIN" hoặc "USER" |
| `TrangThai` | BOOLEAN | — | `true` = hoạt động; `false` = bị khóa |
| `MaCanBo` | VARCHAR | **FK → CAN_BO**, NULL | Cán bộ tương ứng (USER); ADMIN để trống |

> **Cách tiếp cận**: MỘT class `TaiKhoan` có cột `VaiTro` phân biệt Admin/User (KHÔNG dùng inheritance như một số bản tham khảo). Admin/User khác nhau chủ yếu ở **quyền**, nên `VaiTro` là đủ cho PBL2.

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
| Ăn trưa | `LICH_SU_LUONG.AnTrua` |
| **Thực lĩnh** | **Tính toán** `= (HSL + PC) * 1.490.000 + AnTrua` |
| Năm tăng lương | `LICH_SU_LUONG.TuNgay` (lần tăng gần nhất) |
| Xếp loại lao động | `DANH_GIA.XepLoai` (bản mới nhất) |

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
    NamDanhGia   INT,
    XepLoai      VARCHAR(20) CHECK (XepLoai IN ('Gioi','Kha','TrungBinh','Yeu')),
    NhanXet      VARCHAR(200),
    NgayDanhGia  DATE,
    UNIQUE (MaCanBo, NamDanhGia)
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

### 8.1 Nguyên tắc OOP

- **Encapsulation**: mỗi thực thể là một class với thuộc tính `private`, truy cập qua getter/setter.
- **Association**: các class liên kết qua khóa (mã ID) — `CanBo` ↔ `PhanCong`, `PhanCong` ↔ `PhongBan`, `PhanCong` ↔ `ChucVu` (KHÔNG nhúng giá trị đối tượng như bản phase 1).
- **Aggregation**: `PhongBan` chứa nhiều `CanBo` thông qua `PhanCong`; `KhoDuLieu` (kho dữ liệu) chứa toàn bộ `Vector` của 8 entity.
- **Generic Programming**: **`Vector<T>` tự viết** (mảng động dạng template) — hiện thực quản lý bộ nhớ động `new[]/delete[]`, thể hiện rõ encapsulation + phân tích độ phức tạp.
- **Không ép Inheritance**: chưa có lý do nghiệp vụ thực sự; `TaiKhoan` dùng `VaiTro` để phân quyền (Admin/User khác nhau chủ yếu ở quyền) thay vì tạo 2 class kế thừa.

> **Phân biệt**:
> - **DATABASE ENTITY** = 8 bảng ở trên.
> - **C++ CLASS** = 8 class model + `Vector<T>` (cấu trúc dữ liệu tự viết) + `KhoDuLieu` + 5 service (class phụ phục vụ triển khai).
> - Thuộc tính (`TrinhDo`...) ≠ bảng ≠ data structure (`Vector<T>`).

### 8.2 Quy tắc triển khai đã chốt

- **Mã khóa tự sinh** bởi `KhoDuLieu::sinhMaTuDong(prefix, list)` — người dùng không nhập mã → đảm bảo PK unique: `CB001…`, `P01…`, `CV01…`, `PC001…`, `ML001…`, `DG001…`, `SK001…`, `TK001…`.
- **`PHAN_CONG` nhập tay đầy đủ**: người dùng chọn `MaCanBo`, `MaPhong`, `MaChucVu` từ danh sách hiện có và nhập `TuNgay`, `DenNgay` (để trống = hiệu lực), `LoaiPhanCong`, `LaPhongChinh` (0/1). Service vẫn kiểm tra ràng buộc C2/C3.
- **Giới tính**: chỉ nhận `Nam` hoặc `Nu` (`CanBo::nhap()` validate, nhập khác → hỏi lại).
- **Chu kỳ nâng lương cố định `CHU_KY_NANG_LUONG = 3`** (năm) — áp dụng trong `LuongService::lietKeDenHanTangLuong()`.
- **Đăng nhập**: 1 class `TaiKhoan` (`VaiTro = ADMIN/USER`), mật khẩu lưu rõ ràng (demo), đăng nhập qua `TaiKhoanService`. **Tài khoản mặc định demo**: `admin / admin` (ADMIN) và `user / user` (USER).

### 8.3 Cấu trúc thư mục (1 mô-đun = 1 cặp `.h` + `.cpp`, phẳng tại thư mục gốc)

```
QL_CANBO/
├── README.md                            ← báo cáo + ERD (file này)
│
│   ── 7 MÔ-ĐUN MODEL NGHIỆP VỤ (.h + .cpp) ──
├── CanBo.h           / CanBo.cpp
├── PhongBan.h        / PhongBan.cpp
├── ChucVu.h          / ChucVu.cpp
├── PhanCong.h        / PhanCong.cpp
├── LichSuLuong.h     / LichSuLuong.cpp
├── DanhGia.h         / DanhGia.cpp
├── KhenThuongKyLuat.h / KhenThuongKyLuat.cpp
│
│   ── 1 MÔ-ĐUN MODEL ĐĂNG NHẬP (.h + .cpp) ──
├── TaiKhoan.h        / TaiKhoan.cpp     ← ADMIN + USER gộp (VaiTro)
│
│   ── 1 MÔ-ĐUN CẤU TRÚC LƯU TRỮ (.h + .cpp) ──
├── Vector.h          / Vector.cpp       ← mảng động tự viết (template + explicit instantiation)
│
│   ── 1 MÔ-ĐUN KHO DỮ LIỆU (.h + .cpp) ──
├── KhoDuLieu.h       / KhoDuLieu.cpp    ← 8 Vector + load/save file
│
│   ── 5 MÔ-ĐUN NGHIỆP VỤ (.h + .cpp) ──
├── CanBoService.h    / CanBoService.cpp   ← hồ sơ CB + phòng + chức vụ + phân công
├── LuongService.h    / LuongService.cpp   ← lịch sử lương + thực lĩnh + nâng lương
├── DanhGiaService.h  / DanhGiaService.cpp ← đánh giá + khen thưởng/kỷ luật
├── BaoCaoService.h   / BaoCaoService.cpp  ← tìm kiếm + sắp xếp + thống kê + hiển thị
├── TaiKhoanService.h / TaiKhoanService.cpp ← đăng nhập, đổi mật khẩu, phân quyền menu
│
├── data/                                 ← 8 file dữ liệu .txt (mục 10)
└── main.cpp                              ← đăng nhập → menu ADMIN / USER
```

### 8.4 Menu dự kiến

```
============================================
      HỆ THỐNG QUẢN LÝ CÁN BỘ
============================================
Đăng nhập bằng tài khoản (TaiKhoanService)
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

---

## 9. CẤU TRÚC DỮ LIỆU & THUẬT TOÁN (BIG-O)

### 9.1 Cấu trúc dữ liệu
- Mỗi entity quản lý bằng **`Vector<T>` tự viết** (mảng động, không dùng `std::vector`) — hiểu tường tận cơ chế mảng động.
- API đủ dùng: `push_back`, `operator[]`, `erase`, `size`, `capacity`, `empty`, `clear`, `pop_back`, copy constructor, `operator=`, destructor, `begin()/end()`.
- Cấp phát **nhân đôi** khi đầy → `push_back` **O(1) amortized**; `erase` **O(n)** do phải dịch chuyển các phần tử phía sau.
- `Vector.cpp` chứa **explicit instantiation** cho 8 kiểu (`CanBo`, `PhongBan`, `ChucVu`, `PhanCong`, `LichSuLuong`, `DanhGia`, `KhenThuongKyLuat`, `TaiKhoan`).
- Tìm kiếm mặc định: **Linear Search** (O(n)). (Tùy chọn nâng cao) `std::unordered_map<string, size_t>` index theo mã → tìm trung bình **O(1)**, trade-off: tốn bộ nhớ, phải đồng bộ khi thêm/xóa.

### 9.2 Ánh xạ 10 chức năng đề bài → Thuật toán

| Đề bài | Cấu trúc / Thuật toán | Độ phức tạp |
|---|---|---|
| 1 & 10. Nhập / Thêm cán bộ | `Vector::push_back` | **O(1)** (amortized) |
| 2. Hiển thị danh sách | duyệt bằng `operator[]` | **O(n)** |
| 3. Liệt kê đến hạn nâng lương | duyệt `LICH_SU_LUONG` bản hiệu lực + so chu kỳ 3 năm | **O(n)** |
| 4. Đếm cán bộ nữ | vòng lặp so `GioiTinh == "Nu"` | **O(n)** |
| 5. Tổng thu nhập | vòng lặp cộng dồn + `tinhThucLinh()` | **O(n)** |
| 6. Lọc chuyên môn CNTT | duyệt + so `ChuyenMon` | **O(n)** |
| 7. Cán bộ xếp loại "Giỏi" | duyệt `DANH_GIA` lấy bản mới nhất + lọc | **O(n)** |
| 8. Sắp xếp theo mã cán bộ | `std::sort` (qua `Vector::begin()/end()`) | **O(n log n)** |
| 9. Xóa theo mã cán bộ | Linear search + `Vector::erase` / xóa mềm | **O(n)** |

> **Đăng nhập**: tìm `TaiKhoan` theo `TenDangNhap` bằng Linear Search → **O(n)**.

### 9.3 Giải thích ngắn
- **O(1)** thêm cuối: `Vector` cấp phát thêm bộ nhớ theo cấp số nhân → phí amortized là hằng số.
- **O(n)** duyệt/thống kê/lọc: phải xét từng phần tử một lần.
- **O(n log n)** sắp xếp: `std::sort` chia để trị, tốt nhất cho dữ liệu ngẫu nhiên; trade-off với phương án thủ công (Bubble Sort O(n²) — KHÔNG dùng, chỉ nêu để so sánh).

---

## 10. LƯU TRỮ DỮ LIỆU (FILE TEXT)

- Mỗi entity một file, mỗi dòng = 1 bản ghi, các cột ngăn bởi **`|`**:

| File | Nội dung |
|---|---|
| `data/canbo.txt` | CAN_BO |
| `data/phongban.txt` | PHONG_BAN |
| `data/chucvu.txt` | CHUC_VU |
| `data/phancong.txt` | PHAN_CONG |
| `data/lichsuluong.txt` | LICH_SU_LUONG |
| `data/danhgia.txt` | DANH_GIA |
| `data/khenthuongkyluat.txt` | KHEN_THUONG_KY_LUAT |
| `data/taikhoan.txt` | TAI_KHOAN |

- `KhoDuLieu` chịu trách nhiệm `loadAll()` khi khởi động và `saveAll()` sau mỗi thao tác ghi.
- Giá trị `DenNgay` rỗng (không có) được hiểu là **đang hiệu lực**.
- Ứng với `Vector<T>` tự viết, việc ghi/đọc lặp từng phần tử của `Vector`.

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
| 9 | Code model/class | 🔄 7 model xong; chờ `Vector`, `TaiKhoan` |
| 10 | Code `Vector<T>` | ⏳ |
| 11 | Code `KhoDuLieu` + load/save | ⏳ |
| 12 | Code nghiệp vụ (5 service) | ⏳ |
| 13 | Code search/sort/statistics | ⏳ |
| 14 | UI/menu + đăng nhập | ⏳ |
| 15 | Kiểm thử & báo cáo | ⏳ |

---

*Tài liệu này là nguồn tri thức chính thức của dự án. Mọi thiết kế (ERD, Class Diagram, code, báo cáo) phải nhất quán với mô hình 8 bảng được mô tả ở trên.*