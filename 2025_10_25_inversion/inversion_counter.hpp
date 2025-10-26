#ifndef INVERSION_COUNTER_H
#define INVERSION_COUNTER_H

#include <vector>

int mergeAndCount(std::vector<int>& array, std::vector<int>& temp, int left, int mid, int right);
int countInversions(std::vector<int>& array, std::vector<int>& temp, int left, int right);

#endif