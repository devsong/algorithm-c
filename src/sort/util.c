//
// Created by guanzhisong on 2023/3/22.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "util.h"
#include "sort.h"


void print_arr(int arr[], int len) {
    for (int i = 0; i < len - 1; i++) {
        printf("%d,", arr[i]);
    }
    printf("%d\n", arr[len - 1]);
}

void build_random_int_arr(int *base, size_t size, int bound) {
    srand(time(0));
    for (int i = 0; i < size; i++) {
        *(base + i) = (rand() % bound);
    }
}

int is_sorted(int *base, size_t size, int(*cmp)(const void *, const void *)) {
    for (int i = 0; i < size - 1; i++) {
        if (cmp(base + i, base + i + 1) > 0) {
            return 0;
        }
    }
    return 1;
}

void cpy_arr(int *dst, int *src, size_t size) {
    for (int i = 0; i < size; i++) {
        *(dst + i) = *(src + i);
    }
}

void sort_bench_mark(const char *sort_alg, p_sort_struct pss, void(*sort_func)(p_sort_struct)) {
    void *newArr = malloc(pss->arr_len * pss->arr_elem_len);
    int arr_len = pss->arr_len;
    void *oldArr = pss->arr;
    cpy_arr(newArr, pss->arr, arr_len);
    if (arr_len <= 10) {
        printf("origin arr\n");
        print_arr(newArr, arr_len);
    }
    pss->arr = newArr;
    clock_t start = clock();
    sort_func(pss);
    clock_t stop = clock();
    int result = is_sorted(pss->arr, pss->arr_len, pss->compare);
    printf("sort alg %s,len %d cost time %f\n", sort_alg, arr_len, (double) (stop - start) / CLOCKS_PER_SEC);
    if (!result) {
        printf("sort_alg %s is not sorted\n", sort_alg);
    }
    if (arr_len <= 10) {
        printf("sorted arr\n");
        print_arr(newArr, arr_len);
    }
    pss->arr = oldArr;
    free(newArr);
}
