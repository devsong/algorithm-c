//
// Created by guanzhisong on 2023/3/22.
//

#ifndef ALGORITHM_C_UTIL_H
#define ALGORITHM_C_UTIL_H

#include "sort.h"

void print_arr(int* arr, int len);

void build_random_int_arr(int *base, size_t size, int bound);

int is_sorted(const void *base, uint64_t len, size_t size, int(*cmp)(const void *, const void *));

#endif //ALGORITHM_C_UTIL_H
