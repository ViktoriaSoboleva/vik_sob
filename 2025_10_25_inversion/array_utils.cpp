#include "array_utils.hpp"
#include "constants.hpp"
#include <iostream>
#include <cstdlib>

void svr::generateRandomArray(int* arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % RANDOM_RANGE + 1;
    }
}

void svr::printArray(const int* arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}