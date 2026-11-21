# PBL2: Hệ thống quản lý cán bộ (Đề tài 21)

Đồ án cơ sở lập trình – ngôn ngữ C++, phương pháp hướng đối tượng. Gồm hai phiên bản:

- **Console**: menu 10 chức năng nghiệp vụ, tương tác qua dòng lệnh.
- **GUI**: giao diện đồ họa dùng ImGui + GLFW (`src/imgui_main.cpp`).

## Cấu trúc thư mục

| Thư mục / tệp | Nội dung |
| --- | --- |
| `src/` | Mã nguồn C++ (`Nguoi`, `CanBo`, `DList`, `QuanLyCanBo`, `main`, `imgui_main`) |
| `data/canbo.txt` | Dữ liệu mẫu, mỗi dòng một cán bộ, 12 trường ngăn cách bằng `;` |
| `lib/` | Thư viện ImGui và GLFW dùng cho phiên bản GUI |
| `bin/` | Tệp thực thi sau khi biên dịch: `qlcb.exe`, `qlcb_gui.exe` |
| `build.bat` | Tập lệnh biên dịch cả hai phiên bản bằng MinGW-w64 (g++) |
| `Bao_Cao/BaocaoPbl2.docx` | Báo cáo đồ án (bản cuối) |

## Biên dịch

Yêu cầu: MinGW-w64 (GCC >= 8), `g++` có trong `PATH` hoặc chỉnh biến `CXX` trong `build.bat`.

```bat
build.bat
```

Kết quả: `bin\qlcb.exe` và `bin\qlcb_gui.exe`.

## Chạy chương trình

```bat
bin\qlcb.exe        :: phiên bản console
bin\qlcb_gui.exe    :: phiên bản giao diện đồ họa
```

Hàm `duongDanDuLieu()` tự tìm `data/canbo.txt` khi chạy từ thư mục gốc hoặc từ `bin/`. Chọn `0` trong menu console để thoát và tự động lưu dữ liệu.

## Chức năng chính

1. Tạo và nhập danh sách cán bộ (kiểm tra mã trùng)
2. Hiển thị danh sách dạng bảng (12 thuộc tính + thực lĩnh)
3. Liệt kê cán bộ đến thời điểm nâng lương
4. Đếm cán bộ nữ
5. Tổng thu nhập + sắp xếp thực lĩnh giảm dần
6. Liệt kê cán bộ chuyên môn Công nghệ thông tin
7. Liệt kê cán bộ xếp loại lao động Giỏi
8. Sắp xếp danh sách theo mã cán bộ
9. Loại bỏ cán bộ theo mã
10. Thêm một cán bộ mới

Công thức tính thực lĩnh: `(Hệ số lương + Phụ cấp trách nhiệm) × 1.490.000 + Ăn trưa`.
