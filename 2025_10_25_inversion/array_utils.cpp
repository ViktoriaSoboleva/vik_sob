#include "array_utils.h"
#include "constants.h"
#include <iostream>
#include <cstdlib>

void generateRandomArray(std::vector<int>& array)
{
    for (int i = 0; i < array.size(); i++)
    {
        array[i] = rand() % RANDOM_RANGE + 1;
    }
}

void printArray(const std::vector<int>& array)
{
    for (int i = 0; i < array.size(); i++)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}