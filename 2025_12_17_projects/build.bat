@echo off

set BUILD_TUPE=Ninja
set BUILD_SUFFIX=ninja

chcp 65001

set BUILD_FOLDER=build_%BUILD_SUFFIX%
set SOURCE_FOLDER=Source

if not exist %BUILD_FOLDER% mkdir %BUILD_FOLDER%

cd %BUILD_FOLDER%

cmake -G %BUILD_TUPE% ..\%SOURCE_FOLDER%
cmake --build .

copy ..\%SOURCE_FOLDER%\bubble_sort\build_sort.bat .\bubble_sort
copy ..\%SOURCE_FOLDER%\learn_soft\build_soft.bat .\learn_soft

copy ..\run_tests.bat







