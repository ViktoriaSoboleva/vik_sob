@echo off
echo Сборка и запуск программ


echo 1. Bubble Sort:
cd Source\bubble_sort
g++ bubble_sort.cpp -o bubble_sort.exe
bubble_sort.exe
cd ..\..


echo 2. Learn Soft:
cd Source\learn_soft
g++ menu_functions.cpp menu_items.cpp -o learn_soft.exe
learn_soft.exe
cd ..\..


pause