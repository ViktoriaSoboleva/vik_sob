#include <iostream>
#include "inversion_counter.hpp"
#include "array_utils.hpp"

int main()
{
    int size;
    
    std::cout << "Введите размер массива: ";
    std::cin >> size;
    
    int* arr = new int[size];
    int* temp = new int[size];
    
    svr::generateRandomArray(arr, size);
    
    std::cout << "Сгенерированный массив: ";
    svr::printArray(arr, size);
    
    const int inversionCount = svr::countInversions(arr, temp, 0, size - 1);
    
    std::cout << "Количество инверсий в массиве: " << inversionCount << std::endl;
    
    delete[] arr;
    delete[] temp;
    
    return 0;
}