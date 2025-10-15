#include <cmath>
#include <iostream>

const int size = 20;
const int random_arr = 20;

void print_Arr(const int arr[], int size);
void fill_Random(int arr[], int size);
void reverse_Arr(int arr[], int size);

int main()
{
    int arr[size];

    fill_Random(arr, size);

    std::cout << "Исходный массив:" << std::endl;
    print_Arr(arr, size);

    reverse_Arr(arr, size);

    std::cout << "Массив после реверса:" << std::endl;
    print_Arr(arr, size);

    return 0;
}


void fill_Random(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % random_arr;
    }
}


void print_Arr(const int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
}

void reverse_Arr(int arr[], int size)
{
    for (int i = 0; i < size / 2; i++)
    {
        const int temp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = temp;
    }
}