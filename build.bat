@echo off
setlocal
cd /d "%~dp0"

rem Can MinGW-w64 (GCC >= 8). Neu g++ trong PATH la MinGW.org cu (khong bien dich duoc ImGui),
rem duong dan duoi day se duoc uu tien. Co the sua bien CXX cho may cua ban.
set "CXX=g++"
if exist "F:\VibeCoding\Game\Monster_Survival\tools\winlibs\mingw32\bin\g++.exe" set "CXX=F:\VibeCoding\Game\Monster_Survival\tools\winlibs\mingw32\bin\g++.exe"

echo [1/2] Dang bien dich qlcb.exe ...
"%CXX%" -std=c++11 -O2 -static -I src ^
  src/main.cpp src/Nguoi.cpp src/CanBo.cpp src/QuanLyCanBo.cpp ^
  -o bin\qlcb.exe
if errorlevel 1 goto :fail

echo [2/2] Dang bien dich qlcb_gui.exe ...
"%CXX%" -std=c++11 -O2 -static -I src -I lib\imgui -I lib\imgui\backends -I lib\glfw\include ^
  src/imgui_main.cpp src/Nguoi.cpp src/CanBo.cpp src/QuanLyCanBo.cpp ^
  lib\imgui\imgui.cpp lib\imgui\imgui_draw.cpp lib\imgui\imgui_tables.cpp lib\imgui\imgui_widgets.cpp ^
  lib\imgui\backends\imgui_impl_glfw.cpp lib\imgui\backends\imgui_impl_opengl3.cpp ^
  -L lib\glfw\lib -lglfw3 -lopengl32 -lgdi32 ^
  -o bin\qlcb_gui.exe
if errorlevel 1 goto :fail

echo Hoan tat. File thuc thi nam trong thu muc bin\.
exit /b 0

:fail
echo Bien dich that bai. Hay kiem tra lai duong dan CXX / PATH.
exit /b 1
