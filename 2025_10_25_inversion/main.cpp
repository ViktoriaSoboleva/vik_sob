#include <iostream>
#include <vector>
#include "inversion_counter.h"
#include "array_utils.h"

int main()
{
    int size;
    
    std::cout << "Введите размер массива: ";
    std::cin >> size;
    
    std::vector<int> array(size);
    std::vector<int> temp(size);
    
    generateRandomArray(array);
    
    std::cout << "Сгенерированный массив: ";
    printArray(array);
    
    const int inversionCount = countInversions(array, temp, 0, size - 1);
    
    std::cout << "Количество инверсий в массиве: " << inversionCount << std::endl;
    
    return 0;
}