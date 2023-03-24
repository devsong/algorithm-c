//
// Created by guanzhisong on 2023/3/27.
//

#ifndef ALGORITHM_C_TEST_SORT_H
#define ALGORITHM_C_TEST_SORT_H
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include "../src/sort/util.h"
#include "../src/sort/sort.h"

void sort_bench_mark(const char *sort_alg, p_sort_struct pss, void(*sort_func)(p_sort_struct));

void test_sort_benchmark();

#endif //ALGORITHM_C_TEST_SORT_H
