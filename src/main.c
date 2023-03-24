//
// Created by guanzhisong on 2023/3/22.
//
#include <stdlib.h>
#include "sort/sort.h"
#include "sort/util.h"

int int_cmp(const void *first, const void *second) {
    return (*(int *) (first)) - ((*(int *) second));
}

void int_swap(const void *first, const void *second) {
    if (first == second) {
        return;
    }
    int tmp = *((int *) first);
    *((int *) first) = *((int *) second);
    *((int *) second) = tmp;
}

void int_set(const void *first, const void *second) {
    if (first == second) {
        return;
    }
    *((int *) first) = *((int *) second);
}

int main(int argc, char *argv[]) {
    int arr[] = {10, 100, 1000, 10000, 100000,1000000};

    sort_struct s;
    s.arr_elem_len = sizeof(int);
    s.compare = int_cmp;
    s.swap = int_swap;
    s.set = int_set;

    int arr_len = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < arr_len; i++) {
        int len = arr[i];
        void *ptr = calloc(len, sizeof(int));
        build_random_int_arr(ptr, len, 100);
        s.arr = ptr;
        s.arr_len = len;

        if (len <= 10000) {
            sort_bench_mark("bubble_sort", &s, bubble_sort);
            sort_bench_mark("select_sort", &s, select_sort);
            sort_bench_mark("insert_sort", &s, insert_sort);
            sort_bench_mark("binary_insert_sort", &s, binary_insert_sort);
        }
        sort_bench_mark("quick_sort", &s, quick_sort);
        sort_bench_mark("merge_sort", &s, merge_sort);
        free(ptr);
    }
    return 0;
}

