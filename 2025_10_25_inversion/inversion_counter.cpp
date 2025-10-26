#include "inversion_counter.h"

int mergeAndCount(std::vector<int>& array, std::vector<int>& temp, int left, int mid, int right)
{
    int i = left;
    int j = mid + 1;
    int k = left;
    int count = 0;
    
    while (i <= mid && j <= right)
    {
        if (array[i] <= array[j])
        {
            temp[k] = array[i];
            i++;
        }
        else
        {
            temp[k] = array[j];
            j++;
            count += (mid - i + 1);
        }
        k++;
    }
    
    while (i <= mid)
    {
        temp[k] = array[i];
        i++;
        k++;
    }
    
    while (j <= right)
    {
        temp[k] = array[j];
        j++;
        k++;
    }
    
    for (int index = left; index <= right; index++)
    {
        array[index] = temp[index];
    }
    
    return count;
}

int countInversions(std::vector<int>& array, std::vector<int>& temp, int left, int right)
{
    if (left >= right)
    {
        return 0;
    }
    
    const int mid = (left + right) / 2;
    int count = 0;
    
    count += countInversions(array, temp, left, mid);
    count += countInversions(array, temp, mid + 1, right);
    count += mergeAndCount(array, temp, left, mid, right);
    
    return count;
}