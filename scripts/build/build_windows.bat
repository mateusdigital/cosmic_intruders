@echo off
echo "-- build_windows.bat --";
REM ----------------------------------------------------------------------------
REM -- Variables
set "original_cwd=%cd%";
set "build_path=..\build\windows";
set "cmake_generator_type=NMake Makefiles";

REM echo %original_cwd%
REM echo %build_path%
REM echo %cmake_generator_type%

REM ----------------------------------------------------------------------------
REM -- Source the visual studio shit to make the cmake find the compiler.
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\Tools\VsDevCmd.bat"
REM -- The VsDevCmd.bat change the cwd.
cd "%original_cwd%"

REM ----------------------------------------------------------------------------
REM -- Create the build directory.
mkdir %build_path%

cd %build_path%
cmake ../../ -G "%cmake_generator_type%"
cmake --build .