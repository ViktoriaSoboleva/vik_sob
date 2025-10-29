#include "inversion_counter.hpp"

int svr::mergeAndCount(int* arr, int* temp, int left, int mid, int right)
{
    int i = left;
    int j = mid + 1;
    int k = left;
    int count = 0;
    
    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
        {
            temp[k] = arr[i];
            i++;
        }
        else
        {
            temp[k] = arr[j];
            j++;
            count += (mid - i + 1);
        }
        k++;
    }
    
    while (i <= mid)
    {
        temp[k] = arr[i];
        i++;
        k++;
    }
    
    while (j <= right)
    {
        temp[k] = arr[j];
        j++;
        k++;
    }
    
    for (int index = left; index <= right; index++)
    {
        arr[index] = temp[index];
    }
    
    return count;
}

int svr::countInversions(int* arr, int* temp, int left, int right)
{
    if (left >= right)
    {
        return 0;
    }
    
    const int mid = (left + right) / 2;
    int count = 0;
    
    count += countInversions(arr, temp, left, mid);
    count += countInversions(arr, temp, mid + 1, right);
    count += mergeAndCount(arr, temp, left, mid, right);
    
    return count;
}