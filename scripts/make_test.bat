@echo off

if "%1"=="" (
    echo 테스트 이름을 입력하세요
    exit /b 1
)

cd %~dp0

set TEST_NAME=%1
set TEST_DIR=..\test\%TEST_NAME%
set TEMPLATE_DIR=..\test\template

echo %TEST_NAME%
echo %TEST_DIR%
echo %TEMPLATE_DIR%

if not exist %TEST_DIR% (
    mkdir %TEST_DIR%
)

copy %TEMPLATE_DIR%\CMakeLists.txt %TEST_DIR%\CMakeLists.txt
copy %TEMPLATE_DIR%\main.cpp %TEST_DIR%\main.cpp

echo %TEST_NAME% 테스트 프로젝트가 생성되었습니다.

powershell -Command "(Get-Content %TEST_DIR%\CMakeLists.txt) | ForEach-Object { $_ -replace '_template_', '%TEST_NAME%' } | Set-Content %TEST_DIR%\CMakeLists.txt"
powershell -Command "(Get-Content %TEST_DIR%\main.cpp) | ForEach-Object { $_ -replace '_template_', '%TEST_NAME%' } | Set-Content %TEST_DIR%\main.cpp"

powershell -Command "Add-Content ..\test\CMakeLists.txt 'add_subdirectory(%TEST_NAME%)'"
