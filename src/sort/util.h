//
// Created by guanzhisong on 2023/3/22.
//

#ifndef ALGORITHM_C_UTIL_H
#define ALGORITHM_C_UTIL_H

#include "sort.h"

void print_arr(int arr[], int len);

void build_random_int_arr(int *base, size_t size, int bound);

int is_sorted(int *base, size_t size, int(*cmp)(const void *, const void *));

void cpy_arr(int *dst, int *src, size_t size);

void sort_bench_mark(const char *sort_alg, p_sort_struct pss, void(*sort_func)(p_sort_struct));

#endif //ALGORITHM_C_UTIL_H
